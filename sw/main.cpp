#include "PrimeSieveApi.h"
#include <time.h>
#include <sys/time.h>

#define getrow(pe, in) (in/pe/32)

int main(int argc, char **argv)
{
    static const uint32_t max_single_pe = 0x4000;
    uint32_t compute_input = max_single_pe - 1;

    PrimeSieveApi psa_0;
    PrimeSieveApi psa_1 = PrimeSieveApi(1);
    PrimeSieveApi psa_2 = PrimeSieveApi(2,   getrow(2,   max_single_pe));
    PrimeSieveApi psa_3 = PrimeSieveApi(4,   getrow(4,   max_single_pe));
    PrimeSieveApi psa_4 = PrimeSieveApi(8,   getrow(8,   max_single_pe));
    PrimeSieveApi psa_5 = PrimeSieveApi(16,  getrow(16,  max_single_pe));
    PrimeSieveApi psa_6 = PrimeSieveApi(32,  getrow(32,  max_single_pe));
    PrimeSieveApi psa_7 = PrimeSieveApi(64,  getrow(64,  max_single_pe));
    PrimeSieveApi psa_8 = PrimeSieveApi(128, getrow(128, max_single_pe));
    PrimeSieveApi psa_9 = PrimeSieveApi(256, getrow(256, max_single_pe));

    printf("Compute %#x using 1   pe and %*d rows took %*.*fms.\n", compute_input, 3, 1,                          10, psa_1.time_compute(compute_input));
    printf("Compute %#x using 2   pe and %*d rows took %*.*fms.\n", compute_input, 3, getrow(2,   max_single_pe), 10, psa_2.time_compute(compute_input));
    printf("Compute %#x using 4   pe and %*d rows took %*.*fms.\n", compute_input, 3, getrow(4,   max_single_pe), 10, psa_3.time_compute(compute_input));
    printf("Compute %#x using 8   pe and %*d rows took %*.*fms.\n", compute_input, 3, getrow(8,   max_single_pe), 10, psa_4.time_compute(compute_input));
    printf("Compute %#x using 16  pe and %*d rows took %*.*fms.\n", compute_input, 3, getrow(16,  max_single_pe), 10, psa_5.time_compute(compute_input));
    printf("Compute %#x using 32  pe and %*d rows took %*.*fms.\n", compute_input, 3, getrow(32,  max_single_pe), 10, psa_6.time_compute(compute_input));
    printf("Compute %#x using 64  pe and %*d rows took %*.*fms.\n", compute_input, 3, getrow(64,  max_single_pe), 10, psa_7.time_compute(compute_input));
    printf("Compute %#x using 128 pe and %*d rows took %*.*fms.\n", compute_input, 3, getrow(128, max_single_pe), 10, psa_8.time_compute(compute_input));
    printf("Compute %#x using 256 pe and %*d rows took %*.*fms.\n", compute_input, 3, getrow(256, max_single_pe), 10, psa_9.time_compute(compute_input));

    printf("--------------------------\n\n");
    printf("Compute all took %fms.\n", psa_0.time_compute(0x400000));
    return 0;
}
