#include "PrimeSieveApiCM3.h"
#include <time.h>
#include <sys/time.h>

void *PrimeSieveApiCM3::getvaddr(off_t phys_addr)
{
    void *mapped_base;
    int memfd;

    void *mapped_dev_base;
    off_t dev_base = phys_addr;

    memfd = open("/dev/mem", O_RDWR | O_SYNC); // to open this the program needs to be run as root
    if (memfd == -1)
    {
        printf("Can’t open /dev/mem.\n");
        exit(0);
    }

    // Map one page of memory into user space such that the device is in that page, but it may not
    // be at the start of the page

    mapped_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, dev_base & (~MAP_MASK));
    if (mapped_base == (void *) - 1)
    {
        printf("Can’t map the memory to user space.\n");
        exit(0);
    }

    // get the address of the device in user space which will be an offset from the base
    // that was mapped as memory is mapped at the start of a page

    mapped_dev_base = (void *)((off_t)mapped_base + (off_t)(dev_base & MAP_MASK));
    return mapped_dev_base;
}

unsigned PrimeSieveApiCM3::index_to_value (unsigned index) {
    unsigned q = index >> 1;
    unsigned r = ((index & 1) == 0) ? 1 : 5;
    return (6 * q + r);
}
unsigned PrimeSieveApiCM3::value_to_index (unsigned value) {
    unsigned q = value / 6;
    unsigned r = ((value % 6) == 1) ? 0 : 1;
    return ((q << 1) | r);
}

PrimeSieveApiCM3::PrimeSieveApiCM3(uint16_t pe, uint16_t rows) : NUMBER_OF_PE(pe <= 280 ? pe : 280),
    NUMBER_OF_ROWS(rows <= 512 ? rows : 512)
{
    device_base_vaddress[0] = (unsigned *)getvaddr(BASE_ADDRESS_0);
    device_base_vaddress[1] = (unsigned *)getvaddr(BASE_ADDRESS_1);
    MAX_OFFSET = (((NUMBER_OF_ROWS << 4) - 1) * 6 + 5);
    NUMBER_OF_STATUS_REGISTERS = ((NUMBER_OF_PE / 32) + (((NUMBER_OF_PE % 32) == 0) ? 0 : 1));
    MAX_N = ((((NUMBER_OF_PE * NUMBER_OF_ROWS) << 4) - 1) * 6 + 5);
}

unsigned *PrimeSieveApiCM3::pe_command_register_vaddress(unsigned pe_id, unsigned register_id)
{
    unsigned * vaddress;

    if (pe_id < 128) {
        vaddress = device_base_vaddress [0] + ( pe_id        << 1) + register_id;
    } else {
        vaddress = device_base_vaddress [1] + ((pe_id - 128) << 1) + register_id;
    }

    return vaddress;
}

unsigned *PrimeSieveApiCM3::pe_data_register_vaddress (unsigned pe_id) {
    unsigned * vaddress;

    if (pe_id < 128) {
        vaddress = device_base_vaddress [0] + 320 +  pe_id       ;
    } else {
        vaddress = device_base_vaddress [1] + 320 + (pe_id - 128);
    }

    return vaddress;
}

unsigned *PrimeSieveApiCM3::pe_status_register_vaddress (unsigned pe_id) {
    unsigned * vaddress;

    if (pe_id < 128) {
        vaddress = device_base_vaddress [0] + 480 + ( pe_id        >> 5);
    } else {
        vaddress = device_base_vaddress [1] + 480 + ((pe_id - 128) >> 5);
    }

    return vaddress;
}


void PrimeSieveApiCM3::write_command_register_0 (unsigned pe_id, unsigned first_offset_q, unsigned max_offset_q) {
    unsigned * vaddress = pe_command_register_vaddress (pe_id, 0);
    * vaddress = first_offset_q | (max_offset_q << 16);
}

