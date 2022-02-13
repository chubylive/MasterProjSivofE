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
#define BASE_ADDRESS_2 0x43C20000
#define FIRST_PRIME 2

class PrimeSieveApi
{
private:
    uint16_t NUMBER_OF_ROWS;
    uint16_t NUMBER_OF_PE;
    uint32_t MAX_OFFSET;
    unsigned *device_base_vaddress[3];

public:
    PrimeSieveApi(uint16_t pe = 256, uint16_t rows = 512);

    unsigned *pe_register_vaddress(unsigned pe_id, unsigned register_id);

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

    std::stringstream compute_prime(uint32_t n);

    float time_compute(uint32_t n);
};
