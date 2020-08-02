`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/28 20:29:14
// Design Name: 
// Module Name: testbench
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module testbench();
 reg clk_100MHz;
 wire clkout1;
 wire clkout2;

 always #5 clk_100MHz = ~clk_100MHz;

 initial begin
    clk_100MHz = 0;
 end
 
 clk_wiz_0 test(
    .clk_in1(clk_100MHz),
    .clk_out1(clkout1),
    .clk_out2(clkout2) 
 );
 
endmodule
