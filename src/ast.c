#include <stdio.h>
#include <string.h>

#include "ast.h"


void init_ast(ASTModule *ast)
{
    int i;

    memset(ast, 0, sizeof(ASTModule));

    for (i = 0; i < MAX_AST_GATES; i++)
    {
        ast->gates[i].type[0] = '\0';
        ast->gates[i].instance[0] = '\0';
        ast->gates[i].output[0] = '\0';
        ast->gates[i].input1[0] = '\0';
        ast->gates[i].input2[0] = '\0';
    }
}


void build_ast(ASTModule *ast, const Module *module)
{
    int i;

    init_ast(ast);

    /* Copy module name */
    strcpy(ast->name, module->name);

    /* Copy inputs */
    ast->input_count = module->input_count;

    for (i = 0; i < module->input_count; i++)
    {
        strcpy(ast->inputs[i], module->inputs[i].name);
    }

    /* Copy outputs */
    ast->output_count = module->output_count;

    for (i = 0; i < module->output_count; i++)
    {
        strcpy(ast->outputs[i], module->outputs[i].name);
    }

    /* Copy gates */
    ast->gate_count = module->gate_count;

    for (i = 0; i < module->gate_count; i++)
    {
        strcpy(ast->gates[i].type,
               module->gates[i].type);

        strcpy(ast->gates[i].instance,
               module->gates[i].instance);

        strcpy(ast->gates[i].output,
               module->gates[i].output);

        strcpy(ast->gates[i].input1,
               module->gates[i].input1);

        strcpy(ast->gates[i].input2,
               module->gates[i].input2);
    }
}


void print_ast(const ASTModule *ast)
{
    int i;

    printf("\n========== AST ==========\n");

    printf("Module: %s\n", ast->name);

    printf("\nInputs:\n");

    for (i = 0; i < ast->input_count; i++)
    {
        printf("  %s\n", ast->inputs[i]);
    }

    printf("\nOutputs:\n");

    for (i = 0; i < ast->output_count; i++)
    {
        printf("  %s\n", ast->outputs[i]);
    }

    printf("\nGates:\n");

    for (i = 0; i < ast->gate_count; i++)
    {
        printf("  Gate Type : %s\n",
               ast->gates[i].type);

        printf("  Instance  : %s\n",
               ast->gates[i].instance);

        printf("  Output    : %s\n",
               ast->gates[i].output);

        printf("  Input 1   : %s\n",
               ast->gates[i].input1);

        printf("  Input 2   : %s\n\n",
               ast->gates[i].input2);
    }

    printf("=========================\n");
}