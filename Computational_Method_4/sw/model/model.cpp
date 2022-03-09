
#include <stdio.h>

#define NUMBER_OF_ROWS 512
#define NUMBER_OF_PE   256
#define FIRST_PRIME    7

#define MAX_OFFSET     (((NUMBER_OF_ROWS << 2) - 1) * 30 + 29)

#define MAX_N          ((((NUMBER_OF_PE * NUMBER_OF_ROWS) << 2) - 1) * 30 + 29)

unsigned bram [NUMBER_OF_PE][NUMBER_OF_ROWS];

unsigned delta [8] = {6, 4, 2, 4, 2, 4, 6, 2};

unsigned index_to_value (unsigned index) {
        unsigned q = index >> 3;
        unsigned r;

        switch (index & 7) {
                case 0 : {
                        r = 1;
                        break;
                }

                case 1 : {
                        r = 7;
                        break;
                }

                case 2 : {
                        r = 11;
                        break;
                }

                case 3 : {
                        r = 13;
                        break;
                }

                case 4 : {
                        r = 17;
                        break;
                }

                case 5 : {
                        r = 19;
                        break;
                }

                case 6 : {
                        r = 23;
                        break;
                }

                case 7 : {
                        r = 29;
                }
        }

        return (30 * q + r);
}

