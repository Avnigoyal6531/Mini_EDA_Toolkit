module optimizer_test(a, b, c, y);

input a, b, c;
output y;

wire n1;
wire n2;

and G1(n1, a, 1'b1);
or  G2(n2, n1, 1'b0);

assign y = n2;

endmodule