void PrimeSieveApiCM3::write_command_register_1 (unsigned pe_id, unsigned command, unsigned step_q, unsigned step_r, unsigned step_delta_index, unsigned first_offset_r, unsigned max_offset_r) {
    unsigned * vaddress = pe_command_register_vaddress (pe_id, 1);
    * vaddress = command | (step_q << 4) | (step_r << 16) | (step_delta_index << 20) | (first_offset_r << 24) | (max_offset_r << 28);
}

unsigned PrimeSieveApiCM3::read_command_register (unsigned pe_id, unsigned register_id) {
    unsigned * vaddress = pe_command_register_vaddress (pe_id, register_id);
    unsigned register_read_data = * vaddress;
    return register_read_data;
}

unsigned PrimeSieveApiCM3::read_data_register (unsigned pe_id) {
    unsigned * vaddress = pe_data_register_vaddress (pe_id);
    unsigned register_read_data = * vaddress;
    return register_read_data;
}

unsigned PrimeSieveApiCM3::read_status_register (unsigned pe_id) {
    unsigned * vaddress = pe_status_register_vaddress (pe_id);
    unsigned register_read_data = * vaddress;
    return register_read_data;
}


void PrimeSieveApiCM3::clear_memory(unsigned pe_id)
{
    write_command_register_1 (pe_id, PE_CLEAR_MEMORY_COMMAND);
}

