
#include <stdio.h>

#define NUMBER_OF_ROWS 512
#define NUMBER_OF_PE   256
#define FIRST_PRIME    5

#define MAX_OFFSET     (((NUMBER_OF_ROWS << 4) - 1) * 6 + 5)

#define MAX_N          ((((NUMBER_OF_PE * NUMBER_OF_ROWS) << 4) - 1) * 6 + 5)

unsigned bram [NUMBER_OF_PE][NUMBER_OF_ROWS];

unsigned delta [2] = {4, 2};

unsigned index_to_value (unsigned index) {
        unsigned q = index >> 1;
        unsigned r = ((index & 1) == 0) ? 1 : 5;

        return (6 * q + r);
}

unsigned value_to_index (unsigned value) {
        unsigned q = value / 6;
        unsigned r = ((value % 6) == 1) ? 0 : 1;

        return ((q << 1) | r);
}

void clear_memory (unsigned pe_id) {
        for (unsigned row = 0; row < NUMBER_OF_ROWS; row ++) {
                bram [pe_id][row] = 0;
        }
}

void clear_memory_all (void) {
        for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                clear_memory (pe_id);
        }
}

void write_memory_row (unsigned pe_id, unsigned row, unsigned memory_write_data) {
        bram [pe_id][row] = memory_write_data;
}

unsigned read_memory_row (unsigned pe_id, unsigned row) {
        unsigned memory_read_data;

        memory_read_data = bram [pe_id][row];

        return memory_read_data;
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

        for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                read_memory (pe_id);
        }
}

void compute (unsigned pe_id, unsigned step_q, unsigned step_r, unsigned step_delta_index, unsigned first_offset_q, unsigned first_offset_r, unsigned max_offset_q, unsigned max_offset_r) {
        unsigned current_offset_q;
        unsigned current_offset_r;

        current_offset_q = first_offset_q;
        current_offset_r = first_offset_r;

        do {
                unsigned row;
                unsigned memory_read_data;
                unsigned memory_write_data;

                row = (current_offset_q >> 4);

                memory_read_data = read_memory_row (pe_id, row);

                memory_write_data = memory_read_data | (1 << (((current_offset_q & 15) << 1) + ((current_offset_r == 1) ? 0 : 1)));

                write_memory_row (pe_id, row, memory_write_data);

                if (step_delta_index == 0) {
                        current_offset_q += (step_q << 2);

                        if (step_r == 1) {
                                current_offset_r += 4;
                        } else {
                                current_offset_q += 3;
                                current_offset_r += 2;
                        }
                } else {
                        current_offset_q += (step_q << 1);

                        if (step_r == 1) {
                                current_offset_r += 2;
                        } else {
                                current_offset_q += 1;
                                current_offset_r += 4;
                        }
                }

                if (current_offset_r > 5) {
                        current_offset_q ++;
                        current_offset_r -= 6;
                }

                step_delta_index = 1 - step_delta_index;
        } while ((current_offset_q < max_offset_q) || ((current_offset_q == max_offset_q) && (current_offset_r <= max_offset_r)));
}

unsigned compute_for_current_prime (unsigned current_prime) {
        unsigned current_prime_squared;

        current_prime_squared = current_prime * current_prime;

        if (current_prime_squared > MAX_N) {
                return 0;
        } else {
                unsigned current_boolean_id;
                unsigned current_prime_delta_index;

                current_boolean_id = current_prime_squared;

                current_prime_delta_index = ((current_prime % 6) == 1) ? 0 : 1;

                do {
                        unsigned pe_id;
                        unsigned first_offset;

                        unsigned i;
                        unsigned j;
                        unsigned k;

                        pe_id = current_boolean_id / (MAX_OFFSET + 1);
                        first_offset = current_boolean_id % (MAX_OFFSET + 1);

                        compute (pe_id, current_prime / 6, current_prime % 6, current_prime_delta_index, first_offset / 6, first_offset % 6, (NUMBER_OF_ROWS << 4) - 1, 5);

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
        clear_memory_all ();
        compute_all      ();
        read_memory_all  ();

        return 0;
}

