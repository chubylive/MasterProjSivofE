
////////////////////////////////////////////////////////////////////////////////
module processing_element_tb
////////////////////////////////////////////////////////////////////////////////
(
);
////////////////////////////////////////////////////////////////////////////////

localparam
integer                       C_PE_STEP_WIDTH   = 12;
localparam
integer                       C_PE_OFFSET_WIDTH = 14;

////////////////////////////////////////////////////////////////////////////////

`include "uvm_macros.svh"
import uvm_pkg::*;
import processing_element_test_pkg::*;

////////////////////////////////////////////////////////////////////////////////

initial begin
        run_test ("");
end

////////////////////////////////////////////////////////////////////////////////

reg                           clock;
reg                           reset_n;

////////////////////////////////////////////////////////////////////////////////

initial begin
        clock = 1'b0;

        forever begin
                #2ns;
                clock = ~ clock;
        end
end

////////////////////////////////////////////////////////////////////////////////

initial begin
        reset_n = 1'b0;

        @ (posedge clock);
        reset_n = 1'b1;
end

////////////////////////////////////////////////////////////////////////////////

reg                           busy;

reg                     [1:0] command;

reg   [C_PE_STEP_WIDTH  -1:0] argument_1;
reg   [C_PE_OFFSET_WIDTH-1:0] argument_2;
reg   [C_PE_OFFSET_WIDTH-1:0] argument_3;

wire                   [31:0] memory_read_data;

wire                          command_done;

////////////////////////////////////////////////////////////////////////////////

wire                          read_memory;
wire  [C_PE_OFFSET_WIDTH-6:0] current_memory_read_address;
wire                   [31:0] current_memory_read_data;

reg                           read_memory_registered;

////////////////////////////////////////////////////////////////////////////////

wire                          write_memory;
wire  [C_PE_OFFSET_WIDTH-6:0] memory_write_address;
wire                   [31:0] memory_write_data;

////////////////////////////////////////////////////////////////////////////////

wire                          write_command_drv;

wire                    [1:0] command_drv;

wire  [C_PE_STEP_WIDTH  -1:0] argument_1_drv;
wire  [C_PE_OFFSET_WIDTH-1:0] argument_2_drv;
wire  [C_PE_OFFSET_WIDTH-1:0] argument_3_drv;

////////////////////////////////////////////////////////////////////////////////

processing_element_if
processing_element_if_h
(
. clock                     ( clock                             ) ,
. reset_n                   ( reset_n                           ) ,

. start                     ( write_command_drv                 ) ,

. command                   ( command_drv                       ) ,

. argument_1                ( argument_1_drv                    ) ,
. argument_2                ( argument_2_drv                    ) ,
. argument_3                ( argument_3_drv                    ) ,

. memory_read_data_pe       ( memory_read_data                  ) ,
. memory_read_data_axi      ( memory_read_data                  ) ,

. command_done              ( command_done                      ) ,

. read_memory_a             ( read_memory                       ) ,
. read_memory_d             ( read_memory_registered            ) ,
. read_memory_d_drv         ( read_memory                       ) ,
. memory_read_address       ( current_memory_read_address       ) ,
. memory_read_data          ( current_memory_read_data          ) ,

. write_memory              ( write_memory                      ) ,
. memory_write_address      ( memory_write_address              ) ,
. memory_write_data         ( memory_write_data                 ) ,

. busy                      ( busy                              )
);

////////////////////////////////////////////////////////////////////////////////

assign                        write_command_drv        = processing_element_if_h . write_command_drv   ;

assign                        command_drv              = processing_element_if_h . command_drv         ;

assign                        argument_1_drv           = processing_element_if_h . argument_1_drv      ;
assign                        argument_2_drv           = processing_element_if_h . argument_2_drv      ;
assign                        argument_3_drv           = processing_element_if_h . argument_3_drv      ;

assign                        current_memory_read_data = processing_element_if_h . memory_read_data_drv;

////////////////////////////////////////////////////////////////////////////////

initial begin
        uvm_config_db # (virtual processing_element_if) :: set (null, "uvm_test_top", "processing_element_vif", processing_element_if_h);
end

////////////////////////////////////////////////////////////////////////////////

processing_element
# (
. C_PE_STEP_WIDTH           ( C_PE_STEP_WIDTH   ) ,
. C_PE_OFFSET_WIDTH         ( C_PE_OFFSET_WIDTH )
)
dut
(
. clock                     ( clock             ) ,
. reset_n                   ( reset_n           ) ,

. start                     ( busy              ) ,

. command                   ( command           ) ,

. argument_1                ( argument_1        ) ,
. argument_2                ( argument_2        ) ,
. argument_3                ( argument_3        ) ,

. memory_read_data          ( memory_read_data  ) ,

. command_done              ( command_done      )
);

////////////////////////////////////////////////////////////////////////////////

assign                        read_memory                 = dut . read_memory                ;
assign                        current_memory_read_address = dut . current_memory_read_address;
assign                  dut . current_memory_read_data    =       current_memory_read_data   ;

////////////////////////////////////////////////////////////////////////////////

assign                        write_memory                = dut . write_memory        ;
assign                        memory_write_address        = dut . memory_write_address;
assign                        memory_write_data           = dut . memory_write_data   ;

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock or negedge reset_n) begin
        if (reset_n == 1'b0) begin
                read_memory_registered            <=  1'b0;
        end else begin
                read_memory_registered            <= read_memory;
        end
end

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock or negedge reset_n) begin
        if (reset_n == 1'b0) begin
                busy <= 1'b0;
        end else begin
                if (write_command_drv) begin
                        busy <= 1'b1;
                end else begin
                        if (command_done) begin
                                busy <= 1'b0;
                        end else begin
                                busy <= busy;
                        end
                end
        end
end

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock or negedge reset_n) begin
        if (reset_n == 1'b0) begin
                command    <= 2'h0;

                argument_1 <= {(C_PE_STEP_WIDTH  ) {1'b0}};
                argument_2 <= {(C_PE_OFFSET_WIDTH) {1'b0}};
                argument_3 <= {(C_PE_OFFSET_WIDTH) {1'b0}};
        end else begin
                if (write_command_drv) begin
                        command    <= command_drv;

                        argument_1 <= argument_1_drv;
                        argument_2 <= argument_2_drv;
                        argument_3 <= argument_3_drv;
                end else begin
                        command    <= command;

                        argument_1 <= argument_1;
                        argument_2 <= argument_2;
                        argument_3 <= argument_3;
                end
        end
end

////////////////////////////////////////////////////////////////////////////////

pe_axi4_lite_slave
top
(
);

////////////////////////////////////////////////////////////////////////////////

endmodule

