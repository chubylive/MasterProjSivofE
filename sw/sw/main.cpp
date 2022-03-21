#include "PrimeSieveMethod1.h"
#include "PrimeSieveMethod2.h"
#include "PrimeSieveMethod3.h"
#include <stdio.h>
#include <stdint.h>
#include <sstream>
#include <fstream>
#include <iomanip>

void calc_method_1()
{
    std::ofstream out_file("computation_method_1_data.txt");
    uint32_t start_value = 0x4000;
    uint32_t stop_value = (512 * 32 * 280) - 1;
    PrimeSieveMethod1 psm;

    for (int input = start_value; input <= stop_value; input <<= 1)
    {
        unsigned in = input - 1;
        printf("** Input value: %d\n", in);
        out_file << "compute_1_" << in << " = np.array([" << std::endl;
        for (int rows = 512; rows > 0; rows >>= 1)
        {
            unsigned required_pe = input / rows / 32;
            if (required_pe > 280)
            {
                break;
            }
            float time_elapsed = psm.time_compute_0(in, required_pe, rows);
            printf("Compute method 1 %#x using %*d pe and %*d rows took %.*fms.\n", in, 3, required_pe, 3, rows, 10, time_elapsed);
            out_file << "    [" << required_pe << ", " << rows << ", " << std::setprecision(10) << std::fixed << time_elapsed << "]," << std::endl;

            std::stringstream ss;
            ss = psm.read_memory_n(in);
            std::ofstream tmp_file("./val/compute_1/" + std::to_string(in) + "_" + std::to_string(required_pe) + "_" + std::to_string(rows) + ".txt");
            tmp_file << ss.rdbuf();
            tmp_file.close();
        }
        out_file << "])" << std::endl
                 << std::endl;
    }
    out_file.close();
}

void calc_method_2()
{
    std::ofstream out_file("computation_method_2_data.txt");
    uint32_t start_value = 0x4000;
    uint32_t stop_value = (512 * 32 * 280) - 1;
    PrimeSieveMethod2 psm;

    for (int input = start_value; input <= stop_value; input <<= 1)
    {
        unsigned in = input - 1;
        printf("** Input value: %d\n", in);
        out_file << "compute_2_" << in << " = np.array([" << std::endl;
        for (int rows = 512; rows > 0; rows >>= 1)
        {
            unsigned required_pe = input / rows / 32;
            if (required_pe > 280)
            {
                break;
            }
            float time_elapsed = psm.time_compute_0(in, required_pe, rows);
            printf("Compute method 2 %#x using %*d pe and %*d rows took %.*fms.\n", in, 3, required_pe, 3, rows, 10, time_elapsed);
            out_file << "    [" << required_pe << ", " << rows << ", " << std::setprecision(10) << std::fixed << time_elapsed << "]," << std::endl;

            std::stringstream ss;
            ss = psm.read_memory_n(in);
            std::ofstream tmp_file("./val/compute_2/" + std::to_string(in) + "_" + std::to_string(required_pe) + "_" + std::to_string(rows) + ".txt");
            tmp_file << 2 << std::endl;
            tmp_file << ss.rdbuf();
            tmp_file.close();
        }
        out_file << "])" << std::endl
                 << std::endl;
    }
    out_file.close();
}

void calc_method_3()
{
    std::ofstream out_file("computation_method_3_data.txt");
    uint32_t start_value = 0x4000;
    uint32_t stop_value = (512 * 32 * 280) - 1;
    PrimeSieveMethod3 psm;

    for (int input = start_value; input <= stop_value; input <<= 1)
    {
        unsigned in = input - 1;
        printf("** Input value: %d\n", in);
        out_file << "compute_3_" << in << " = np.array([" << std::endl;
        for (int rows = 512; rows > 0; rows >>= 1)
        {
            unsigned required_pe = input / rows / 32;
            if (required_pe > 280)
            {
                break;
            }
            float time_elapsed = psm.time_compute_0(in, required_pe, rows);
            printf("Compute method 3 %#x using %*d pe and %*d rows took %.*fms.\n", in, 3, required_pe, 3, rows, 10, time_elapsed);
            out_file << "    [" << required_pe << ", " << rows << ", " << std::setprecision(10) << std::fixed << time_elapsed << "]," << std::endl;

            std::stringstream ss;
            ss = psm.read_memory_n(in);
            std::ofstream tmp_file("./val/compute_3/" + std::to_string(in) + "_" + std::to_string(required_pe) + "_" + std::to_string(rows) + ".txt");
            tmp_file << 2 << std::endl;
            tmp_file << 3 << std::endl;
            tmp_file << ss.rdbuf();
            tmp_file.close();
        }
        out_file << "])" << std::endl
                 << std::endl;
    }
    out_file.close();
}

void validate_method_1()
{
    PrimeSieveMethod1 psm;
    std::stringstream ss;
    uint32_t in = (512 * 32 * 280) - 1;

    psm.reconfig(280, 512, in);
    psm.clear_memory_all();
    psm.compute_all();
    ss = psm.read_memory_n(in);
    std::ofstream out_file("./val/computation_method_1_result.txt");
    out_file << ss.rdbuf();
    out_file.close();

    printf("last_compute_count: %d\n", psm.get_last_compute_count());
}

void validate_method_2()
{
    PrimeSieveMethod2 psm;
    std::stringstream ss;
    uint32_t in = (512 * 32 * 280) - 1;

    psm.reconfig(280, 512, in);
    psm.clear_memory_all();
    psm.compute_all();
    ss = psm.read_memory_n(in);
    std::ofstream out_file("./val/computation_method_2_result.txt");
    out_file << 2 << std::endl;
    out_file << ss.rdbuf();
    out_file.close();

    printf("last_compute_count: %d\n", psm.get_last_compute_count());
}

void validate_method_3()
{
    PrimeSieveMethod3 psm;
    std::stringstream ss;
    uint32_t in = (512 * 32 * 280) - 1;

    psm.reconfig(280, 512, in);
    psm.clear_memory_all();
    psm.compute_all();
    ss = psm.read_memory_n(in);
    std::ofstream out_file("./val/computation_method_3_result.txt");
    out_file << 2 << std::endl;
    out_file << 3 << std::endl;
    out_file << ss.rdbuf();
    out_file.close();

    printf("last_compute_count: %d\n", psm.get_last_compute_count());
}

int main(int argc, char **argv)
{
    printf("Programming Xilinx Zynq FPGA for computational method 1 and 2...\n");
    system("~/progCM1_2.sh");
    sleep(10);
    calc_method_1();
    printf("--------------------------\n\n");
    calc_method_2();
    printf("--------------------------\n\n");
    // validate_method_1();
    // validate_method_2();

    printf("Programming Xilinx Zynq FPGA for computational method 3...\n");
    system("~/progCM3.sh");
    sleep(10);
    calc_method_3();
    printf("--------------------------\n\n");
    // validate_method_3();
    return 0;
}
