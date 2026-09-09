module all_optimization_test(a, b, c, d, y);

input a, b, c, d;
output y;

wire n1;
wire n2;
wire n3;
wire n4;
wire n5;
wire n6;

and G1(n1, a, 1'b1);
or  G2(n2, b, 1'b0);
and G3(n3, c, 1'b0);
or  G4(n4, d, 1'b1);
and G5(n5, n1, n1);
or  G6(n6, n2, n2);

endmodule