
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
#define BASE_ADDRESS_2 0x43C20000

#define NUMBER_OF_ROWS 512
#define NUMBER_OF_PE   256
#define FIRST_PRIME    2

#define MAX_OFFSET     ((NUMBER_OF_ROWS << 5) - 1)

unsigned * device_base_vaddress [3];

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

        mapped_dev_base = (void *) ((off_t) mapped_base + (off_t) (dev_base & MAP_MASK));
        return mapped_dev_base;
}

unsigned * pe_register_vaddress (unsigned pe_id, unsigned register_id) {
        unsigned * vaddress = device_base_vaddress [pe_id >> 7] + ((pe_id & 127) << 2) + register_id;
        return vaddress;
}

void write_register_0 (unsigned pe_id, unsigned argument_1) {
        unsigned * vaddress = pe_register_vaddress (pe_id, 0);
        * vaddress = argument_1;
}

void write_register_1 (unsigned pe_id, unsigned argument_2, unsigned argument_3) {
        unsigned * vaddress = pe_register_vaddress (pe_id, 1);
        * vaddress = argument_2 | (argument_3 << 16);
}

void write_register_2 (unsigned pe_id, unsigned command) {
        unsigned * vaddress = pe_register_vaddress (pe_id, 2);
        * vaddress = (command << 4);
}

unsigned read_register (unsigned pe_id, unsigned register_id) {
        unsigned * vaddress = pe_register_vaddress (pe_id, register_id);
        unsigned register_read_data = * vaddress;
        return register_read_data;
}

void clear_memory (unsigned pe_id) {
        write_register_2 (pe_id, 1);
}

void clear_memory_all (void) {
        unsigned pe_busy [NUMBER_OF_PE];
        unsigned done;

        for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                clear_memory (pe_id);
                pe_busy [pe_id] = 1;
        }

        do {
                done = 1;

                for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                        if (pe_busy [pe_id]) {
                                unsigned register_2 = read_register (pe_id, 2);

                                if (register_2 & 1) {
                                        done = 0;
                                } else {
                                        pe_busy [pe_id] = 0;
                                }
                        }
                }
        } while (done == 0);
}

unsigned read_memory_row (unsigned pe_id, unsigned row) {
        unsigned register_2;
        unsigned register_3;

        write_register_0 (pe_id, row);
        write_register_2 (pe_id, 2);

        do {
                register_2 = read_register (pe_id, 2);
        } while (register_2 & 1);

        register_3 = read_register (pe_id, 3);

        return register_3;
}

void read_memory (unsigned pe_id) {
        for (unsigned row = 0; row < NUMBER_OF_ROWS; row ++) {
                unsigned memory_read_data;

                memory_read_data = read_memory_row (pe_id, row);

                for (unsigned bit_position = 0; bit_position < 32; bit_position ++) {
                        if ((memory_read_data & (1 << bit_position)) == 0) {
                                unsigned boolean_id;

                                boolean_id = ((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position;

                                if (boolean_id >= FIRST_PRIME) {
                                        printf ("%u\n", boolean_id);
                                }
                        }
                }
        }
}

void read_memory_all (void) {
        for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                read_memory (pe_id);
        }
}

void compute (unsigned pe_id, unsigned step, unsigned first_offset, unsigned max_offset) {
        write_register_0 (pe_id, step);
        write_register_1 (pe_id, first_offset, max_offset);
        write_register_2 (pe_id, 0);
}

unsigned compute_for_current_prime (unsigned current_prime) {
        unsigned current_prime_squared;

        current_prime_squared = current_prime * current_prime;

        if (current_prime_squared > (((NUMBER_OF_PE * NUMBER_OF_ROWS) << 5) - 1)) {
                return 0;
        } else {
                unsigned current_boolean_id;

                unsigned pe_busy [NUMBER_OF_PE];
                unsigned done;

                current_boolean_id = current_prime_squared;

                for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                        pe_busy [pe_id] = 0;
                }

                do {
                        unsigned pe_id;
                        unsigned first_offset;

                        pe_id = current_boolean_id / (MAX_OFFSET + 1);
                        first_offset = current_boolean_id % (MAX_OFFSET + 1);

                        compute (pe_id, current_prime, first_offset, MAX_OFFSET);
                        pe_busy [pe_id] = 1;

                        current_boolean_id += (((MAX_OFFSET - first_offset) / current_prime) + 1) * current_prime;
                } while (current_boolean_id <= (((NUMBER_OF_PE * NUMBER_OF_ROWS) << 5) - 1));

                do {
                        done = 1;

                        for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                                if (pe_busy [pe_id]) {
                                        unsigned register_2 = read_register (pe_id, 2);

                                        if (register_2 & 1) {
                                                done = 0;
                                        } else {
                                                pe_busy [pe_id] = 0;
                                        }
                                }
                        }
                } while (done == 0);

                return 1;
        }
}

unsigned get_next_prime (unsigned current_prime) {
        unsigned memory_read_data_available;

        memory_read_data_available = 0;

        while (1) {
                unsigned global_row;
                unsigned bit_position;
                unsigned memory_read_data;

                unsigned pe_id;
                unsigned row;

                current_prime ++;

                global_row = current_prime >> 5;
                bit_position = current_prime & 31;

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

        return current_prime;
}

void compute_all (void) {
        unsigned current_prime;

        current_prime = FIRST_PRIME;

        while (compute_for_current_prime (current_prime)) {
                current_prime = get_next_prime (current_prime);
        }
}

int main () {
        device_base_vaddress [0] = (unsigned *) getvaddr (BASE_ADDRESS_0);
        device_base_vaddress [1] = (unsigned *) getvaddr (BASE_ADDRESS_1);
//      device_base_vaddress [2] = (unsigned *) getvaddr (BASE_ADDRESS_2);

        clear_memory_all ();
        compute_all      ();
        read_memory_all  ();

        return 0;
}

