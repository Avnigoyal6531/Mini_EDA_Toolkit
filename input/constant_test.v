module constant_test(a, b, y);

input a, b;
output y;

wire n1;
wire n2;

and G1(n1, a, 1'b0);
or  G2(n2, b, 1'b1);

endmodule