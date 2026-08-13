`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/10/2026 07:00:21 PM
// Design Name: 
// Module Name: Multi_Gate
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

module MULTI_GATE(a, b, c, y);

input a;
input b;
input c;

output y;

and G1(n1, a, b);
or  G2(n2, n1, c);
xor G3(n3, n2, a);
not G4(y, n3);

endmodule