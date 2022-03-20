#/bin/bash 

echo "programming fpga for computational method 1 and 2"
cd /lib/firmware ; echo methods_1_and_2_final_implementation.bin > /sys/class/fpga_manager/fpga0/firmware