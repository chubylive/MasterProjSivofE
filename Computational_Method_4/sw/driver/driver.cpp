
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define BASE_ADDRESS_0 0x43C00000
#define BASE_ADDRESS_1 0x43C10000

#define NUMBER_OF_ROWS 512
#define NUMBER_OF_PE   272
#define FIRST_PRIME    7

#define MAX_OFFSET     (((NUMBER_OF_ROWS << 2) - 1) * 30 + 29)

#define MAX_N          ((((NUMBER_OF_PE * NUMBER_OF_ROWS) << 2) - 1) * 30 + 29)

#define PE_COMPUTE_COMMAND 0
#define PE_CLEAR_MEMORY_COMMAND 1
#define PE_READ_MEMORY_COMMAND 2

#define NUMBER_OF_STATUS_REGISTERS ((NUMBER_OF_PE / 32) + (((NUMBER_OF_PE % 32) == 0) ? 0 : 1))

unsigned * device_base_vaddress [2];

unsigned delta [8] = {6, 4, 2, 4, 2, 4, 6, 2};

void * getvaddr(off_t phys_addr) {
        void * mapped_base;
        int memfd;

        void * mapped_dev_base;
        off_t dev_base = phys_addr;

        memfd = open("/dev/mem", O_RDWR | O_SYNC); // to open this the program needs to be run as root
        if (memfd == -1) {
                printf("Can’t open /dev/mem.\n");
                exit(0);
        }

        // Map one page of memory into user space such that the device is in that page, but it may not
        // be at the start of the page

        mapped_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, dev_base & (~ MAP_MASK));
        if (mapped_base == (void *) -1) {
                printf("Can’t map the memory to user space.\n");
                exit(0);
        }

        // get the address of the device in user space which will be an offset from the base
        // that was mapped as memory is mapped at the start of a page

        mapped_dev_base = (void *) (((off_t) mapped_base) + (off_t) (dev_base & MAP_MASK));
        return mapped_dev_base;
}

unsigned index_to_value (unsigned index) {
        unsigned q = index >> 3;
        unsigned r;

        switch (index & 7) {
                case 0 : {
                        r = 1;
                        break;
                }

                case 1 : {
                        r = 7;
                        break;
                }

                case 2 : {
                        r = 11;
                        break;
                }

                case 3 : {
                        r = 13;
                        break;
                }

                case 4 : {
                        r = 17;
                        break;
                }

                case 5 : {
                        r = 19;
                        break;
                }

                case 6 : {
                        r = 23;
                        break;
                }

                case 7 : {
                        r = 29;
                }
        }

        return (30 * q + r);
}

unsigned value_to_index (unsigned value) {
        unsigned q = value / 30;
        unsigned r;

        switch (value % 30) {
                case 1 : {
                        r = 0;
                        break;
                }

                case 7 : {
                        r = 1;
                        break;
                }

                case 11 : {
                        r = 2;
                        break;
                }

                case 13 : {
                        r = 3;
                        break;
                }

                case 17 : {
                        r = 4;
                        break;
                }

                case 19 : {
                        r = 5;
                        break;
                }

                case 23 : {
                        r = 6;
                        break;
                }

                case 29 : {
                        r = 7;
                }
        }

        return ((q << 3) | r);
}

unsigned * pe_command_register_vaddress (unsigned pe_id, unsigned register_id) {
        unsigned * vaddress;

        if (pe_id < 128) {
                vaddress = device_base_vaddress [0] + ( pe_id        << 1) + register_id;
        } else {
                vaddress = device_base_vaddress [1] + ((pe_id - 128) << 1) + register_id;
        }

        return vaddress;
}

unsigned * pe_data_register_vaddress (unsigned pe_id) {
        unsigned * vaddress;

        if (pe_id < 128) {
                vaddress = device_base_vaddress [0] + 320 +  pe_id       ;
        } else {
                vaddress = device_base_vaddress [1] + 320 + (pe_id - 128);
        }

        return vaddress;
}

unsigned * pe_status_register_vaddress (unsigned pe_id) {
        unsigned * vaddress;

        if (pe_id < 128) {
                vaddress = device_base_vaddress [0] + 480 + ( pe_id        >> 5);
        } else {
                vaddress = device_base_vaddress [1] + 480 + ((pe_id - 128) >> 5);
        }

        return vaddress;
}

