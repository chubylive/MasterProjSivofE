#pragma once

#include "PrimeSieveBase.h"

class PrimeSieveMethod2 : public PrimeSieveBase
{
private:
    unsigned last_compute_count;

public:
    PrimeSieveMethod2();
    ~PrimeSieveMethod2();
    void reconfig(uint16_t pe, uint16_t rows, uint32_t n = 0);
    void read_memory(unsigned pe_id);
    void compute(unsigned pe_id, unsigned step, unsigned first_offset, unsigned max_offset);
    unsigned compute_for_current_prime(unsigned current_prime);
    unsigned get_next_prime(unsigned current_prime);
    void compute_all();
    std::stringstream read_memory_n(uint32_t n);
    unsigned get_last_compute_count();
};
