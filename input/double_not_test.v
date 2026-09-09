module double_not_test(a, y);

input a;
output y;

wire n1;
wire n2;

not G1(n1, a);
not G2(n2, n1);

endmodule