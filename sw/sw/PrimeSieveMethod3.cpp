#include "PrimeSieveMethod3.h"

PrimeSieveMethod3::PrimeSieveMethod3() : PrimeSieveBase()
{
    last_compute_count = 0U;
    FIRST_PRIME = 5;
    MAX_OFFSET = (((NUMBER_OF_ROWS << 4) - 1) * 6 + 5);
    MAX_N = ((((NUMBER_OF_PE * NUMBER_OF_ROWS) << 4) - 1) * 6 + 5);
}

PrimeSieveMethod3::~PrimeSieveMethod3()
{
}

void PrimeSieveMethod3::reconfig(uint16_t pe, uint16_t rows, uint32_t n)
{
    last_compute_count = 0U;
    NUMBER_OF_PE = (pe <= 280 ? (pe > 0 ? pe : 1) : 280);
    NUMBER_OF_ROWS = (rows <= 512 ? (rows > 0 ? rows : 1) : 512);
    MAX_OFFSET = (((NUMBER_OF_ROWS << 4) - 1) * 6 + 5);
    MAX_N = (n == 0 ? ((((NUMBER_OF_PE * NUMBER_OF_ROWS) << 4) - 1) * 6 + 5) : n);
    NUMBER_OF_STATUS_REGISTERS = ((NUMBER_OF_PE / 32) + (((NUMBER_OF_PE % 32) == 0) ? 0 : 1));
}

unsigned PrimeSieveMethod3::index_to_value(unsigned index)
{
    unsigned q = index >> 1;
    unsigned r = ((index & 1) == 0) ? 1 : 5;

    return (6 * q + r);
}

unsigned PrimeSieveMethod3::value_to_index(unsigned value)
{
    unsigned q = value / 6;
    unsigned r = ((value % 6) == 1) ? 0 : 1;

    return ((q << 1) | r);
}

void PrimeSieveMethod3::write_command_register_1(unsigned pe_id, unsigned command, unsigned step_q, unsigned step_r, unsigned step_delta_index, unsigned first_offset_r, unsigned max_offset_r)
{
    unsigned *vaddress = pe_command_register_vaddress(pe_id, 1);
    *vaddress = command | (step_q << 4) | (step_r << 16) | (step_delta_index << 20) | (first_offset_r << 24) | (max_offset_r << 28);
}

void PrimeSieveMethod3::read_memory(unsigned pe_id)
{
    for (unsigned row = 0; row < NUMBER_OF_ROWS; row++)
    {
        unsigned memory_read_data = read_memory_row(pe_id, row);
        for (unsigned bit_position = 0; bit_position < 32; bit_position++)
        {
            if ((memory_read_data & (1 << bit_position)) == 0)
            {
                unsigned boolean_id = ((((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position) << 1) + 1;
                unsigned value = index_to_value(boolean_id);
                if (value >= FIRST_PRIME)
                {
                    printf("%u\n", boolean_id);
                }
            }
        }
    }
}

void PrimeSieveMethod3::compute(unsigned pe_id, unsigned step_q, unsigned step_r, unsigned step_delta_index, unsigned first_offset_q, unsigned first_offset_r, unsigned max_offset_q, unsigned max_offset_r)
{
    write_command_register_0(pe_id, first_offset_q, max_offset_q);
    write_command_register_1(pe_id, PE_COMPUTE_COMMAND, step_q, step_r, step_delta_index, first_offset_r, max_offset_r);
}

void PrimeSieveMethod3::compute(unsigned pe_id, unsigned step, unsigned first_offset, unsigned max_offset)
{
}

unsigned PrimeSieveMethod3::compute_for_current_prime(unsigned current_prime)
{
    unsigned current_prime_squared = current_prime * current_prime;
    if (current_prime_squared > MAX_N)
    {
        return 0;
    }
    else
    {
        unsigned current_boolean_id;
        unsigned current_prime_delta_index;
        unsigned status_register[NUMBER_OF_STATUS_REGISTERS];
        unsigned done;
        unsigned pe_id;

        current_boolean_id = current_prime_squared;
        current_prime_delta_index = ((current_prime % 6) == 1) ? 0 : 1;

        for (unsigned i = 0; i < NUMBER_OF_STATUS_REGISTERS; i++)
        {
            status_register[i] = 0;
        }

        do
        {
            unsigned first_offset;

            unsigned i;
            unsigned j;
            unsigned k;

            pe_id = current_boolean_id / (MAX_OFFSET + 1);
            first_offset = current_boolean_id % (MAX_OFFSET + 1);

            compute(pe_id, current_prime / 6, (current_prime % 6) >> 2, current_prime_delta_index, first_offset / 6, (first_offset % 6) >> 2, (NUMBER_OF_ROWS << 4) - 1, 1);
            status_register[pe_id >> 5] |= (1 << (pe_id & 31));

            i = (MAX_OFFSET - first_offset) / current_prime;
            j = i / 6;
            k = i % 6;

            if (k >= delta[current_prime_delta_index])
            {
                current_boolean_id += (6 * (j + 1) * current_prime);
            }
            else
            {
                current_boolean_id += ((6 * j + delta[current_prime_delta_index]) * current_prime);
                current_prime_delta_index = 1 - current_prime_delta_index;
            }
            last_compute_count++;
        } while (current_boolean_id <= MAX_N && pe_id < NUMBER_OF_PE);

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

unsigned PrimeSieveMethod3::get_next_prime(unsigned current_prime)
{
}

unsigned PrimeSieveMethod3::get_next_index(unsigned current_index)
{
    unsigned memory_read_data_available = 0;
    while (1)
    {
        unsigned global_row;
        unsigned bit_position;
        unsigned memory_read_data;

        unsigned pe_id;
        unsigned row;

        current_index++;

        global_row = current_index >> 5;
        bit_position = current_index & 31;

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
    return current_index;
}

void PrimeSieveMethod3::compute_all()
{
    unsigned current_prime = FIRST_PRIME;
    unsigned current_index = value_to_index(current_prime);
    while (compute_for_current_prime(current_prime))
    {
        current_index = get_next_index(current_index);
        current_prime = index_to_value(current_index);
    }
}

std::stringstream PrimeSieveMethod3::read_memory_n(uint32_t n)
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
                    unsigned boolean_id = ((pe_id * NUMBER_OF_ROWS + row) << 5) + bit_position;
                    unsigned value = index_to_value(boolean_id);
                    if (value <= n)
                    {
                        if (value >= FIRST_PRIME)
                        {
                            ss << value << "\n";
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

unsigned PrimeSieveMethod3::get_last_compute_count()
{
    return last_compute_count;
}
