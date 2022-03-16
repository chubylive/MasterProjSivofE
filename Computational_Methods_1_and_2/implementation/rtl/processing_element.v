
////////////////////////////////////////////////////////////////////////////////
module processing_element
////////////////////////////////////////////////////////////////////////////////
# (
parameter
integer                       C_PE_STEP_WIDTH   = 12,
parameter
integer                       C_PE_OFFSET_WIDTH = 14
)
////////////////////////////////////////////////////////////////////////////////
(
input                         clock,
input                         reset_n,

input                         start,

input                   [1:0] command,

input [C_PE_STEP_WIDTH  -1:0] argument_1,
input [C_PE_OFFSET_WIDTH-1:0] argument_2,
input [C_PE_OFFSET_WIDTH-1:0] argument_3,

output
reg                    [31:0] memory_read_data,

output
reg                           command_done
);
////////////////////////////////////////////////////////////////////////////////

reg                           start_registered;

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock) begin
        if (reset_n == 1'b0) begin
                start_registered <= 1'b0;
        end else begin
                start_registered <= start;
        end
end

////////////////////////////////////////////////////////////////////////////////

wire  [C_PE_OFFSET_WIDTH  :0] max_offset;
assign                        max_offset = {1'b0, argument_3};

////////////////////////////////////////////////////////////////////////////////

reg   [C_PE_OFFSET_WIDTH  :0] current_offset;
wire  [C_PE_OFFSET_WIDTH  :0] next_offset;

assign                        next_offset = current_offset + argument_1;

////////////////////////////////////////////////////////////////////////////////

wire                          current_offset_at_most_max_offset;
assign                        current_offset_at_most_max_offset = (current_offset <= max_offset);

////////////////////////////////////////////////////////////////////////////////

wire                          executing_compute_command;
wire                          executing_clear_memory_command;
wire                          executing_read_memory_command;

assign                        executing_compute_command      = start & (command == 2'd0);
assign                        executing_clear_memory_command = start & (command == 2'd1);
assign                        executing_read_memory_command  = start & (command == 2'd2);

wire                          start_compute_command;
wire                          start_clear_memory_command;
wire                          start_read_memory_command;

assign                        start_compute_command      = executing_compute_command      & (~ start_registered);
assign                        start_clear_memory_command = executing_clear_memory_command & (~ start_registered);
assign                        start_read_memory_command  = executing_read_memory_command  & (~ start_registered);

////////////////////////////////////////////////////////////////////////////////

reg                           read_memory;
reg                           read_memory_registered;

reg   [C_PE_OFFSET_WIDTH-6:0] current_memory_read_address;
wire  [C_PE_OFFSET_WIDTH-6:0] next_memory_read_address;

assign                        next_memory_read_address = current_offset[C_PE_OFFSET_WIDTH-1:5];

wire                   [31:0] current_memory_read_data;
reg                           current_memory_read_data_available;

////////////////////////////////////////////////////////////////////////////////

wire                                                                next_memory_read_address_equals_current_memory_read_address;
assign                                                              next_memory_read_address_equals_current_memory_read_address = (next_memory_read_address == current_memory_read_address);

wire                          current_offset_at_most_max_offset_and_next_memory_read_address_equals_current_memory_read_address;
assign                        current_offset_at_most_max_offset_and_next_memory_read_address_equals_current_memory_read_address = current_offset_at_most_max_offset & next_memory_read_address_equals_current_memory_read_address;

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock) begin
        if (reset_n == 1'b0) begin
                current_offset <= {(C_PE_OFFSET_WIDTH+1) {1'b0}};
        end else begin
                if (executing_compute_command) begin
                        if (~ start_registered) begin
                                current_offset <= {1'b0, argument_2};
                        end else begin
                                if (current_offset_at_most_max_offset_and_next_memory_read_address_equals_current_memory_read_address) begin
                                        current_offset <= next_offset;
                                end else begin
                                        current_offset <= current_offset;
                                end
                        end
                end else begin
                        current_offset <= current_offset;
                end
        end
end

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock) begin
        if (reset_n == 1'b0) begin
                read_memory_registered            <= 1'b0;
        end else begin
                read_memory_registered            <= read_memory;
        end
end

////////////////////////////////////////////////////////////////////////////////

wire                    [4:0] current_boolean_bit_position;
assign                        current_boolean_bit_position = current_offset[4:0];

reg                    [31:0] new_boolean_bit_vector;

always @ (*) begin
        case (current_boolean_bit_position)
                5'd0 : begin
                        new_boolean_bit_vector <= 32'h0000_0001;
                end

                5'd1 : begin
                        new_boolean_bit_vector <= 32'h0000_0002;
                end

                5'd2 : begin
                        new_boolean_bit_vector <= 32'h0000_0004;
                end

                5'd3 : begin
                        new_boolean_bit_vector <= 32'h0000_0008;
                end

                5'd4 : begin
                        new_boolean_bit_vector <= 32'h0000_0010;
                end

                5'd5 : begin
                        new_boolean_bit_vector <= 32'h0000_0020;
                end

                5'd6 : begin
                        new_boolean_bit_vector <= 32'h0000_0040;
                end

                5'd7 : begin
                        new_boolean_bit_vector <= 32'h0000_0080;
                end

                5'd8 : begin
                        new_boolean_bit_vector <= 32'h0000_0100;
                end

                5'd9 : begin
                        new_boolean_bit_vector <= 32'h0000_0200;
                end

                5'd10 : begin
                        new_boolean_bit_vector <= 32'h0000_0400;
                end

                5'd11 : begin
                        new_boolean_bit_vector <= 32'h0000_0800;
                end

                5'd12 : begin
                        new_boolean_bit_vector <= 32'h0000_1000;
                end

                5'd13 : begin
                        new_boolean_bit_vector <= 32'h0000_2000;
                end

                5'd14 : begin
                        new_boolean_bit_vector <= 32'h0000_4000;
                end

                5'd15 : begin
                        new_boolean_bit_vector <= 32'h0000_8000;
                end

                5'd16 : begin
                        new_boolean_bit_vector <= 32'h0001_0000;
                end

                5'd17 : begin
                        new_boolean_bit_vector <= 32'h0002_0000;
                end

                5'd18 : begin
                        new_boolean_bit_vector <= 32'h0004_0000;
                end

                5'd19 : begin
                        new_boolean_bit_vector <= 32'h0008_0000;
                end

                5'd20 : begin
                        new_boolean_bit_vector <= 32'h0010_0000;
                end

                5'd21 : begin
                        new_boolean_bit_vector <= 32'h0020_0000;
                end

                5'd22 : begin
                        new_boolean_bit_vector <= 32'h0040_0000;
                end

                5'd23 : begin
                        new_boolean_bit_vector <= 32'h0080_0000;
                end

                5'd24 : begin
                        new_boolean_bit_vector <= 32'h0100_0000;
                end

                5'd25 : begin
                        new_boolean_bit_vector <= 32'h0200_0000;
                end

                5'd26 : begin
                        new_boolean_bit_vector <= 32'h0400_0000;
                end

                5'd27 : begin
                        new_boolean_bit_vector <= 32'h0800_0000;
                end

                5'd28 : begin
                        new_boolean_bit_vector <= 32'h1000_0000;
                end

                5'd29 : begin
                        new_boolean_bit_vector <= 32'h2000_0000;
                end

                5'd30 : begin
                        new_boolean_bit_vector <= 32'h4000_0000;
                end

                5'd31 : begin
                        new_boolean_bit_vector <= 32'h8000_0000;
                end
        endcase
end

reg                    [31:0] current_boolean_bit_vector;

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock) begin
        if (reset_n == 1'b0) begin
                read_memory                 <= 1'b0;
                current_memory_read_address <= {(C_PE_OFFSET_WIDTH-5) {1'b0}};
                current_boolean_bit_vector  <= 32'h0;
        end else begin
                if (executing_compute_command) begin
                        if (~ start_registered) begin
                                read_memory                 <= 1'b1;
                                current_memory_read_address <= argument_2[C_PE_OFFSET_WIDTH-1:5];
                                current_boolean_bit_vector  <= 32'h0;
                        end else begin
                                if (current_memory_read_data_available & current_offset_at_most_max_offset & (~ next_memory_read_address_equals_current_memory_read_address)) begin
                                        read_memory                 <= 1'b1;
                                        current_memory_read_address <= next_memory_read_address;
                                        current_boolean_bit_vector  <= 32'h0;
                                end else begin
                                        read_memory                 <= 1'b0;
                                        current_memory_read_address <= current_memory_read_address;

                                        if (current_offset_at_most_max_offset_and_next_memory_read_address_equals_current_memory_read_address) begin
                                                current_boolean_bit_vector  <= current_boolean_bit_vector | new_boolean_bit_vector;
                                        end else begin
                                                current_boolean_bit_vector  <= current_boolean_bit_vector;
                                        end
                                end
                        end
                end else begin
                        if (executing_read_memory_command) begin
                                if (~ start_registered) begin
                                        read_memory                 <= 1'b1;
                                        current_memory_read_address <= argument_1[C_PE_OFFSET_WIDTH-6:0];
                                end else begin
                                        read_memory                 <= 1'b0;
                                        current_memory_read_address <= current_memory_read_address;
                                end
                        end else begin
                                read_memory                 <= 1'b0;
                                current_memory_read_address <= current_memory_read_address;
                        end

                        current_boolean_bit_vector  <= current_boolean_bit_vector;
                end
        end
end

////////////////////////////////////////////////////////////////////////////////

reg                           write_memory;
reg   [C_PE_OFFSET_WIDTH-6:0] memory_write_address;
reg                    [31:0] memory_write_data;

wire                          maxed_memory_write_address;
assign                        maxed_memory_write_address = (& memory_write_address);

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock) begin
        if (reset_n == 1'b0) begin
                write_memory         <= 1'b0;
                memory_write_address <= {(C_PE_OFFSET_WIDTH-5) {1'b0}};
                memory_write_data    <= 32'h0;
        end else begin
                if (executing_compute_command) begin
                        if (current_memory_read_data_available & (~ current_offset_at_most_max_offset_and_next_memory_read_address_equals_current_memory_read_address)) begin
                                write_memory         <= 1'b1;
                                memory_write_address <= current_memory_read_address;
                                memory_write_data    <= current_memory_read_data | current_boolean_bit_vector;
                        end else begin
                                write_memory         <= 1'b0;
                                memory_write_address <= memory_write_address;
                                memory_write_data    <= memory_write_data;
                        end
                end else begin
                        if (executing_clear_memory_command) begin
                                if (~ start_registered) begin
                                        write_memory         <= 1'b1;
                                        memory_write_address <= {(C_PE_OFFSET_WIDTH-5) {1'b0}};
                                        memory_write_data    <= 32'h0;
                                end else begin
                                        if (~ maxed_memory_write_address) begin
                                                write_memory         <= 1'b1;
                                                memory_write_address <= memory_write_address + 1'b1;
                                                memory_write_data    <= 32'h0;
                                        end else begin
                                                write_memory         <= 1'b0;
                                                memory_write_address <= memory_write_address;
                                                memory_write_data    <= memory_write_data;
                                        end
                                end
                        end else begin
                                write_memory         <= 1'b0;
                                memory_write_address <= memory_write_address;
                                memory_write_data    <= memory_write_data;
                        end
                end
        end
end

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock) begin
        if (reset_n == 1'b0) begin
                current_memory_read_data_available <= 1'b0;
        end else begin
                if (executing_compute_command & read_memory) begin
                        current_memory_read_data_available <= 1'b1;
                end else begin
                        if (current_memory_read_data_available & (~ current_offset_at_most_max_offset_and_next_memory_read_address_equals_current_memory_read_address)) begin
                                current_memory_read_data_available <= 1'b0;
                        end else begin
                                current_memory_read_data_available <= current_memory_read_data_available;
                        end
                end
        end
end

////////////////////////////////////////////////////////////////////////////////

wire                          compute_command_done;
wire                          clear_memory_command_done;
wire                          read_memory_command_done;

assign                        compute_command_done      = executing_compute_command      & write_memory & (~ current_offset_at_most_max_offset);
assign                        clear_memory_command_done = executing_clear_memory_command & write_memory & maxed_memory_write_address;
assign                        read_memory_command_done  = executing_read_memory_command  & read_memory_registered;

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock) begin
        if (reset_n == 1'b0) begin
                command_done <= 1'b0;
        end else begin
                command_done <= compute_command_done | clear_memory_command_done | read_memory_command_done;
        end
end

////////////////////////////////////////////////////////////////////////////////

always @ (posedge clock) begin
        if (reset_n == 1'b0) begin
                memory_read_data <= 32'h0;
        end else begin
                if (read_memory_command_done) begin
                        memory_read_data <= current_memory_read_data;
                end else begin
                        memory_read_data <= memory_read_data;
                end
        end
end

////////////////////////////////////////////////////////////////////////////////

pe_bram_sdp_512x32
   bram_sdp_512x32
(
. clka                      ( clock                       ) ,

. wea                       ( write_memory                ) ,
. addra                     ( memory_write_address        ) ,
. dina                      ( memory_write_data           ) ,

. clkb                      ( clock                       ) ,

. addrb                     ( current_memory_read_address ) ,
. doutb                     ( current_memory_read_data    )
);

////////////////////////////////////////////////////////////////////////////////

endmodule

