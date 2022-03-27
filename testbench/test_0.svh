
////////////////////////////////////////////////////////////////////////////////
class test_0 extends uvm_test;
////////////////////////////////////////////////////////////////////////////////

        `uvm_component_utils (test_0)

////////////////////////////////////////////////////////////////////////////////

        virtual processing_element_if processing_element_vif;

        bit          current_command_valid     = 0;
        int unsigned current_command              ;

        int unsigned memory_read_address_queue [$];
        int unsigned memory_read_data_queue    [$];
        bit [63:0]   write_memory_queue        [$];

////////////////////////////////////////////////////////////////////////////////

        function new (string name = "test_0", uvm_component parent);
                super . new (name, parent);
        endfunction

////////////////////////////////////////////////////////////////////////////////

        virtual function void build_phase (uvm_phase phase);
                super . build_phase (phase);

                if (uvm_config_db # (virtual processing_element_if) :: get (this, "", "processing_element_vif", processing_element_vif) == 0) begin
                        `uvm_fatal ("processing_element_vif", "failed to initialize virtual interface")
                end
        endfunction

////////////////////////////////////////////////////////////////////////////////

        virtual task run_phase (uvm_phase phase);
                super . run_phase (phase);

                phase . raise_objection (this);

                @ (posedge processing_element_vif . reset_n);

                fork
////////////////////////////////////////////////////////////////////////////////
                begin
                        forever begin
                                @ (posedge processing_element_vif . clock);

                                if (processing_element_vif . start) begin
                                        int unsigned command;
                                        int unsigned step;
                                        int unsigned current_offset;
                                        int unsigned max_offset;

                                        command        = processing_element_vif . command   ;
                                        step           = processing_element_vif . argument_1;
                                        current_offset = processing_element_vif . argument_2;
                                        max_offset     = processing_element_vif . argument_3;

                                        `uvm_info ("current_command", $sformatf ("command = %0d, argument_1 = %0d, argument_2 = %0d, argument_3 = %0d", command, step, current_offset, max_offset), UVM_NONE)

                                        if (current_command_valid) begin
                                                `uvm_fatal ("current_command_valid", "unexpected current_command_valid")
                                        end

                                        current_command_valid = 1;
                                        current_command       = command;

                                        case (command)
                                                0 : begin
                                                        int unsigned cmra;
                                                        int unsigned cmwd;
                                                        int unsigned nmra;

                                                        cmra           = (current_offset >> 5);
                                                        cmwd           = 0;

//                                                      `uvm_info ("current_command", $sformatf ("predicting read_memory_address = 'h%0h", cmra), UVM_NONE)
                                                        memory_read_address_queue . push_back (cmra);

                                                        do begin
                                                                nmra = (current_offset >> 5);

                                                                if (nmra == cmra) begin
                                                                end else begin
//                                                                      `uvm_info ("current_command", $sformatf ("predicting write_memory_address = 'h%0h, write_memory_data = 'h%0h", cmra, cmwd), UVM_NONE)
                                                                        write_memory_queue . push_back ({cmwd, cmra});

                                                                        cmra           = nmra;
                                                                        cmwd           = 0;

//                                                                      `uvm_info ("current_command", $sformatf ("predicting read_memory_address = 'h%0h", cmra), UVM_NONE)
                                                                        memory_read_address_queue . push_back (cmra);
                                                                end

                                                                cmwd |= (1 << (current_offset & 31));

                                                                current_offset += step;
                                                        end while (current_offset <= max_offset);