void write_command_register_0 (unsigned pe_id, unsigned first_offset_q, unsigned max_offset_q) {
        unsigned * vaddress = pe_command_register_vaddress (pe_id, 0);
        * vaddress = first_offset_q | (max_offset_q << 16);
}

void write_command_register_1 (unsigned pe_id, unsigned command, unsigned step_q = 0, unsigned step_r = 0, unsigned step_delta_index = 0, unsigned first_offset_r = 0, unsigned max_offset_r = 0) {
        unsigned * vaddress = pe_command_register_vaddress (pe_id, 1);
        * vaddress = command | (step_q << 4) | (step_r << 16) | (step_delta_index << 20) | (first_offset_r << 24) | (max_offset_r << 28);
}

unsigned read_command_register (unsigned pe_id, unsigned register_id) {
        unsigned * vaddress = pe_command_register_vaddress (pe_id, register_id);
        unsigned register_read_data = * vaddress;
        return register_read_data;
}

unsigned read_data_register (unsigned pe_id) {
        unsigned * vaddress = pe_data_register_vaddress (pe_id);
        unsigned register_read_data = * vaddress;
        return register_read_data;
}

unsigned read_status_register (unsigned pe_id) {
        unsigned * vaddress = pe_status_register_vaddress (pe_id);
        unsigned register_read_data = * vaddress;
        return register_read_data;
}

void clear_memory (unsigned pe_id) {
        write_command_register_1 (pe_id, PE_CLEAR_MEMORY_COMMAND);
}

void clear_memory_all (void) {
        unsigned status_register [NUMBER_OF_STATUS_REGISTERS];
        unsigned done;

        for (unsigned i = 0; i < NUMBER_OF_STATUS_REGISTERS; i ++) {
                status_register [i] = 0;
        }

        for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                clear_memory (pe_id);
                status_register [pe_id >> 5] |= (1 << (pe_id & 31));
        }

        do {
                done = 1;

                for (unsigned i = 0; i < NUMBER_OF_STATUS_REGISTERS; i ++) {
                        if (status_register [i] != 0) {
                                unsigned status = read_status_register (i << 5);

                                if (status != 0) {
                                        done = 0;
                                }

                                status_register [i] &= status;
                        }
                }
        } while (done == 0);
}

unsigned read_memory_row (unsigned pe_id, unsigned row) {
        unsigned status_register;
        unsigned data_register;

        write_command_register_1 (pe_id, PE_READ_MEMORY_COMMAND, row);

        do {
                status_register = read_status_register (pe_id);
        } while (status_register != 0);

        data_register = read_data_register (pe_id);

        return data_register;
}

