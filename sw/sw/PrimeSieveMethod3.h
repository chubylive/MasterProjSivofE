#pragma once

#include "PrimeSieveBase.h"

class PrimeSieveMethod3 : public PrimeSieveBase
{
private:
    unsigned last_compute_count;

public:
    PrimeSieveMethod3();
    ~PrimeSieveMethod3();
    void reconfig(uint16_t pe, uint16_t rows, uint32_t n = 0);
    unsigned index_to_value(unsigned index);
    unsigned value_to_index(unsigned value);
    void write_command_register_1(unsigned pe_id, unsigned command, unsigned step_q = 0, unsigned step_r = 0, unsigned step_delta_index = 0, unsigned first_offset_r = 0, unsigned max_offset_r = 0);
    void read_memory(unsigned pe_id);
    void compute(unsigned pe_id, unsigned step_q, unsigned step_r, unsigned step_delta_index, unsigned first_offset_q, unsigned first_offset_r, unsigned max_offset_q, unsigned max_offset_r);
    void compute(unsigned pe_id, unsigned step, unsigned first_offset, unsigned max_offset);
    unsigned compute_for_current_prime(unsigned current_prime);
    unsigned get_next_prime(unsigned current_prime);
    unsigned get_next_index(unsigned current_index);
    void compute_all();
    std::stringstream read_memory_n(uint32_t n);
    unsigned get_last_compute_count();
};