unsigned value_to_index (unsigned value) {
        unsigned q = value / 30;
        unsigned r;

        switch (value % 30) {
                case 1 : {
                        r = 0;
                        break;
                }

                case 7 : {
                        r = 1;
                        break;
                }

                case 11 : {
                        r = 2;
                        break;
                }

                case 13 : {
                        r = 3;
                        break;
                }

                case 17 : {
                        r = 4;
                        break;
                }

                case 19 : {
                        r = 5;
                        break;
                }

                case 23 : {
                        r = 6;
                        break;
                }

                case 29 : {
                        r = 7;
                }
        }

        return ((q << 3) | r);
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
        printf ("5\n");

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

                unsigned r;

                switch (current_offset_r) {
                        case 1 : {
                                r = 0;
                                break;
                        }

                        case 7 : {
                                r = 1;
                                break;
                        }

                        case 11 : {
                                r = 2;
                                break;
                        }

                        case 13 : {
                                r = 3;
                                break;
                        }

                        case 17 : {
                                r = 4;
                                break;
                        }

                        case 19 : {
                                r = 5;
                                break;
                        }

                        case 23 : {
                                r = 6;
                                break;
                        }

                        case 29 : {
                                r = 7;
                        }
                }

                row = (current_offset_q >> 2);

                memory_read_data = read_memory_row (pe_id, row);

                memory_write_data = memory_read_data | (1 << (((current_offset_q & 3) << 3) + r));

                write_memory_row (pe_id, row, memory_write_data);

                switch (step_delta_index) {
                        case 2 :
                        case 4 :
                        case 7 : {
                                current_offset_q += (step_q << 1);

                                switch (step_r) {
                                        case 1 : {
                                                current_offset_r += 2;

                                                break;
                                        }

                                        case 7 : {
                                                current_offset_r += 14;

                                                break;
                                        }

                                        case 11 : {
                                                current_offset_r += 22;

                                                break;
                                        }

                                        case 13 : {
                                                current_offset_r += 26;

                                                break;
                                        }

                                        case 17 : {
                                                current_offset_q += 1;
                                                current_offset_r += 4;

                                                break;
                                        }

                                        case 19 : {
                                                current_offset_q += 1;
                                                current_offset_r += 8;

                                                break;
                                        }

                                        case 23 : {
                                                current_offset_q += 1;
                                                current_offset_r += 16;

                                                break;
                                        }

                                        case 29 : {
                                                current_offset_q += 1;
                                                current_offset_r += 28;
                                        }
                                }

                                break;
                        }

                        case 1 :
                        case 3 :
                        case 5 : {
                                current_offset_q += (step_q << 2);

                                switch (step_r) {
                                        case 1 : {
                                                current_offset_r += 4;

                                                break;
                                        }

                                        case 7 : {
                                                current_offset_r += 28;

                                                break;
                                        }

                                        case 11 : {
                                                current_offset_q += 1;
                                                current_offset_r += 14;

                                                break;
                                        }

                                        case 13 : {
                                                current_offset_q += 1;
                                                current_offset_r += 22;

                                                break;
                                        }

                                        case 17 : {
                                                current_offset_q += 2;
                                                current_offset_r += 8;

                                                break;
                                        }

                                        case 19 : {
                                                current_offset_q += 2;
                                                current_offset_r += 16;

                                                break;
                                        }

                                        case 23 : {
                                                current_offset_q += 3;
                                                current_offset_r += 2;

                                                break;
                                        }

                                        case 29 : {
                                                current_offset_q += 3;
                                                current_offset_r += 26;
                                        }
                                }

                                break;
                        }

                        case 0 :
                        case 6 : {
                                current_offset_q += (step_q << 2) + (step_q << 1);

                                switch (step_r) {
                                        case 1 : {
                                                current_offset_r += 6;

                                                break;
                                        }

                                        case 7 : {
                                                current_offset_q += 1;
                                                current_offset_r += 12;

                                                break;
                                        }

                                        case 11 : {
                                                current_offset_q += 2;
                                                current_offset_r += 6;

                                                break;
                                        }

                                        case 13 : {
                                                current_offset_q += 2;
                                                current_offset_r += 18;

                                                break;
                                        }

                                        case 17 : {
                                                current_offset_q += 3;
                                                current_offset_r += 12;

                                                break;
                                        }

                                        case 19 : {
                                                current_offset_q += 3;
                                                current_offset_r += 24;

                                                break;
                                        }

                                        case 23 : {
                                                current_offset_q += 4;
                                                current_offset_r += 18;

                                                break;
                                        }

                                        case 29 : {
                                                current_offset_q += 5;
                                                current_offset_r += 24;
                                        }
                                }
                        }
                }

                if (current_offset_r > 29) {
                        current_offset_q ++;
                        current_offset_r -= 30;
                }

                step_delta_index = (step_delta_index + 1) % 8;
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

                switch (current_prime % 30) {
                        case 1 : {
                                current_prime_delta_index = 0;
                                break;
                        }

                        case 7 : {
                                current_prime_delta_index = 1;
                                break;
                        }

                        case 11 : {
                                current_prime_delta_index = 2;
                                break;
                        }

                        case 13 : {
                                current_prime_delta_index = 3;
                                break;
                        }

                        case 17 : {
                                current_prime_delta_index = 4;
                                break;
                        }

                        case 19 : {
                                current_prime_delta_index = 5;
                                break;
                        }

                        case 23 : {
                                current_prime_delta_index = 6;
                                break;
                        }

                        case 29 : {
                                current_prime_delta_index = 7;
                        }
                }

                do {
                        unsigned pe_id;
                        unsigned first_offset;

                        unsigned i;
                        unsigned j;
                        unsigned k;
                        unsigned l;

                        pe_id = current_boolean_id / (MAX_OFFSET + 1);
                        first_offset = current_boolean_id % (MAX_OFFSET + 1);

                        compute (pe_id, current_prime / 30, current_prime % 30, current_prime_delta_index, first_offset / 30, first_offset % 30, (NUMBER_OF_ROWS << 2) - 1, 29);

                        i = (MAX_OFFSET - first_offset) / current_prime;
                        j = i / 30;
                        k = i % 30;
                        l = 30 * j;

                        for (unsigned m = 0; m < 8; m ++) {
                                l += delta [current_prime_delta_index];

                                if (k < delta [current_prime_delta_index]) {
                                        current_prime_delta_index = (current_prime_delta_index + 1) % 8;

                                        break;
                                }

                                k -= delta [current_prime_delta_index];
                                current_prime_delta_index = (current_prime_delta_index + 1) % 8;
                        }

                        current_boolean_id += (l * current_prime);
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

