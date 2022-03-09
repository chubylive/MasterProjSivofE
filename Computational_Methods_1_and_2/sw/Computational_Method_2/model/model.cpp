
#include <stdio.h>

#define NUMBER_OF_ROWS 512
#define NUMBER_OF_PE   280
#define FIRST_PRIME    3

#define MAX_OFFSET     ((NUMBER_OF_ROWS << 5) - 1)

#define MAX_N          (((NUMBER_OF_PE * NUMBER_OF_ROWS) << 5) - 1)

unsigned bram [NUMBER_OF_PE][NUMBER_OF_ROWS];

unsigned index_to_value (unsigned index) {
        return ((index << 1) + 1);
}

unsigned value_to_index (unsigned value) {
        return (value >> 1);
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

        for (unsigned pe_id = 0; pe_id < NUMBER_OF_PE; pe_id ++) {
                read_memory (pe_id);
        }
}

void compute (unsigned pe_id, unsigned step, unsigned first_offset, unsigned max_offset) {
        unsigned current_offset;

        current_offset = first_offset;

        do {
                unsigned row;
                unsigned memory_read_data;
                unsigned memory_write_data;

                row = (current_offset >> 5);

                memory_read_data = read_memory_row (pe_id, row);

                memory_write_data = memory_read_data | (1 << (current_offset & 31));

                write_memory_row (pe_id, row, memory_write_data);

                current_offset += step;
        } while (current_offset <= max_offset);
}

unsigned compute_for_current_prime (unsigned current_prime) {
        unsigned current_prime_squared;

        current_prime_squared = current_prime * current_prime;

        if (current_prime_squared > index_to_value (MAX_N)) {
                return 0;
        } else {
                unsigned current_boolean_id;

                current_boolean_id = value_to_index (current_prime_squared);

                do {
                        unsigned pe_id;
                        unsigned first_offset;

                        pe_id = current_boolean_id / (MAX_OFFSET + 1);
                        first_offset = current_boolean_id % (MAX_OFFSET + 1);

                        compute (pe_id, current_prime, first_offset, MAX_OFFSET);

                        current_boolean_id += (((MAX_OFFSET - first_offset) / current_prime) + 1) * current_prime;
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

