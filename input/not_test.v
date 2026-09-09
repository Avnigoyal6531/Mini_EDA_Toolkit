module not_test(a, y);

input a;
output y;

wire n1;
wire n2;

not G1(n1, 1'b0);
not G2(n2, 1'b1);

endmodule