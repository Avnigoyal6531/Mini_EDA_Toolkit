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


module test_gates(
    input a,
    input b,
    input c,
    output y
    );
    
    wire n1;
    wire n2;
    wire n3;
    wire n4;
    wire n5;
    wire n6;
    
    and G1(n1, a, b);
    or G2(n2, n1, c);
    not G3(n3, n2);
    nand G4(n4, a, c);
    nor G5(n5, b, c);
    xor G6(n6, n3, n4);
    xnor G7(y,n5, n6); 
    
endmodule
