
`timescale 1 ns / 1 ps

module pe_axi4_lite_slave #
(
// Users to add parameters here

// User parameters ends
// Do not modify the parameters beyond this line


// Parameters of Axi Slave Bus Interface S00_AXI
parameter integer C_S00_AXI_DATA_WIDTH= 32,
parameter integer C_S00_AXI_ADDR_WIDTH= 11,

// Parameters of Axi Slave Bus Interface S01_AXI
parameter integer C_S01_AXI_DATA_WIDTH= 32,
parameter integer C_S01_AXI_ADDR_WIDTH= 11
)
(
// Users to add ports here

// User ports ends
// Do not modify the ports beyond this line


// Ports of Axi Slave Bus Interface S00_AXI
input wire  s00_axi_aclk,
input wire  s00_axi_aresetn,
input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_awaddr,
input wire [2 : 0] s00_axi_awprot,
input wire  s00_axi_awvalid,
output wire  s00_axi_awready,
input wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_wdata,
input wire [(C_S00_AXI_DATA_WIDTH/8)-1 : 0] s00_axi_wstrb,
input wire  s00_axi_wvalid,
output wire  s00_axi_wready,
output wire [1 : 0] s00_axi_bresp,
output wire  s00_axi_bvalid,
input wire  s00_axi_bready,
input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_araddr,
input wire [2 : 0] s00_axi_arprot,
input wire  s00_axi_arvalid,
output wire  s00_axi_arready,
output wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_rdata,
output wire [1 : 0] s00_axi_rresp,
output wire  s00_axi_rvalid,
input wire  s00_axi_rready,

// Ports of Axi Slave Bus Interface S01_AXI
input wire  s01_axi_aclk,
input wire  s01_axi_aresetn,
input wire [C_S01_AXI_ADDR_WIDTH-1 : 0] s01_axi_awaddr,
input wire [2 : 0] s01_axi_awprot,
input wire  s01_axi_awvalid,
output wire  s01_axi_awready,
input wire [C_S01_AXI_DATA_WIDTH-1 : 0] s01_axi_wdata,
input wire [(C_S01_AXI_DATA_WIDTH/8)-1 : 0] s01_axi_wstrb,
input wire  s01_axi_wvalid,
output wire  s01_axi_wready,
output wire [1 : 0] s01_axi_bresp,
output wire  s01_axi_bvalid,
input wire  s01_axi_bready,
input wire [C_S01_AXI_ADDR_WIDTH-1 : 0] s01_axi_araddr,
input wire [2 : 0] s01_axi_arprot,
input wire  s01_axi_arvalid,
output wire  s01_axi_arready,
output wire [C_S01_AXI_DATA_WIDTH-1 : 0] s01_axi_rdata,
output wire [1 : 0] s01_axi_rresp,
output wire  s01_axi_rvalid,
input wire  s01_axi_rready
);
// Instantiation of Axi Bus Interface S00_AXI
pe_axi4_lite_slave_S00_AXI # (
.C_S_AXI_DATA_WIDTH(C_S00_AXI_DATA_WIDTH),
.C_S_AXI_ADDR_WIDTH(C_S00_AXI_ADDR_WIDTH)
) pe_axi4_lite_slave_S00_AXI_inst (
.S_AXI_ACLK(s00_axi_aclk),
.S_AXI_ARESETN(s00_axi_aresetn),
.S_AXI_AWADDR(s00_axi_awaddr),
.S_AXI_AWPROT(s00_axi_awprot),
.S_AXI_AWVALID(s00_axi_awvalid),
.S_AXI_AWREADY(s00_axi_awready),
.S_AXI_WDATA(s00_axi_wdata),
.S_AXI_WSTRB(s00_axi_wstrb),
.S_AXI_WVALID(s00_axi_wvalid),
.S_AXI_WREADY(s00_axi_wready),
.S_AXI_BRESP(s00_axi_bresp),
.S_AXI_BVALID(s00_axi_bvalid),
.S_AXI_BREADY(s00_axi_bready),
.S_AXI_ARADDR(s00_axi_araddr),
.S_AXI_ARPROT(s00_axi_arprot),
.S_AXI_ARVALID(s00_axi_arvalid),
.S_AXI_ARREADY(s00_axi_arready),
.S_AXI_RDATA(s00_axi_rdata),
.S_AXI_RRESP(s00_axi_rresp),
.S_AXI_RVALID(s00_axi_rvalid),
.S_AXI_RREADY(s00_axi_rready)
);

// Instantiation of Axi Bus Interface S01_AXI
pe_axi4_lite_slave_S01_AXI # (
.C_S_AXI_DATA_WIDTH(C_S01_AXI_DATA_WIDTH),
.C_S_AXI_ADDR_WIDTH(C_S01_AXI_ADDR_WIDTH)
) pe_axi4_lite_slave_S01_AXI_inst (
.S_AXI_ACLK(s01_axi_aclk),
.S_AXI_ARESETN(s01_axi_aresetn),
.S_AXI_AWADDR(s01_axi_awaddr),
.S_AXI_AWPROT(s01_axi_awprot),
.S_AXI_AWVALID(s01_axi_awvalid),
.S_AXI_AWREADY(s01_axi_awready),
.S_AXI_WDATA(s01_axi_wdata),
.S_AXI_WSTRB(s01_axi_wstrb),
.S_AXI_WVALID(s01_axi_wvalid),
.S_AXI_WREADY(s01_axi_wready),
.S_AXI_BRESP(s01_axi_bresp),
.S_AXI_BVALID(s01_axi_bvalid),
.S_AXI_BREADY(s01_axi_bready),
.S_AXI_ARADDR(s01_axi_araddr),
.S_AXI_ARPROT(s01_axi_arprot),
.S_AXI_ARVALID(s01_axi_arvalid),
.S_AXI_ARREADY(s01_axi_arready),
.S_AXI_RDATA(s01_axi_rdata),
.S_AXI_RRESP(s01_axi_rresp),
.S_AXI_RVALID(s01_axi_rvalid),
.S_AXI_RREADY(s01_axi_rready)
);

// Add user logic here

// User logic ends

endmodule
