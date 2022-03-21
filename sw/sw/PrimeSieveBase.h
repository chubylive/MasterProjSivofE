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
#include <sstream>

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define BASE_ADDRESS_0 0x43C00000
#define BASE_ADDRESS_1 0x43C10000
#define PE_COMPUTE_COMMAND 0
#define PE_CLEAR_MEMORY_COMMAND 1
#define PE_READ_MEMORY_COMMAND 2

class PrimeSieveBase
{
protected:
    unsigned NUMBER_OF_PE;
    unsigned NUMBER_OF_ROWS;
    unsigned FIRST_PRIME;
    uint32_t MAX_OFFSET;
    uint32_t MAX_N;
    uint32_t NUMBER_OF_STATUS_REGISTERS;
    unsigned *device_base_vaddress[2];
    unsigned delta[2];

public:
    PrimeSieveBase();
    ~PrimeSieveBase();
    void *getvaddr(off_t phys_addr);
    unsigned *pe_command_register_vaddress(unsigned pe_id, unsigned register_id);
    unsigned *pe_data_register_vaddress(unsigned pe_id);
    unsigned *pe_status_register_vaddress(unsigned pe_id);
    void write_command_register_0(unsigned pe_id, unsigned argument_2, unsigned argument_3);
    void write_command_register_1(unsigned pe_id, unsigned command, unsigned argument_1 = 0);
    unsigned read_command_register(unsigned pe_id, unsigned register_id);
    unsigned read_data_register(unsigned pe_id);
    unsigned read_status_register(unsigned pe_id);
    void clear_memory(unsigned pe_id);
    void clear_memory_all();
    unsigned read_memory_row(unsigned pe_id, unsigned row);
    float time_compute_0(uint32_t n, unsigned pe, unsigned rows);
    float time_compute_1(uint32_t n, unsigned pe, unsigned rows);
    void read_memory_all();
    virtual void reconfig(uint16_t pe, uint16_t rows, uint32_t n = 0) = 0;
    virtual void read_memory(unsigned pe_id) = 0;
    virtual void compute(unsigned pe_id, unsigned step, unsigned first_offset, unsigned max_offset) = 0;
    virtual unsigned compute_for_current_prime(unsigned current_prime) = 0;
    virtual unsigned get_next_prime(unsigned current_prime) = 0;
    virtual void compute_all() = 0;
    virtual std::stringstream read_memory_n(uint32_t n) = 0;
};