void PrimeSieveApiCM3::clear_memory_all() {
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


unsigned PrimeSieveApiCM3::read_memory_row(unsigned pe_id, unsigned row) {
    unsigned status_register;
    unsigned data_register;

    write_command_register_1 (pe_id, PE_READ_MEMORY_COMMAND, row);

    do {
        status_register = read_status_register (pe_id);
    } while (status_register != 0);

    data_register = read_data_register (pe_id);

    return data_register;
}

void PrimeSieveApiCM3::read_memory(unsigned pe_id) {
    for (unsigned row = 0; row < NUMBER_OF_ROWS; row ++) {
        unsigned memory_read_data;
        memory_read_data = read_memory_row (pe_id, row);
        for (unsigned bit_position = 0; bit_position < 32; bit_position ++) {
            if ((memory_read_data & (1 << bit_position)) == 0) {
                unsigned boolean_id;
                unsigned value;
                boolean_id = ((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position;
                value = index_to_value (boolean_id);
                if (value >= FIRST_PRIME_CM3) {
                    printf ("%u\n", value);
                }
            }
        }
    }
}

void PrimeSieveApiCM3::read_memory_all()
{
    for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id++)
    {
        read_memory(pe_id);
    }
}

void PrimeSieveApiCM3::compute (unsigned pe_id, unsigned step_q, unsigned step_r, unsigned step_delta_index, unsigned first_offset_q, unsigned first_offset_r, unsigned max_offset_q, unsigned max_offset_r) {
    write_command_register_0 (pe_id, first_offset_q, max_offset_q);
    write_command_register_1 (pe_id, PE_COMPUTE_COMMAND, step_q, step_r, step_delta_index, first_offset_r, max_offset_r);
}


unsigned PrimeSieveApiCM3::compute_for_current_prime(unsigned current_prime)
{
    unsigned current_prime_squared;
    current_prime_squared = current_prime * current_prime;
    if (current_prime_squared > MAX_N) {
        return 0;
    } else {
        unsigned current_boolean_id;
        unsigned current_prime_delta_index;
        unsigned status_register [NUMBER_OF_STATUS_REGISTERS];
        unsigned done;
        current_boolean_id = current_prime_squared;
        current_prime_delta_index = ((current_prime % 6) == 1) ? 0 : 1;
        for (unsigned i = 0; i < NUMBER_OF_STATUS_REGISTERS; i ++) {
            status_register [i] = 0;
        }
        do {
            unsigned pe_id;
            unsigned first_offset;
            unsigned i;
            unsigned j;
            unsigned k;
            pe_id = current_boolean_id / (MAX_OFFSET + 1);
            first_offset = current_boolean_id % (MAX_OFFSET + 1);
            compute (pe_id, current_prime / 6, (current_prime % 6) >> 2, current_prime_delta_index, first_offset / 6, (first_offset % 6) >> 2, (NUMBER_OF_ROWS << 4) - 1, 1);
            status_register [pe_id >> 5] |= (1 << (pe_id & 31));
            i = (MAX_OFFSET - first_offset) / current_prime;
            j = i / 6;
            k = i % 6;
            if (k >= delta [current_prime_delta_index]) {
                current_boolean_id += (6 * (j + 1) * current_prime);
            } else {
                current_boolean_id += ((6 * j + delta [current_prime_delta_index]) * current_prime);
                current_prime_delta_index = 1 - current_prime_delta_index;
            }
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

unsigned PrimeSieveApiCM3::get_next_index (unsigned current_index) {
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


void PrimeSieveApiCM3::compute_all()
{
    unsigned current_prime;
    unsigned current_index;

    current_prime = FIRST_PRIME_CM3;

    current_index = value_to_index (current_prime);

    while (compute_for_current_prime (current_prime)) {
        current_index = get_next_index (current_index);
        current_prime = index_to_value (current_index);
    }
}

std::stringstream PrimeSieveApiCM3::read_memory_n(uint32_t n)
{
    std::stringstream res;
    bool done = false;
    for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE && !done; pe_id++)
    {
        for (unsigned row = 0; row < NUMBER_OF_ROWS && !done; row++)
        {
            unsigned memory_read_data = read_memory_row(pe_id, row);
            for (unsigned bit_position = 0; bit_position < 32; bit_position++)
            {
                if ((memory_read_data & (1 << bit_position)) == 0)
                {
                    unsigned boolean_id = ((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position;
                    unsigned value = index_to_value (boolean_id);
                    if (value <= n)
                    {
                        if (value >= FIRST_PRIME_CM3)
                        {
                            res << value << "\n";
                        }
                    }
                    else
                    {
                        done = true;
                    }
                }
            }
        }
    }
    return res;
}

void PrimeSieveApiCM3::compute_prime(uint32_t n)
{
    const uint32_t max_sup_prime = (NUMBER_OF_ROWS * 32 * NUMBER_OF_PE) - 1;
    const uint32_t max_sup_num_of_primes = (max_sup_prime / (log(max_sup_prime) - 1)); // Prime-number theorem: π(n) ≈ n/ln(n)

    unsigned current_prime = FIRST_PRIME_CM3;
    unsigned current_index = value_to_index (current_prime);
    unsigned current_prime_squared = current_prime * current_prime;


    while (compute_for_current_prime(current_prime) && current_prime_squared <= n)
    {
        current_index = get_next_index (current_index);
        current_prime = index_to_value(current_index);
        current_prime_squared = current_prime * current_prime;
    }


}

float PrimeSieveApiCM3::time_compute(uint32_t n)
{
    clock_t start, end;
    clear_memory_all();
    FILE * fp;
    fp = fopen ("cm3Out.txt", "w");
    start = clock();
    compute_prime(n);
    end = clock();
    std::stringstream res = read_memory_n(n);

    float cpu_time = ((float)(end - start)) * 1000 / CLOCKS_PER_SEC;
    // printf("%s\n", res.str().c_str());
    fprintf(fp, "%s",  res.str().c_str());
    fclose(fp);
    return cpu_time;
}


float PrimeSieveApiCM3::time_compute_int(uint32_t n)
{
    unsigned * clock_counter_vaddress = device_base_vaddress [1] + 496;

    unsigned clockStart, clockEnd;

    clock_t start, end;
    clear_memory_all();
    FILE * fp;
    fp = fopen ("cm3Out.txt", "w");
    // start = clock();
    clockStart = * clock_counter_vaddress;
    compute_prime(n);
    // end = clock();
    clockEnd = * clock_counter_vaddress;
    std::stringstream res = read_memory_n(n);

    // float cpu_time = ((float)(end - start)) * 1000 / CLOCKS_PER_SEC;
    // printf("%s\n", res.str().c_str());
    fprintf(fp, "%s",  res.str().c_str());
    fclose(fp);
    return ((1/5e7) * ((float)clockEnd) ) * 1000;
}