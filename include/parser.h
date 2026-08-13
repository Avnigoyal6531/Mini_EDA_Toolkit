#ifndef PARSER_H
#define PARSER_H

#define MAX_NAME 64
#define MAX_PORTS 32
#define MAX_GATES 64

/* Represents an input or output port */
typedef struct
{
    char name[MAX_NAME];
} Port;

/* Represents a gate in the Verilog netlist */
typedef struct
{
    char type[MAX_NAME];
    char instance[MAX_NAME];

    char output[MAX_NAME];
    char input1[MAX_NAME];
    char input2[MAX_NAME];

} Gate;

/* Represents a complete Verilog module */
typedef struct
{
    char name[MAX_NAME];

    Port inputs[MAX_PORTS];
    Port outputs[MAX_PORTS];

    int input_count;
    int output_count;

    Gate gates[MAX_GATES];
    int gate_count;

} Module;


int parse_verilog(const char *filename, Module *module);
void print_module(const Module *module);
void parseLine(char line[]);
extern Module current_module;

#endif