void read_memory (unsigned pe_id) {
        for (unsigned row = 0; row < NUMBER_OF_ROWS; row ++) {
                unsigned memory_read_data;

                memory_read_data = read_memory_row (pe_id, row);

                for (unsigned bit_position = 0; bit_position < 32; bit_position ++) {
                        if ((memory_read_data & (1 << bit_position)) == 0) {
                                unsigned boolean_id;
                                unsigned value;

                                boolean_id = ((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position;

                                value = index_to_value (boolean_id);

                                if (value >= FIRST_PRIME) {
                                        printf ("%u\n", value);
                                }
                        }
                }
        }
}

void read_memory_all (void) {
        printf ("2\n");
        printf ("3\n");
        printf ("5\n");

        for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                read_memory (pe_id);
        }
}

void compute (unsigned pe_id, unsigned step_q, unsigned step_r, unsigned step_delta_index, unsigned first_offset_q, unsigned first_offset_r, unsigned max_offset_q, unsigned max_offset_r) {
        write_command_register_0 (pe_id, first_offset_q, max_offset_q);
        write_command_register_1 (pe_id, PE_COMPUTE_COMMAND, step_q, step_r, step_delta_index, first_offset_r, max_offset_r);
}

unsigned compute_for_current_prime (unsigned current_prime) {
        unsigned current_prime_squared;

        current_prime_squared = current_prime * current_prime;

        if (current_prime_squared > MAX_N) {
                return 0;
        } else {
                unsigned current_boolean_id;
                unsigned current_prime_delta_index;

                unsigned current_prime_r_encoded;

                unsigned status_register [NUMBER_OF_STATUS_REGISTERS];
                unsigned done;

                current_boolean_id = current_prime_squared;

                switch (current_prime % 30) {
                        case 1 : {
                                current_prime_delta_index = 0;
                                break;
                        }

                        case 7 : {
                                current_prime_delta_index = 1;
                                break;
                        }

                        case 11 : {
                                current_prime_delta_index = 2;
                                break;
                        }

                        case 13 : {
                                current_prime_delta_index = 3;
                                break;
                        }

                        case 17 : {
                                current_prime_delta_index = 4;
                                break;
                        }

                        case 19 : {
                                current_prime_delta_index = 5;
                                break;
                        }

                        case 23 : {
                                current_prime_delta_index = 6;
                                break;
                        }

                        case 29 : {
                                current_prime_delta_index = 7;
                        }
                }

                current_prime_r_encoded = current_prime_delta_index;

                for (unsigned i = 0; i < NUMBER_OF_STATUS_REGISTERS; i ++) {
                        status_register [i] = 0;
                }

                do {
                        unsigned pe_id;
                        unsigned first_offset;

                        unsigned i;
                        unsigned j;
                        unsigned k;
                        unsigned l;

                        pe_id = current_boolean_id / (MAX_OFFSET + 1);
                        first_offset = current_boolean_id % (MAX_OFFSET + 1);

                        compute (pe_id, current_prime / 30, current_prime_r_encoded, current_prime_delta_index, first_offset / 30, (first_offset % 30) >> 1, (NUMBER_OF_ROWS << 2) - 1, 7);
                        status_register [pe_id >> 5] |= (1 << (pe_id & 31));

                        i = (MAX_OFFSET - first_offset) / current_prime;
                        j = i / 30;
                        k = i % 30;
                        l = 30 * j;

                        for (unsigned m = 0; m < 8; m ++) {
                                l += delta [current_prime_delta_index];

                                if (k < delta [current_prime_delta_index]) {
                                        current_prime_delta_index = (current_prime_delta_index + 1) % 8;

                                        break;
                                }

                                k -= delta [current_prime_delta_index];
                                current_prime_delta_index = (current_prime_delta_index + 1) % 8;
                        }

                        current_boolean_id += (l * current_prime);
                } while (current_boolean_id <= MAX_N);

                do {
                        done = 1;

                        for (unsigned i = 0; i < NUMBER_OF_STATUS_REGISTERS; i ++) {
                                if (status_register [i] != 0) {
                                        unsigned status = read_status_register (i << 5);

                                        if (status != 0) {
                                                done = 0;
                                        }

                                        status_register [i] &= status;
                                }
                        }
                } while (done == 0);

                return 1;
        }
}

unsigned get_next_index (unsigned current_index) {
        unsigned memory_read_data_available;

        memory_read_data_available = 0;

        while (1) {
                unsigned global_row;
                unsigned bit_position;
                unsigned memory_read_data;

                unsigned pe_id;
                unsigned row;

                current_index ++;

                global_row = current_index >> 5;
                bit_position = current_index & 31;

                if (memory_read_data_available && ((global_row / NUMBER_OF_ROWS) == pe_id) && ((global_row % NUMBER_OF_ROWS) == row)) {
                } else {
                        memory_read_data_available = 1;
                        pe_id = global_row / NUMBER_OF_ROWS;
                        row = global_row % NUMBER_OF_ROWS;

                        memory_read_data = read_memory_row (pe_id, row);
                }

                if ((memory_read_data & (1 << bit_position)) == 0) {
                        break;
                }
        }

        return current_index;
}

void compute_all (void) {
        unsigned current_prime;
        unsigned current_index;

        current_prime = FIRST_PRIME;

        current_index = value_to_index (current_prime);

        while (compute_for_current_prime (current_prime)) {
                current_index = get_next_index (current_index);
                current_prime = index_to_value (current_index);
        }
}

int main () {
        unsigned * clock_counter_vaddress;
        unsigned clock_counter [4];

        device_base_vaddress [0] = (unsigned *) getvaddr (BASE_ADDRESS_0);
        device_base_vaddress [1] = (unsigned *) getvaddr (BASE_ADDRESS_1);

        clock_counter_vaddress = device_base_vaddress [1] + 496;

        clock_counter [0] = * clock_counter_vaddress;
        clear_memory_all ();
        clock_counter [1] = * clock_counter_vaddress;
        compute_all      ();
        clock_counter [2] = * clock_counter_vaddress;
        read_memory_all  ();
        clock_counter [3] = * clock_counter_vaddress;

        for (unsigned i = 1; i < 4; i ++) {
                printf ("clock_counter [%u] = %u\n", i, clock_counter [i]);
        }

        return 0;
}

