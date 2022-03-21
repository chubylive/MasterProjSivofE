#include "PrimeSieveMethod2.h"

PrimeSieveMethod2::PrimeSieveMethod2() : PrimeSieveBase()
{
    last_compute_count = 0U;
    FIRST_PRIME = 3;
    MAX_OFFSET = ((NUMBER_OF_ROWS << 5) - 1);
    MAX_N = (((NUMBER_OF_PE * NUMBER_OF_ROWS) << 6) - 1);
}

PrimeSieveMethod2::~PrimeSieveMethod2()
{
}

void PrimeSieveMethod2::reconfig(uint16_t pe, uint16_t rows, uint32_t n)
{
    last_compute_count = 0U;
    NUMBER_OF_PE = (pe <= 280 ? (pe > 0 ? pe : 1) : 280);
    NUMBER_OF_ROWS = (rows <= 512 ? (rows > 0 ? rows : 1) : 512);
    MAX_OFFSET = ((NUMBER_OF_ROWS << 5) - 1);
    MAX_N = (n == 0 ? (((NUMBER_OF_PE * NUMBER_OF_ROWS) << 6) - 1) : n);
    NUMBER_OF_STATUS_REGISTERS = ((NUMBER_OF_PE / 32) + (((NUMBER_OF_PE % 32) == 0) ? 0 : 1));
}

void PrimeSieveMethod2::read_memory(unsigned pe_id)
{
    for (unsigned row = 0; row < NUMBER_OF_ROWS; row++)
    {
        unsigned memory_read_data = read_memory_row(pe_id, row);
        for (unsigned bit_position = 0; bit_position < 32; bit_position++)
        {
            if ((memory_read_data & (1 << bit_position)) == 0)
            {
                unsigned boolean_id = ((((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position) << 1) + 1;
                if (boolean_id >= FIRST_PRIME)
                {
                    printf("%u\n", boolean_id);
                }
            }
        }
    }
}

void PrimeSieveMethod2::compute(unsigned pe_id, unsigned step, unsigned first_offset, unsigned max_offset)
{
    write_command_register_0(pe_id, first_offset, max_offset);
    write_command_register_1(pe_id, PE_COMPUTE_COMMAND, step);
}

unsigned PrimeSieveMethod2::compute_for_current_prime(unsigned current_prime)
{
    unsigned current_prime_squared = current_prime * current_prime;
    if (current_prime_squared > MAX_N)
    {
        return 0;
    }
    else
    {
        unsigned current_boolean_id;
        unsigned value;
        unsigned status_register[NUMBER_OF_STATUS_REGISTERS];
        unsigned done;
        unsigned pe_id;

        current_boolean_id = current_prime_squared >> 1;

        for (unsigned i = 0; i < NUMBER_OF_STATUS_REGISTERS; i++)
        {
            status_register[i] = 0;
        }

        do
        {
            unsigned first_offset;

            pe_id = current_boolean_id / (MAX_OFFSET + 1);
            first_offset = current_boolean_id % (MAX_OFFSET + 1);

            compute(pe_id, current_prime, first_offset, MAX_OFFSET);
            status_register[pe_id >> 5] |= (1 << (pe_id & 31));

            current_boolean_id += (((MAX_OFFSET - first_offset) / current_prime) + 1) * current_prime;
            value = (current_boolean_id * 2) + 1;
            last_compute_count++;
        } while (value <= MAX_N && pe_id < NUMBER_OF_PE);

        do
        {
            done = 1;
            for (unsigned i = 0; i < NUMBER_OF_STATUS_REGISTERS; i++)
            {
                if (status_register[i] != 0)
                {
                    unsigned status = read_status_register(i << 5);
                    if (status != 0)
                    {
                        done = 0;
                    }
                    status_register[i] &= status;
                }
            }
        } while (done == 0);
        return 1;
    }
}

unsigned PrimeSieveMethod2::get_next_prime(unsigned current_prime)
{
    unsigned memory_read_data_available = 0;
    while (1)
    {
        unsigned global_row;
        unsigned bit_position;
        unsigned memory_read_data;

        unsigned pe_id;
        unsigned row;

        current_prime += 2;

        global_row = current_prime >> 6;
        bit_position = (current_prime >> 1) & 31;

        if (memory_read_data_available && ((global_row / NUMBER_OF_ROWS) == pe_id) && ((global_row % NUMBER_OF_ROWS) == row))
        {
        }
        else
        {
            memory_read_data_available = 1;
            pe_id = global_row / NUMBER_OF_ROWS;
            row = global_row % NUMBER_OF_ROWS;

            memory_read_data = read_memory_row(pe_id, row);
        }

        if ((memory_read_data & (1 << bit_position)) == 0)
        {
            break;
        }
    }
    return current_prime;
}

void PrimeSieveMethod2::compute_all()
{
    unsigned current_prime = FIRST_PRIME;
    while (compute_for_current_prime(current_prime))
    {
        current_prime = get_next_prime(current_prime);
    }
}

std::stringstream PrimeSieveMethod2::read_memory_n(uint32_t n)
{
    std::stringstream ss;
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
                    unsigned boolean_id = ((((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position) << 1) + 1;
                    if (boolean_id <= n)
                    {
                        if (boolean_id >= FIRST_PRIME)
                        {
                            ss << boolean_id << "\n";
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
    return ss;
}

unsigned PrimeSieveMethod2::get_last_compute_count()
{
    return last_compute_count;
}