//                                                      `uvm_info ("current_command", $sformatf ("predicting write_memory_address = 'h%0h, write_memory_data = 'h%0h", cmra, cmwd), UVM_NONE)
                                                        write_memory_queue . push_back ({cmwd, cmra});
                                                end

                                                1 : begin
                                                        for (int unsigned mwa = 0; mwa < 512; mwa ++) begin
                                                                write_memory_queue . push_back ({32'h0, mwa});
                                                        end
                                                end

                                                2 : begin
                                                        memory_read_address_queue . push_back (step & 32'h1ff);
                                                end
                                        endcase
                                end
                        end
                end
////////////////////////////////////////////////////////////////////////////////
                begin
                        forever begin
                                @ (posedge processing_element_vif . clock);

                                if (processing_element_vif . command_done) begin
                                        int unsigned mrd_pe;

                                        mrd_pe = processing_element_vif . memory_read_data_pe;

//                                      `uvm_info ("command_done", "command_done", UVM_NONE)

                                        if (~ current_command_valid) begin
                                                `uvm_fatal ("current_command_valid", "expecting current_command_valid")
                                        end

                                        if (memory_read_address_queue . size ()) begin
                                                `uvm_fatal ("memory_read_address_queue", "expecting empty")
                                        end

                                        if (current_command == 2) begin
                                        int unsigned mrd;

                                        if (memory_read_data_queue    . size () == 1) begin
                                        end else begin
                                                `uvm_fatal ("memory_read_data_queue"   , "unexpected size")
                                        end

                                        mrd = memory_read_data_queue [0];

                                        if (mrd_pe === mrd) begin
                                        end else begin
                                                `uvm_fatal ("memory_read_data", $sformatf ("expecting 'h%0h", mrd))
                                        end
                                        end else begin
                                        if (memory_read_data_queue    . size ()) begin
                                                `uvm_fatal ("memory_read_data_queue"   , "expecting empty")
                                        end
                                        end

                                        if (write_memory_queue        . size ()) begin
                                                `uvm_fatal ("write_memory_queue"       , "expecting empty")
                                        end

                                        current_command_valid = 0;
                                end
                        end
                end
////////////////////////////////////////////////////////////////////////////////
                begin
                        forever begin
                                @ (posedge processing_element_vif . clock);

                                if (processing_element_vif . read_memory_a) begin
                                        int unsigned mra_vif;
                                        int unsigned mra;

                                        mra_vif = processing_element_vif . memory_read_address;

//                                      `uvm_info ("memory_read_address", $sformatf ("'h%0h", mra_vif), UVM_NONE)

                                        if (~ current_command_valid) begin
                                                `uvm_fatal ("current_command_valid", "expecting current_command_valid")
                                        end

                                        if (memory_read_address_queue . size () == 0) begin
                                                `uvm_fatal ("memory_read_address_queue", "unexpectedly empty")
                                        end

                                        mra = memory_read_address_queue . pop_front ();

                                        if (mra_vif === mra) begin
                                        end else begin
                                                `uvm_fatal ("memory_read_address", $sformatf ("expecting 'h%0h", mra))
                                        end
                                end
                        end
                end
////////////////////////////////////////////////////////////////////////////////
                begin
                        forever begin
                                @ (posedge processing_element_vif . clock);

                                if (processing_element_vif . read_memory_d) begin
                                        int unsigned mrd;

                                        mrd = processing_element_vif . memory_read_data;

//                                      `uvm_info ("memory_read_data", $sformatf ("'h%0h", mrd), UVM_NONE)

                                        if (~ current_command_valid) begin
                                                `uvm_fatal ("current_command_valid", "expecting current_command_valid")
                                        end

                                        if (memory_read_data_queue    . size ()) begin
                                                `uvm_fatal ("memory_read_data_queue"   , "expecting empty")
                                        end

                                        memory_read_data_queue . push_back (mrd);
                                end
                        end
                end
////////////////////////////////////////////////////////////////////////////////
                begin
                        forever begin
                                @ (posedge processing_element_vif . clock);

                                if (processing_element_vif . write_memory) begin
                                        int unsigned mwa_vif;
                                        int unsigned mwd_vif;
                                        int unsigned mrd;
                                        bit [63:0]   wm;
                                        int unsigned mwa;
                                        int unsigned mwd;

                                        mwa_vif = processing_element_vif . memory_write_address;
                                        mwd_vif = processing_element_vif . memory_write_data   ;

//                                      `uvm_info ("write_memory", $sformatf ("address = 'h%0h, data = 'h%0h", mwa_vif, mwd_vif), UVM_NONE)

                                        if (~ current_command_valid) begin
                                                `uvm_fatal ("current_command_valid", "expecting current_command_valid")
                                        end

                                        if (current_command == 0) begin
                                        if (memory_read_data_queue    . size () == 1) begin
                                        end else begin
                                                `uvm_fatal ("memory_read_data_queue", "unexpected size")
                                        end
                                        end

                                        if (write_memory_queue        . size () == 0) begin
                                                `uvm_fatal ("write_memory_queue", "unexpectedly empty")
                                        end

                                        if (current_command == 0) begin
                                        mrd = memory_read_data_queue . pop_front ();
                                        end else begin
                                        mrd = 0;
                                        end
                                        wm  = write_memory_queue     . pop_front ();

                                        mwa = wm [31: 0];
                                        mwd = wm [63:32];

                                        if (mwa_vif === mwa) begin
                                        end else begin
                                                `uvm_fatal ("memory_write_address", $sformatf ("expecting 'h%0h", mwa      ))
                                        end

                                        if (mwd_vif === (mwd | mrd)) begin
                                        end else begin
                                                `uvm_fatal ("memory_write_data"   , $sformatf ("expecting 'h%0h", mwd | mrd))
                                        end
                                end
                        end
                end
////////////////////////////////////////////////////////////////////////////////
                begin
                        forever begin
                                @ (posedge processing_element_vif . clock);

                                if (processing_element_vif . read_memory_d_drv) begin
                                        processing_element_vif . memory_read_data_drv = $urandom ();
                                end
                        end
                end
////////////////////////////////////////////////////////////////////////////////
                join_none

////////////////////////////////////////////////////////////////////////////////

                repeat (22_500_000) begin
                        int unsigned command   ;
                        int unsigned argument_1;
                        int unsigned argument_2;
                        int unsigned argument_3;

                        command    = $urandom_range (2                        );
                        argument_1 = $urandom_range ((1 << 12) - 1, 1         );
                        argument_2 = $urandom_range ((1 << 14) - 1            );
                        argument_3 = $urandom_range ((1 << 14) - 1, argument_2);

                        if (command == 2) begin
                                argument_1 --;
                        end

                        fork
                        begin
                        repeat ($urandom_range (10)) begin
                        @ (posedge processing_element_vif . clock);
                        end

                        @ (posedge processing_element_vif . clock);
                        processing_element_vif . write_command_drv = 1         ;
                        processing_element_vif . command_drv       = command   ;
                        processing_element_vif . argument_1_drv    = argument_1;
                        processing_element_vif . argument_2_drv    = argument_2;
                        processing_element_vif . argument_3_drv    = argument_3;

                        @ (posedge processing_element_vif . clock);
                        processing_element_vif . write_command_drv = 0         ;
                        end
                        join_none

                        do begin
                        @ (posedge processing_element_vif . clock);
                        end while (~ processing_element_vif . busy);

                        do begin
                        @ (posedge processing_element_vif . clock);
                        end while (processing_element_vif . busy);

                        if (command == 2) begin
                                int unsigned mrd_axi;
                                int unsigned mrd;

                                mrd_axi = processing_element_vif . memory_read_data_axi;

                                if (memory_read_data_queue    . size () == 1) begin
                                end else begin
                                        `uvm_fatal ("memory_read_data_queue"   , "unexpected size")
                                end

                                mrd = memory_read_data_queue . pop_front ();

                                if (mrd_axi === mrd) begin
                                end else begin
                                        `uvm_fatal ("memory_read_data", $sformatf ("expecting 'h%0h", mrd))
                                end
                        end
                end

                        repeat (10) begin
                        @ (posedge processing_element_vif . clock);
                        end

////////////////////////////////////////////////////////////////////////////////

                phase . drop_objection (this);
        endtask

////////////////////////////////////////////////////////////////////////////////

endclass

