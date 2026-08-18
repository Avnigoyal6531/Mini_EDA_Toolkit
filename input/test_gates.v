`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/10/2026 07:19:51 PM
// Design Name: 
// Module Name: test_gates
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


module fanout_test(a, b, c, y);

input a;
input b;
input c;

output y;

wire n1;
wire n2;
wire n3;

and G1(n1, a, b);
or  G2(n2, n1, c);
xor G3(n3, n1, a);
and G4(y, n2, n3);

endmodule