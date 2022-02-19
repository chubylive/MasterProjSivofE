
////////////////////////////////////////////////////////////////////////////////
module processing_element
////////////////////////////////////////////////////////////////////////////////
# (
parameter
integer                       C_PE_STEP_WIDTH   = 11,
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
reg                           read_memory_registered_registered;

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
                read_memory_registered_registered <= 1'b0;
        end else begin
                read_memory_registered            <= read_memory;
                read_memory_registered_registered <= read_memory_registered;
        end
end

////////////////////////////////////////////////////////////////////////////////

wire                    [4:0] current_boolean_bit_position;
assign                        current_boolean_bit_position = current_offset[4:0];

wire                          new_boolean_bit_vector_bit_0;
wire                          new_boolean_bit_vector_bit_1;
wire                          new_boolean_bit_vector_bit_2;
wire                          new_boolean_bit_vector_bit_3;
wire                          new_boolean_bit_vector_bit_4;
wire                          new_boolean_bit_vector_bit_5;
wire                          new_boolean_bit_vector_bit_6;
wire                          new_boolean_bit_vector_bit_7;
wire                          new_boolean_bit_vector_bit_8;
wire                          new_boolean_bit_vector_bit_9;

wire                          new_boolean_bit_vector_bit_10;
wire                          new_boolean_bit_vector_bit_11;
wire                          new_boolean_bit_vector_bit_12;
wire                          new_boolean_bit_vector_bit_13;
wire                          new_boolean_bit_vector_bit_14;
wire                          new_boolean_bit_vector_bit_15;
wire                          new_boolean_bit_vector_bit_16;
wire                          new_boolean_bit_vector_bit_17;
wire                          new_boolean_bit_vector_bit_18;
wire                          new_boolean_bit_vector_bit_19;

wire                          new_boolean_bit_vector_bit_20;
wire                          new_boolean_bit_vector_bit_21;
wire                          new_boolean_bit_vector_bit_22;
wire                          new_boolean_bit_vector_bit_23;
wire                          new_boolean_bit_vector_bit_24;
wire                          new_boolean_bit_vector_bit_25;
wire                          new_boolean_bit_vector_bit_26;
wire                          new_boolean_bit_vector_bit_27;
wire                          new_boolean_bit_vector_bit_28;
wire                          new_boolean_bit_vector_bit_29;

wire                          new_boolean_bit_vector_bit_30;
wire                          new_boolean_bit_vector_bit_31;

assign                        new_boolean_bit_vector_bit_0  = (current_boolean_bit_position == 5'd0 );
assign                        new_boolean_bit_vector_bit_1  = (current_boolean_bit_position == 5'd1 );
assign                        new_boolean_bit_vector_bit_2  = (current_boolean_bit_position == 5'd2 );
assign                        new_boolean_bit_vector_bit_3  = (current_boolean_bit_position == 5'd3 );
assign                        new_boolean_bit_vector_bit_4  = (current_boolean_bit_position == 5'd4 );
assign                        new_boolean_bit_vector_bit_5  = (current_boolean_bit_position == 5'd5 );
assign                        new_boolean_bit_vector_bit_6  = (current_boolean_bit_position == 5'd6 );
assign                        new_boolean_bit_vector_bit_7  = (current_boolean_bit_position == 5'd7 );
assign                        new_boolean_bit_vector_bit_8  = (current_boolean_bit_position == 5'd8 );
assign                        new_boolean_bit_vector_bit_9  = (current_boolean_bit_position == 5'd9 );

assign                        new_boolean_bit_vector_bit_10 = (current_boolean_bit_position == 5'd10);
assign                        new_boolean_bit_vector_bit_11 = (current_boolean_bit_position == 5'd11);
assign                        new_boolean_bit_vector_bit_12 = (current_boolean_bit_position == 5'd12);
assign                        new_boolean_bit_vector_bit_13 = (current_boolean_bit_position == 5'd13);
assign                        new_boolean_bit_vector_bit_14 = (current_boolean_bit_position == 5'd14);
assign                        new_boolean_bit_vector_bit_15 = (current_boolean_bit_position == 5'd15);
assign                        new_boolean_bit_vector_bit_16 = (current_boolean_bit_position == 5'd16);
assign                        new_boolean_bit_vector_bit_17 = (current_boolean_bit_position == 5'd17);
assign                        new_boolean_bit_vector_bit_18 = (current_boolean_bit_position == 5'd18);
assign                        new_boolean_bit_vector_bit_19 = (current_boolean_bit_position == 5'd19);

assign                        new_boolean_bit_vector_bit_20 = (current_boolean_bit_position == 5'd20);
assign                        new_boolean_bit_vector_bit_21 = (current_boolean_bit_position == 5'd21);
assign                        new_boolean_bit_vector_bit_22 = (current_boolean_bit_position == 5'd22);
assign                        new_boolean_bit_vector_bit_23 = (current_boolean_bit_position == 5'd23);
assign                        new_boolean_bit_vector_bit_24 = (current_boolean_bit_position == 5'd24);
assign                        new_boolean_bit_vector_bit_25 = (current_boolean_bit_position == 5'd25);
assign                        new_boolean_bit_vector_bit_26 = (current_boolean_bit_position == 5'd26);
assign                        new_boolean_bit_vector_bit_27 = (current_boolean_bit_position == 5'd27);
assign                        new_boolean_bit_vector_bit_28 = (current_boolean_bit_position == 5'd28);
assign                        new_boolean_bit_vector_bit_29 = (current_boolean_bit_position == 5'd29);

assign                        new_boolean_bit_vector_bit_30 = (current_boolean_bit_position == 5'd30);
assign                        new_boolean_bit_vector_bit_31 = (current_boolean_bit_position == 5'd31);

wire                   [31:0] new_boolean_bit_vector;
assign                        new_boolean_bit_vector = {
                                      new_boolean_bit_vector_bit_31,
                                      new_boolean_bit_vector_bit_30,

                                      new_boolean_bit_vector_bit_29,
                                      new_boolean_bit_vector_bit_28,
                                      new_boolean_bit_vector_bit_27,
                                      new_boolean_bit_vector_bit_26,
                                      new_boolean_bit_vector_bit_25,
                                      new_boolean_bit_vector_bit_24,
                                      new_boolean_bit_vector_bit_23,
                                      new_boolean_bit_vector_bit_22,
                                      new_boolean_bit_vector_bit_21,
                                      new_boolean_bit_vector_bit_20,

                                      new_boolean_bit_vector_bit_19,
                                      new_boolean_bit_vector_bit_18,
                                      new_boolean_bit_vector_bit_17,
                                      new_boolean_bit_vector_bit_16,
                                      new_boolean_bit_vector_bit_15,
                                      new_boolean_bit_vector_bit_14,
                                      new_boolean_bit_vector_bit_13,
                                      new_boolean_bit_vector_bit_12,
                                      new_boolean_bit_vector_bit_11,
                                      new_boolean_bit_vector_bit_10,

                                      new_boolean_bit_vector_bit_9,
                                      new_boolean_bit_vector_bit_8,
                                      new_boolean_bit_vector_bit_7,
                                      new_boolean_bit_vector_bit_6,
                                      new_boolean_bit_vector_bit_5,
                                      new_boolean_bit_vector_bit_4,
                                      new_boolean_bit_vector_bit_3,
                                      new_boolean_bit_vector_bit_2,
                                      new_boolean_bit_vector_bit_1,
                                      new_boolean_bit_vector_bit_0
                              };

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
                if (executing_compute_command & read_memory_registered) begin
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
assign                        read_memory_command_done  = executing_read_memory_command  & read_memory_registered_registered;

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
