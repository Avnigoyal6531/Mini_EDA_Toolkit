module same_input_test(a, y);

input a;
output y;

wire n1;
wire n2;

and G1(n1, a, a);
or  G2(n2, n1, n1);

endmodule