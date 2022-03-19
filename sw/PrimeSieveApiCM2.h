#pragma once

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
#include <math.h>
#include <string>
#include <sstream>

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)
#define BASE_ADDRESS_0 0x43C00000
#define BASE_ADDRESS_1 0x43C10000

#define PE_COMPUTE_COMMAND 0
#define PE_CLEAR_MEMORY_COMMAND 1
#define PE_READ_MEMORY_COMMAND 2


#define FIRST_PRIME_CM2 3

class PrimeSieveApiCM2 {
private:
    uint16_t NUMBER_OF_ROWS;
    uint16_t NUMBER_OF_PE;
    uint16_t NUMBER_OF_STATUS_REGISTERS;
    uint32_t MAX_OFFSET;
    uint32_t MAX_N;
    unsigned *device_base_vaddress[2];
    void * getvaddr(off_t phys_addr);
public:
    PrimeSieveApiCM2(uint16_t pe = 280, uint16_t rows = 512);


    unsigned *pe_command_register_vaddress (unsigned pe_id, unsigned register_id);

    unsigned *pe_data_register_vaddress (unsigned pe_id);

    unsigned *pe_status_register_vaddress (unsigned pe_id);

    void write_command_register_0 (unsigned pe_id, unsigned argument_2, unsigned argument_3    );

    void write_command_register_1 (unsigned pe_id, unsigned command   , unsigned argument_1 = 0);

    unsigned read_command_register (unsigned pe_id, unsigned register_id);

    unsigned read_data_register (unsigned pe_id);

    unsigned read_status_register (unsigned pe_id);

    void write_register_0(unsigned pe_id, unsigned argument_1);

    void write_register_1(unsigned pe_id, unsigned argument_2, unsigned argument_3);

    void write_register_2(unsigned pe_id, unsigned command);

    unsigned read_register(unsigned pe_id, unsigned register_id);

    void clear_memory(unsigned pe_id);

    void clear_memory_all();

    unsigned read_memory_row(unsigned pe_id, unsigned row);

    void read_memory(unsigned pe_id);

    void read_memory_all();

    void compute(unsigned pe_id, unsigned step, unsigned first_offset);

    unsigned compute_for_current_prime(unsigned current_prime);

    unsigned get_next_prime(unsigned current_prime);

    void compute_all();

    std::stringstream read_memory_n(uint32_t n);

    void compute_prime(uint32_t n);

    float time_compute(uint32_t n);
};
