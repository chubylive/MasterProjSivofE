
////////////////////////////////////////////////////////////////////////////////
interface processing_element_if
////////////////////////////////////////////////////////////////////////////////
(
input                         clock,
input                         reset_n,

input                         start,

input                  [31:0] command,

input                  [31:0] argument_1,
input                  [31:0] argument_2,
input                  [31:0] argument_3,

input                  [31:0] memory_read_data_pe,
input                  [31:0] memory_read_data_axi,

input                         command_done,

input                         read_memory_a,
input                         read_memory_d,
input                         read_memory_d_drv,
input                  [31:0] memory_read_address,
input                  [31:0] memory_read_data,

input                         write_memory,
input                  [31:0] memory_write_address,
input                  [31:0] memory_write_data,

input                         busy
);
////////////////////////////////////////////////////////////////////////////////

reg                           write_command_drv;

reg                    [31:0] command_drv;

reg                    [31:0] argument_1_drv;
reg                    [31:0] argument_2_drv;
reg                    [31:0] argument_3_drv;

reg                    [31:0] memory_read_data_drv;

////////////////////////////////////////////////////////////////////////////////

initial begin
        write_command_drv    =  1'b0;

        command_drv          = 32'h0;

        argument_1_drv       = 32'h0;
        argument_2_drv       = 32'h0;
        argument_3_drv       = 32'h0;

        memory_read_data_drv = 32'h0;
end

////////////////////////////////////////////////////////////////////////////////

endinterface

