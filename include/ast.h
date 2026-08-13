#ifndef AST_H
#define AST_H

#include "parser.h"

#define MAX_AST_GATES 64

typedef struct
{
    char type[MAX_NAME];
    char instance[MAX_NAME];

    char output[MAX_NAME];
    char input1[MAX_NAME];
    char input2[MAX_NAME];

} ASTGate;


typedef struct
{
    char name[MAX_NAME];

    char inputs[MAX_PORTS][MAX_NAME];
    char outputs[MAX_PORTS][MAX_NAME];

    int input_count;
    int output_count;

    ASTGate gates[MAX_AST_GATES];
    int gate_count;

} ASTModule;


/* AST functions */

void init_ast(ASTModule *ast);

void build_ast(ASTModule *ast, const Module *module);

void print_ast(const ASTModule *ast);

#endif