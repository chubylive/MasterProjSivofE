#include "PrimeSieveApiCM1.h"
#include "PrimeSieveApiCM2.h"
#include "PrimeSieveApiCM3.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
uint32_t getrow(uint32_t pe, uint32_t in);

uint32_t getrow(uint32_t pe, uint32_t in) {
    return (in / pe / 32);
}

int main(int argc, char **argv)
{
    static const uint32_t max_single_pe = 0x4000;


    uint32_t compute_input = max_single_pe - 1;
    uint32_t compute_input_2Pe = (2 * max_single_pe) - 1;
    uint32_t compute_input_3Pe = (3 * max_single_pe) - 1;
    uint32_t compute_input_4Pe = (4 * max_single_pe) - 1;
    uint32_t compute_input_5Pe = (5 * max_single_pe) - 1;

    system("/home/root/t1/progCM1_2.sh");

    sleep(10);

    PrimeSieveApiCM1 psa_0;
    PrimeSieveApiCM1 psa_1 = PrimeSieveApiCM1(1);
    PrimeSieveApiCM1 psa_2 = PrimeSieveApiCM1(2,   getrow(2,   max_single_pe));
    PrimeSieveApiCM1 psa_3 = PrimeSieveApiCM1(4,   getrow(4,   max_single_pe));
    PrimeSieveApiCM1 psa_4 = PrimeSieveApiCM1(8,   getrow(8,   max_single_pe));
    PrimeSieveApiCM1 psa_5 = PrimeSieveApiCM1(16,  getrow(16,  max_single_pe));
    PrimeSieveApiCM1 psa_6 = PrimeSieveApiCM1(32,  getrow(32,  max_single_pe));
    PrimeSieveApiCM1 psa_7 = PrimeSieveApiCM1(64,  getrow(64,  max_single_pe));
    PrimeSieveApiCM1 psa_8 = PrimeSieveApiCM1(128, getrow(128, max_single_pe));
    PrimeSieveApiCM1 psa_9 = PrimeSieveApiCM1(256, getrow(256, max_single_pe));

    PrimeSieveApiCM1 psa2Pe_1 = PrimeSieveApiCM1(2 * 1);
    PrimeSieveApiCM1 psa2Pe_2 = PrimeSieveApiCM1(2 * 2,   getrow(2 * 2,   2 * max_single_pe));
    PrimeSieveApiCM1 psa2Pe_3 = PrimeSieveApiCM1(2 * 4,   getrow(2 * 4,   2 * max_single_pe));
    PrimeSieveApiCM1 psa2Pe_4 = PrimeSieveApiCM1(2 * 8,   getrow(2 * 8,   2 * max_single_pe));
    PrimeSieveApiCM1 psa2Pe_5 = PrimeSieveApiCM1(2 * 16,  getrow(2 * 16,  2 * max_single_pe));
    PrimeSieveApiCM1 psa2Pe_6 = PrimeSieveApiCM1(2 * 32,  getrow(2 * 32,  2 * max_single_pe));
    PrimeSieveApiCM1 psa2Pe_7 = PrimeSieveApiCM1(2 * 64,  getrow(2 * 64,  2 * max_single_pe));
    PrimeSieveApiCM1 psa2Pe_8 = PrimeSieveApiCM1(2 * 128, getrow(2 * 128, 2 * max_single_pe));

    PrimeSieveApiCM1 psa3Pe_1 = PrimeSieveApiCM1(3 * 1);
    PrimeSieveApiCM1 psa3Pe_2 = PrimeSieveApiCM1(3 * 2,   getrow(3 * 2,   3 * max_single_pe));
    PrimeSieveApiCM1 psa3Pe_3 = PrimeSieveApiCM1(3 * 4,   getrow(3 * 4,   3 * max_single_pe));
    PrimeSieveApiCM1 psa3Pe_4 = PrimeSieveApiCM1(3 * 8,   getrow(3 * 8,   3 * max_single_pe));
    PrimeSieveApiCM1 psa3Pe_5 = PrimeSieveApiCM1(3 * 16,  getrow(3 * 16,  3 * max_single_pe));
    PrimeSieveApiCM1 psa3Pe_6 = PrimeSieveApiCM1(3 * 32,  getrow(3 * 32,  3 * max_single_pe));
    PrimeSieveApiCM1 psa3Pe_7 = PrimeSieveApiCM1(3 * 64,  getrow(3 * 64,  3 * max_single_pe));

    PrimeSieveApiCM1 psa4Pe_1 = PrimeSieveApiCM1(4 * 1);
    PrimeSieveApiCM1 psa4Pe_2 = PrimeSieveApiCM1(4 * 2,   getrow(4 * 2,   4 * max_single_pe));
    PrimeSieveApiCM1 psa4Pe_3 = PrimeSieveApiCM1(4 * 4,   getrow(4 * 4,   4 * max_single_pe));
    PrimeSieveApiCM1 psa4Pe_4 = PrimeSieveApiCM1(4 * 8,   getrow(4 * 8,   4 * max_single_pe));
    PrimeSieveApiCM1 psa4Pe_5 = PrimeSieveApiCM1(4 * 16,  getrow(4 * 16,  4 * max_single_pe));
    PrimeSieveApiCM1 psa4Pe_6 = PrimeSieveApiCM1(4 * 32,  getrow(4 * 32,  4 * max_single_pe));

    PrimeSieveApiCM1 psa5Pe_1 = PrimeSieveApiCM1(5 * 1);
    PrimeSieveApiCM1 psa5Pe_2 = PrimeSieveApiCM1(5 * 2,   getrow(5 * 2,   5 * max_single_pe));
    PrimeSieveApiCM1 psa5Pe_3 = PrimeSieveApiCM1(5 * 4,   getrow(5 * 4,   5 * max_single_pe));
    PrimeSieveApiCM1 psa5Pe_4 = PrimeSieveApiCM1(5 * 8,   getrow(5 * 8,   5 * max_single_pe));
    PrimeSieveApiCM1 psa5Pe_5 = PrimeSieveApiCM1(5 * 16,  getrow(5 * 16,  5 * max_single_pe));
    PrimeSieveApiCM1 psa5Pe_6 = PrimeSieveApiCM1(5 * 32,  getrow(5 * 32,  5 * max_single_pe));

    // PrimeSieveApiCM1 psa3Pe_8 = PrimeSieveApiCM1(3 * 128, getrow(3 * 128, 2 * max_single_pe));
    // PrimeSieveApiCM1 psa2Pe_9 = PrimeSieveApiCM1(2 * 256, getrow(2 * 256, 2 * max_single_pe));

    printf("Compute method 1 %#x using 1   pe and %*d rows took %.*fms.\n", compute_input, 3, 512,                        10, psa_1.time_compute(compute_input));
    printf("Compute method 1 %#x using 2   pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(2,   max_single_pe), 10, psa_2.time_compute(compute_input));
    printf("Compute method 1 %#x using 4   pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(4,   max_single_pe), 10, psa_3.time_compute(compute_input));
    printf("Compute method 1 %#x using 8   pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(8,   max_single_pe), 10, psa_4.time_compute(compute_input));
    printf("Compute method 1 %#x using 16  pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(16,  max_single_pe), 10, psa_5.time_compute(compute_input));
    printf("Compute method 1 %#x using 32  pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(32,  max_single_pe), 10, psa_6.time_compute(compute_input));
    printf("Compute method 1 %#x using 64  pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(64,  max_single_pe), 10, psa_7.time_compute(compute_input));
    printf("Compute method 1 %#x using 128 pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(128, max_single_pe), 10, psa_8.time_compute(compute_input));
    printf("Compute method 1 %#x using 256 pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(256, max_single_pe), 10, psa_9.time_compute(compute_input));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 2   pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, 512,                                10, psa2Pe_1.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 4   pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 2,   2 * max_single_pe), 10, psa2Pe_2.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 8   pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 4,   2 * max_single_pe), 10, psa2Pe_3.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 16  pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 8,   2 * max_single_pe), 10, psa2Pe_4.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 32  pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 16,  2 * max_single_pe), 10, psa2Pe_5.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 64  pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 32,  2 * max_single_pe), 10, psa2Pe_6.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 128 pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 64,  2 * max_single_pe), 10, psa2Pe_7.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 256 pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 128, 2 * max_single_pe), 10, psa2Pe_8.time_compute(compute_input_2Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 3   pe and %*d rows took %.*fms.\n", compute_input_3Pe,   3, 512,                                10, psa3Pe_1.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 6   pe and %*d rows took %.*fms.\n", compute_input_3Pe,   3, getrow(3 * 2,   3 * max_single_pe), 10, psa3Pe_2.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 12  pe and %*d rows took %.*fms.\n", compute_input_3Pe,   3, getrow(3 * 4,   3 * max_single_pe), 10, psa3Pe_3.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 24  pe and %*d rows took %.*fms.\n", compute_input_3Pe,   3, getrow(3 * 8,   3 * max_single_pe), 10, psa3Pe_4.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 48  pe and %*d rows took %.*fms.\n", compute_input_3Pe,  3, getrow(3 * 16,  3 * max_single_pe), 10, psa3Pe_5.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 96  pe and %*d rows took %.*fms.\n", compute_input_3Pe,  3, getrow(3 * 32,  3 * max_single_pe), 10, psa3Pe_6.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 192 pe and %*d rows took %.*fms.\n", compute_input_3Pe,  3, getrow(3 * 64,  3 * max_single_pe), 10, psa3Pe_7.time_compute(compute_input_3Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 4   pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, 512,                                10, psa4Pe_1.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 8   pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 2,   4 * max_single_pe), 10, psa4Pe_2.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 16  pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 4,   4 * max_single_pe), 10, psa4Pe_3.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 32  pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 8,   4 * max_single_pe), 10, psa4Pe_4.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 64  pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 16,  4 * max_single_pe), 10, psa4Pe_5.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 128 pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 32,  4 * max_single_pe), 10, psa4Pe_6.time_compute(compute_input_4Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 5   pe and %*d rows took %.*fms.\n", compute_input_5Pe,   3, 512,                                10, psa5Pe_1.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 10  pe and %*d rows took %.*fms.\n", compute_input_5Pe,   3, getrow(5 * 2,   5 * max_single_pe), 10, psa5Pe_2.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 20  pe and %*d rows took %.*fms.\n", compute_input_5Pe,   3, getrow(5 * 4,   5 * max_single_pe), 10, psa5Pe_3.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 40  pe and %*d rows took %.*fms.\n", compute_input_5Pe,   3, getrow(5 * 8,   5 * max_single_pe), 10, psa5Pe_4.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 80  pe and %*d rows took %.*fms.\n", compute_input_5Pe,  3, getrow(5 * 16,  5 * max_single_pe), 10, psa5Pe_5.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 160 pe and %*d rows took %.*fms.\n", compute_input_5Pe,  3, getrow(5 * 32,  5 * max_single_pe), 10, psa5Pe_6.time_compute(compute_input_5Pe));



    printf("--------------------------\n\n");
    printf("Compute all method 1 took %fms.\n", psa_0.time_compute(0x400000));

    PrimeSieveApiCM2 psacm2_0;
    PrimeSieveApiCM2 psacm2_1 = PrimeSieveApiCM2(1);
    PrimeSieveApiCM2 psacm2_2 = PrimeSieveApiCM2(2,   getrow(2,   max_single_pe));
    PrimeSieveApiCM2 psacm2_3 = PrimeSieveApiCM2(4,   getrow(4,   max_single_pe));
    PrimeSieveApiCM2 psacm2_4 = PrimeSieveApiCM2(8,   getrow(8,   max_single_pe));
    PrimeSieveApiCM2 psacm2_5 = PrimeSieveApiCM2(16,  getrow(16,  max_single_pe));
    PrimeSieveApiCM2 psacm2_6 = PrimeSieveApiCM2(32,  getrow(32,  max_single_pe));
    PrimeSieveApiCM2 psacm2_7 = PrimeSieveApiCM2(64,  getrow(64,  max_single_pe));
    PrimeSieveApiCM2 psacm2_8 = PrimeSieveApiCM2(128, getrow(128, max_single_pe));
    PrimeSieveApiCM2 psacm2_9 = PrimeSieveApiCM2(256, getrow(256, max_single_pe));

    PrimeSieveApiCM2 psacm2_2Pe_1 = PrimeSieveApiCM2(2 * 1);
    PrimeSieveApiCM2 psacm2_2Pe_2 = PrimeSieveApiCM2(2 * 2,   getrow(2 * 2,   2 * max_single_pe));
    PrimeSieveApiCM2 psacm2_2Pe_3 = PrimeSieveApiCM2(2 * 4,   getrow(2 * 4,   2 * max_single_pe));
    PrimeSieveApiCM2 psacm2_2Pe_4 = PrimeSieveApiCM2(2 * 8,   getrow(2 * 8,   2 * max_single_pe));
    PrimeSieveApiCM2 psacm2_2Pe_5 = PrimeSieveApiCM2(2 * 16,  getrow(2 * 16,  2 * max_single_pe));
    PrimeSieveApiCM2 psacm2_2Pe_6 = PrimeSieveApiCM2(2 * 32,  getrow(2 * 32,  2 * max_single_pe));
    PrimeSieveApiCM2 psacm2_2Pe_7 = PrimeSieveApiCM2(2 * 64,  getrow(2 * 64,  2 * max_single_pe));
    PrimeSieveApiCM2 psacm2_2Pe_8 = PrimeSieveApiCM2(2 * 128, getrow(2 * 128, 2 * max_single_pe));

    PrimeSieveApiCM2 psacm2_3Pe_1 = PrimeSieveApiCM2(3 * 1);
    PrimeSieveApiCM2 psacm2_3Pe_2 = PrimeSieveApiCM2(3 * 2,   getrow(3 * 2,   3 * max_single_pe));
    PrimeSieveApiCM2 psacm2_3Pe_3 = PrimeSieveApiCM2(3 * 4,   getrow(3 * 4,   3 * max_single_pe));
    PrimeSieveApiCM2 psacm2_3Pe_4 = PrimeSieveApiCM2(3 * 8,   getrow(3 * 8,   3 * max_single_pe));
    PrimeSieveApiCM2 psacm2_3Pe_5 = PrimeSieveApiCM2(3 * 16,  getrow(3 * 16,  3 * max_single_pe));
    PrimeSieveApiCM2 psacm2_3Pe_6 = PrimeSieveApiCM2(3 * 32,  getrow(3 * 32,  3 * max_single_pe));
    PrimeSieveApiCM2 psacm2_3Pe_7 = PrimeSieveApiCM2(3 * 64,  getrow(3 * 64,  3 * max_single_pe));

    PrimeSieveApiCM2 psacm2_4Pe_1 = PrimeSieveApiCM2(4 * 1);
    PrimeSieveApiCM2 psacm2_4Pe_2 = PrimeSieveApiCM2(4 * 2,   getrow(4 * 2,   4 * max_single_pe));
    PrimeSieveApiCM2 psacm2_4Pe_3 = PrimeSieveApiCM2(4 * 4,   getrow(4 * 4,   4 * max_single_pe));
    PrimeSieveApiCM2 psacm2_4Pe_4 = PrimeSieveApiCM2(4 * 8,   getrow(4 * 8,   4 * max_single_pe));
    PrimeSieveApiCM2 psacm2_4Pe_5 = PrimeSieveApiCM2(4 * 16,  getrow(4 * 16,  4 * max_single_pe));
    PrimeSieveApiCM2 psacm2_4Pe_6 = PrimeSieveApiCM2(4 * 32,  getrow(4 * 32,  4 * max_single_pe));

    PrimeSieveApiCM2 psacm2_5Pe_1 = PrimeSieveApiCM2(5 * 1);
    PrimeSieveApiCM2 psacm2_5Pe_2 = PrimeSieveApiCM2(5 * 2,   getrow(5 * 2,   5 * max_single_pe));
    PrimeSieveApiCM2 psacm2_5Pe_3 = PrimeSieveApiCM2(5 * 4,   getrow(5 * 4,   5 * max_single_pe));
    PrimeSieveApiCM2 psacm2_5Pe_4 = PrimeSieveApiCM2(5 * 8,   getrow(5 * 8,   5 * max_single_pe));
    PrimeSieveApiCM2 psacm2_5Pe_5 = PrimeSieveApiCM2(5 * 16,  getrow(5 * 16,  5 * max_single_pe));
    PrimeSieveApiCM2 psacm2_5Pe_6 = PrimeSieveApiCM2(5 * 32,  getrow(5 * 32,  5 * max_single_pe));

    printf("Compute method 2 %#x using 1   pe and %*d rows took %.*fms.\n", compute_input, 3, 512,                        10, psacm2_1.time_compute(compute_input));
    printf("Compute method 2 %#x using 2   pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(2,   max_single_pe), 10, psacm2_2.time_compute(compute_input));
    printf("Compute method 2 %#x using 4   pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(4,   max_single_pe), 10, psacm2_3.time_compute(compute_input));
    printf("Compute method 2 %#x using 8   pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(8,   max_single_pe), 10, psacm2_4.time_compute(compute_input));
    printf("Compute method 2 %#x using 16  pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(16,  max_single_pe), 10, psacm2_5.time_compute(compute_input));
    printf("Compute method 2 %#x using 32  pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(32,  max_single_pe), 10, psacm2_6.time_compute(compute_input));
    printf("Compute method 2 %#x using 64  pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(64,  max_single_pe), 10, psacm2_7.time_compute(compute_input));
    printf("Compute method 2 %#x using 128 pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(128, max_single_pe), 10, psacm2_8.time_compute(compute_input));
    printf("Compute method 2 %#x using 256 pe and %*d rows took %.*fms.\n", compute_input, 3, getrow(256, max_single_pe), 10, psacm2_9.time_compute(compute_input));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 2   pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, 512,                                10, psacm2_2Pe_1.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 4   pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 2,   2 * max_single_pe), 10, psacm2_2Pe_2.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 8   pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 4,   2 * max_single_pe), 10, psacm2_2Pe_3.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 16  pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 8,   2 * max_single_pe), 10, psacm2_2Pe_4.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 32  pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 16,  2 * max_single_pe), 10, psacm2_2Pe_5.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 64  pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 32,  2 * max_single_pe), 10, psacm2_2Pe_6.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 128 pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 64,  2 * max_single_pe), 10, psacm2_2Pe_7.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 256 pe and %*d rows took %.*fms.\n", compute_input_2Pe, 3, getrow(2 * 128, 2 * max_single_pe), 10, psacm2_2Pe_8.time_compute(compute_input_2Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 3   pe and %*d rows took %.*fms.\n", compute_input_3Pe,   3, 512,                                10, psacm2_3Pe_1.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 6   pe and %*d rows took %.*fms.\n", compute_input_3Pe,   3, getrow(3 * 2,   3 * max_single_pe), 10, psacm2_3Pe_2.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 12  pe and %*d rows took %.*fms.\n", compute_input_3Pe,   3, getrow(3 * 4,   3 * max_single_pe), 10, psacm2_3Pe_3.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 24  pe and %*d rows took %.*fms.\n", compute_input_3Pe,   3, getrow(3 * 8,   3 * max_single_pe), 10, psacm2_3Pe_4.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 48  pe and %*d rows took %.*fms.\n", compute_input_3Pe,  3, getrow(3 * 16,  3 * max_single_pe), 10, psacm2_3Pe_5.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 96  pe and %*d rows took %.*fms.\n", compute_input_3Pe,  3, getrow(3 * 32,  3 * max_single_pe), 10, psacm2_3Pe_6.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 192 pe and %*d rows took %.*fms.\n", compute_input_3Pe,  3, getrow(3 * 64,  3 * max_single_pe), 10, psacm2_3Pe_7.time_compute(compute_input_3Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 4   pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, 512,                                10, psacm2_4Pe_1.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 8   pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 2,   4 * max_single_pe), 10, psacm2_4Pe_2.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 16  pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 4,   4 * max_single_pe), 10, psacm2_4Pe_3.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 32  pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 8,   4 * max_single_pe), 10, psacm2_4Pe_4.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 64  pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 16,  4 * max_single_pe), 10, psacm2_4Pe_5.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 128 pe and %*d rows took %.*fms.\n", compute_input_4Pe, 3, getrow(4 * 32,  4 * max_single_pe), 10, psacm2_4Pe_6.time_compute(compute_input_4Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 5   pe and %*d rows took %.*fms.\n", compute_input_5Pe,   3, 512,                                10, psacm2_5Pe_1.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 10  pe and %*d rows took %.*fms.\n", compute_input_5Pe,   3, getrow(5 * 2,   5 * max_single_pe), 10, psacm2_5Pe_2.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 20  pe and %*d rows took %.*fms.\n", compute_input_5Pe,   3, getrow(5 * 4,   5 * max_single_pe), 10, psacm2_5Pe_3.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 40  pe and %*d rows took %.*fms.\n", compute_input_5Pe,   3, getrow(5 * 8,   5 * max_single_pe), 10, psacm2_5Pe_4.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 80  pe and %*d rows took %.*fms.\n", compute_input_5Pe,  3, getrow(5 * 16,  5 * max_single_pe), 10, psacm2_5Pe_5.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 160 pe and %*d rows took %.*fms.\n", compute_input_5Pe,  3, getrow(5 * 32,  5 * max_single_pe), 10, psacm2_5Pe_6.time_compute(compute_input_5Pe));



    printf("--------------------------\n\n");
    printf("Compute method 2  all took %fms.\n", psacm2_0.time_compute(0x400000));

    system("/home/root/t1/progCM3.sh");
    sleep(10);
    PrimeSieveApiCM3 psacm3_0;
    PrimeSieveApiCM3 psacm3_1 = PrimeSieveApiCM3(1);
    PrimeSieveApiCM3 psacm3_2 = PrimeSieveApiCM3(2,   getrow(2,   max_single_pe));
    PrimeSieveApiCM3 psacm3_3 = PrimeSieveApiCM3(4,   getrow(4,   max_single_pe));
    PrimeSieveApiCM3 psacm3_4 = PrimeSieveApiCM3(8,   getrow(8,   max_single_pe));
    PrimeSieveApiCM3 psacm3_5 = PrimeSieveApiCM3(16,  getrow(16,  max_single_pe));
    PrimeSieveApiCM3 psacm3_6 = PrimeSieveApiCM3(32,  getrow(32,  max_single_pe));
    PrimeSieveApiCM3 psacm3_7 = PrimeSieveApiCM3(64,  getrow(64,  max_single_pe));
    PrimeSieveApiCM3 psacm3_8 = PrimeSieveApiCM3(128, getrow(128, max_single_pe));
    PrimeSieveApiCM3 psacm3_9 = PrimeSieveApiCM3(256, getrow(256, max_single_pe));

    PrimeSieveApiCM3 psacm3_2Pe_1 = PrimeSieveApiCM3(2 * 1);
    PrimeSieveApiCM3 psacm3_2Pe_2 = PrimeSieveApiCM3(2 * 2,   getrow(2 * 2,   2 * max_single_pe));
    PrimeSieveApiCM3 psacm3_2Pe_3 = PrimeSieveApiCM3(2 * 4,   getrow(2 * 4,   2 * max_single_pe));
    PrimeSieveApiCM3 psacm3_2Pe_4 = PrimeSieveApiCM3(2 * 8,   getrow(2 * 8,   2 * max_single_pe));
    PrimeSieveApiCM3 psacm3_2Pe_5 = PrimeSieveApiCM3(2 * 16,  getrow(2 * 16,  2 * max_single_pe));
    PrimeSieveApiCM3 psacm3_2Pe_6 = PrimeSieveApiCM3(2 * 32,  getrow(2 * 32,  2 * max_single_pe));
    PrimeSieveApiCM3 psacm3_2Pe_7 = PrimeSieveApiCM3(2 * 64,  getrow(2 * 64,  2 * max_single_pe));
    PrimeSieveApiCM3 psacm3_2Pe_8 = PrimeSieveApiCM3(2 * 128, getrow(2 * 128, 2 * max_single_pe));

    PrimeSieveApiCM3 psacm3_3Pe_1 = PrimeSieveApiCM3(3 * 1);
    PrimeSieveApiCM3 psacm3_3Pe_2 = PrimeSieveApiCM3(3 * 2,   getrow(3 * 2,   3 * max_single_pe));
    PrimeSieveApiCM3 psacm3_3Pe_3 = PrimeSieveApiCM3(3 * 4,   getrow(3 * 4,   3 * max_single_pe));
    PrimeSieveApiCM3 psacm3_3Pe_4 = PrimeSieveApiCM3(3 * 8,   getrow(3 * 8,   3 * max_single_pe));
    PrimeSieveApiCM3 psacm3_3Pe_5 = PrimeSieveApiCM3(3 * 16,  getrow(3 * 16,  3 * max_single_pe));
    PrimeSieveApiCM3 psacm3_3Pe_6 = PrimeSieveApiCM3(3 * 32,  getrow(3 * 32,  3 * max_single_pe));
    PrimeSieveApiCM3 psacm3_3Pe_7 = PrimeSieveApiCM3(3 * 64,  getrow(3 * 64,  3 * max_single_pe));

    PrimeSieveApiCM3 psacm3_4Pe_1 = PrimeSieveApiCM3(4 * 1);
    PrimeSieveApiCM3 psacm3_4Pe_2 = PrimeSieveApiCM3(4 * 2,   getrow(4 * 2,   4 * max_single_pe));
    PrimeSieveApiCM3 psacm3_4Pe_3 = PrimeSieveApiCM3(4 * 4,   getrow(4 * 4,   4 * max_single_pe));
    PrimeSieveApiCM3 psacm3_4Pe_4 = PrimeSieveApiCM3(4 * 8,   getrow(4 * 8,   4 * max_single_pe));
    PrimeSieveApiCM3 psacm3_4Pe_5 = PrimeSieveApiCM3(4 * 16,  getrow(4 * 16,  4 * max_single_pe));
    PrimeSieveApiCM3 psacm3_4Pe_6 = PrimeSieveApiCM3(4 * 32,  getrow(4 * 32,  4 * max_single_pe));

    PrimeSieveApiCM3 psacm3_5Pe_1 = PrimeSieveApiCM3(5 * 1);
    PrimeSieveApiCM3 psacm3_5Pe_2 = PrimeSieveApiCM3(5 * 2,   getrow(5 * 2,   5 * max_single_pe));
    PrimeSieveApiCM3 psacm3_5Pe_3 = PrimeSieveApiCM3(5 * 4,   getrow(5 * 4,   5 * max_single_pe));
    PrimeSieveApiCM3 psacm3_5Pe_4 = PrimeSieveApiCM3(5 * 8,   getrow(5 * 8,   5 * max_single_pe));
    PrimeSieveApiCM3 psacm3_5Pe_5 = PrimeSieveApiCM3(5 * 16,  getrow(5 * 16,  5 * max_single_pe));
    PrimeSieveApiCM3 psacm3_5Pe_6 = PrimeSieveApiCM3(5 * 32,  getrow(5 * 32,  5 * max_single_pe));

    printf("Compute method 3 %#x using 1   pe and %*d rows took %.*f ms\n", compute_input, 3, 512,                        10, psacm3_1.time_compute(compute_input));
    printf("Compute method 3 %#x using 2   pe and %*d rows took %.*f ms\n", compute_input, 3, getrow(2,   max_single_pe), 10, psacm3_2.time_compute(compute_input));
    printf("Compute method 3 %#x using 4   pe and %*d rows took %.*f ms\n", compute_input, 3, getrow(4,   max_single_pe), 10, psacm3_3.time_compute(compute_input));
    printf("Compute method 3 %#x using 8   pe and %*d rows took %.*f ms\n", compute_input, 3, getrow(8,   max_single_pe), 10, psacm3_4.time_compute(compute_input));
    printf("Compute method 3 %#x using 16  pe and %*d rows took %.*f ms\n", compute_input, 3, getrow(16,  max_single_pe), 10, psacm3_5.time_compute(compute_input));
    printf("Compute method 3 %#x using 32  pe and %*d rows took %.*f ms\n", compute_input, 3, getrow(32,  max_single_pe), 10, psacm3_6.time_compute(compute_input));
    printf("Compute method 3 %#x using 64  pe and %*d rows took %.*f ms\n", compute_input, 3, getrow(64,  max_single_pe), 10, psacm3_7.time_compute(compute_input));
    printf("Compute method 3 %#x using 128 pe and %*d rows took %.*f ms\n", compute_input, 3, getrow(128, max_single_pe), 10, psacm3_8.time_compute(compute_input));
    printf("Compute method 3 %#x using 256 pe and %*d rows took %.*f ms\n", compute_input, 3, getrow(256, max_single_pe), 10, psacm3_9.time_compute(compute_input));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 2   pe and %*d rows took %.*f ms\n", compute_input_2Pe, 3, 512,                                10, psacm3_2Pe_1.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 4   pe and %*d rows took %.*f ms\n", compute_input_2Pe, 3, getrow(2 * 2,   2 * max_single_pe), 10, psacm3_2Pe_2.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 8   pe and %*d rows took %.*f ms\n", compute_input_2Pe, 3, getrow(2 * 4,   2 * max_single_pe), 10, psacm3_2Pe_3.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 16  pe and %*d rows took %.*f ms\n", compute_input_2Pe, 3, getrow(2 * 8,   2 * max_single_pe), 10, psacm3_2Pe_4.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 32  pe and %*d rows took %.*f ms\n", compute_input_2Pe, 3, getrow(2 * 16,  2 * max_single_pe), 10, psacm3_2Pe_5.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 64  pe and %*d rows took %.*f ms\n", compute_input_2Pe, 3, getrow(2 * 32,  2 * max_single_pe), 10, psacm3_2Pe_6.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 128 pe and %*d rows took %.*f ms\n", compute_input_2Pe, 3, getrow(2 * 64,  2 * max_single_pe), 10, psacm3_2Pe_7.time_compute(compute_input_2Pe));
    printf("Compute method 1 %#x using 256 pe and %*d rows took %.*f ms\n", compute_input_2Pe, 3, getrow(2 * 128, 2 * max_single_pe), 10, psacm3_2Pe_8.time_compute(compute_input_2Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 3   pe and %*d rows took %.*f ms\n", compute_input_3Pe,   3, 512,                                10, psacm3_3Pe_1.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 6   pe and %*d rows took %.*f ms\n", compute_input_3Pe,   3, getrow(3 * 2,   3 * max_single_pe), 10, psacm3_3Pe_2.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 12  pe and %*d rows took %.*f ms\n", compute_input_3Pe,   3, getrow(3 * 4,   3 * max_single_pe), 10, psacm3_3Pe_3.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 24  pe and %*d rows took %.*f ms\n", compute_input_3Pe,   3, getrow(3 * 8,   3 * max_single_pe), 10, psacm3_3Pe_4.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 48  pe and %*d rows took %.*f ms\n", compute_input_3Pe,  3, getrow(3 * 16,  3 * max_single_pe), 10, psacm3_3Pe_5.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 96  pe and %*d rows took %.*f ms\n", compute_input_3Pe,  3, getrow(3 * 32,  3 * max_single_pe), 10, psacm3_3Pe_6.time_compute(compute_input_3Pe));
    printf("Compute method 1 %#x using 192 pe and %*d rows took %.*f ms\n", compute_input_3Pe,  3, getrow(3 * 64,  3 * max_single_pe), 10, psacm3_3Pe_7.time_compute(compute_input_3Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 4   pe and %*d rows took %.*f ms\n", compute_input_4Pe, 3, 512,                                10, psacm3_4Pe_1.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 8   pe and %*d rows took %.*f ms\n", compute_input_4Pe, 3, getrow(4 * 2,   4 * max_single_pe), 10, psacm3_4Pe_2.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 16  pe and %*d rows took %.*f ms\n", compute_input_4Pe, 3, getrow(4 * 4,   4 * max_single_pe), 10, psacm3_4Pe_3.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 32  pe and %*d rows took %.*f ms\n", compute_input_4Pe, 3, getrow(4 * 8,   4 * max_single_pe), 10, psacm3_4Pe_4.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 64  pe and %*d rows took %.*f ms\n", compute_input_4Pe, 3, getrow(4 * 16,  4 * max_single_pe), 10, psacm3_4Pe_5.time_compute(compute_input_4Pe));
    printf("Compute method 1 %#x using 128 pe and %*d rows took %.*f ms\n", compute_input_4Pe, 3, getrow(4 * 32,  4 * max_single_pe), 10, psacm3_4Pe_6.time_compute(compute_input_4Pe));
    printf("--------------------------\n\n");
    printf("Compute method 1 %#x using 5   pe and %*d rows took %.*f ms\n", compute_input_5Pe,   3, 512,                                10, psacm3_5Pe_1.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 10  pe and %*d rows took %.*f ms\n", compute_input_5Pe,   3, getrow(5 * 2,   5 * max_single_pe), 10, psacm3_5Pe_2.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 20  pe and %*d rows took %.*f ms\n", compute_input_5Pe,   3, getrow(5 * 4,   5 * max_single_pe), 10, psacm3_5Pe_3.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 40  pe and %*d rows took %.*f ms\n", compute_input_5Pe,   3, getrow(5 * 8,   5 * max_single_pe), 10, psacm3_5Pe_4.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 80  pe and %*d rows took %.*f ms\n", compute_input_5Pe,  3, getrow(5 * 16,  5 * max_single_pe), 10, psacm3_5Pe_5.time_compute(compute_input_5Pe));
    printf("Compute method 1 %#x using 160 pe and %*d rows took %.*f ms\n", compute_input_5Pe,  3, getrow(5 * 32,  5 * max_single_pe), 10, psacm3_5Pe_6.time_compute(compute_input_5Pe));

    printf("--------------------------\n\n");
    printf("Compute method 3  all took %fms.\n", psacm3_0.time_compute(0x400000));

    // psa_0.clear_memory_all();
    // psa_0.compute_all();
    // psa_0.read_memory_all();
    return 0;
}
