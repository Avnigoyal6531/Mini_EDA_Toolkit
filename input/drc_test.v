module drc_test(a, b, c, y);

input a, b, c;
output y;

wire n1;
wire unused;

and G1(n1, a, b);
or  G2(unused, n1, c);

assign y = n1;

endmodule