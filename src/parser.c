#include <stdio.h>
#include <string.h>
#include "../include/parser.h"

Module current_module;

static char *next_gate_token(void)
{
    char *token;

    token = strtok(NULL, "(,); \t\r\n");

    return token;
}

void parseLine(char line[])
{
    char *word;

    word = strtok(line, " \t\r\n");

    if(word == NULL)
    return;

    if(strncmp(word, "//", 2) == 0)
    return;

/* Ignore Verilog compiler directives such as `timescale */
    if(word[0] == '`')
    return;

/* Ignore wire declarations */
    if(strcmp(word,"wire")==0)
    return;

    if(strcmp(word,");")==0)
    return;

    if(strcmp(word,"module")==0)
{
    char *moduleName;

    moduleName = strtok(NULL, " (");

    if(moduleName != NULL)
    {
        strcpy(current_module.name, moduleName);
    }

    current_module.input_count = 0;
    current_module.output_count = 0;
    current_module.gate_count = 0;

    printf("Module Declaration Found\n");
    printf("Module Name : %s\n", current_module.name);
}

    else if(strcmp(word,"input")==0)
{
    char *name;

    name = strtok(NULL," ,;");

    if(name != NULL && current_module.input_count < MAX_PORTS)
    {
        strcpy(current_module.inputs[current_module.input_count].name, name);
        current_module.input_count++;
    }

    printf("Input Name : %s\n",name);
}

    else if(strcmp(word,"output")==0)
{
    char *name;

    name = strtok(NULL," ,;");

    if(name != NULL && current_module.output_count < MAX_PORTS)
    {
        strcpy(current_module.outputs[current_module.output_count].name, name);
        current_module.output_count++;
    }

    printf("Output Name : %s\n",name);
}

    else if(strcmp(word,"and")==0)
{
    char *gateName;
    char *output;
    char *input1;
    char *input2;

    gateName = next_gate_token();
    output = next_gate_token();
    input1 = next_gate_token();
    input2 = next_gate_token();

    if(gateName != NULL &&
       output != NULL &&
       input1 != NULL &&
       input2 != NULL &&
       current_module.gate_count < MAX_GATES)
    {
        Gate *gate = &current_module.gates[current_module.gate_count];

        strcpy(gate->type, "AND");
        strcpy(gate->instance, gateName);
        strcpy(gate->output, output);
        strcpy(gate->input1, input1);
        strcpy(gate->input2, input2);

        current_module.gate_count++;
    }

    printf("\n");
    printf("Gate Type : AND\n");
    printf("Gate Name : %s\n",gateName);
    printf("Output    : %s\n",output);
    printf("Input1    : %s\n",input1);
    printf("Input2    : %s\n",input2);
}

    else if(strcmp(word,"or")==0)
{
    char *gateName;
    char *output;
    char *input1;
    char *input2;

    gateName = next_gate_token();
    output = next_gate_token();
    input1 = next_gate_token();
    input2 = next_gate_token();

    if(gateName != NULL &&
       output != NULL &&
       input1 != NULL &&
       input2 != NULL &&
       current_module.gate_count < MAX_GATES)
    {
        Gate *gate = &current_module.gates[current_module.gate_count];

        strcpy(gate->type, "OR");
        strcpy(gate->instance, gateName);
        strcpy(gate->output, output);
        strcpy(gate->input1, input1);
        strcpy(gate->input2, input2);

        current_module.gate_count++;
    }

    printf("\n");
    printf("Gate Type : OR\n");
    printf("Gate Name : %s\n",gateName);
    printf("Output    : %s\n",output);
    printf("Input1    : %s\n",input1);
    printf("Input2    : %s\n",input2);
}

   else if(strcmp(word,"xor")==0)
{
    char *gateName;
    char *output;
    char *input1;
    char *input2;

    gateName = next_gate_token();
    output = next_gate_token();
    input1 = next_gate_token();
    input2 = next_gate_token();

    if(gateName != NULL &&
       output != NULL &&
       input1 != NULL &&
       input2 != NULL &&
       current_module.gate_count < MAX_GATES)
    {
        Gate *gate = &current_module.gates[current_module.gate_count];

        strcpy(gate->type, "XOR");
        strcpy(gate->instance, gateName);
        strcpy(gate->output, output);
        strcpy(gate->input1, input1);
        strcpy(gate->input2, input2);

        current_module.gate_count++;
    }

    printf("\n");
    printf("Gate Type : XOR\n");
    printf("Gate Name : %s\n",gateName);
    printf("Output    : %s\n",output);
    printf("Input1    : %s\n",input1);
    printf("Input2    : %s\n",input2);
}

else if(strcmp(word,"nand")==0)
{
    char *gateName;
    char *output;
    char *input1;
    char *input2;

    gateName = next_gate_token();
    output = next_gate_token();
    input1 = next_gate_token();
    input2 = next_gate_token();

    if(gateName != NULL &&
       output != NULL &&
       input1 != NULL &&
       input2 != NULL &&
       current_module.gate_count < MAX_GATES)
    {
        Gate *gate = &current_module.gates[current_module.gate_count];

        strcpy(gate->type, "NAND");
        strcpy(gate->instance, gateName);
        strcpy(gate->output, output);
        strcpy(gate->input1, input1);
        strcpy(gate->input2, input2);

        current_module.gate_count++;
    }

    printf("\n");
    printf("Gate Type : NAND\n");
    printf("Gate Name : %s\n", gateName);
    printf("Output    : %s\n", output);
    printf("Input1    : %s\n", input1);
    printf("Input2    : %s\n", input2);
}

else if(strcmp(word,"nor")==0)
{
    char *gateName;
    char *output;
    char *input1;
    char *input2;

    gateName = next_gate_token();
    output = next_gate_token();
    input1 = next_gate_token();
    input2 = next_gate_token();

    if(gateName != NULL &&
       output != NULL &&
       input1 != NULL &&
       input2 != NULL &&
       current_module.gate_count < MAX_GATES)
    {
        Gate *gate = &current_module.gates[current_module.gate_count];

        strcpy(gate->type, "NOR");
        strcpy(gate->instance, gateName);
        strcpy(gate->output, output);
        strcpy(gate->input1, input1);
        strcpy(gate->input2, input2);

        current_module.gate_count++;
    }

    printf("\n");
    printf("Gate Type : NOR\n");
    printf("Gate Name : %s\n", gateName);
    printf("Output    : %s\n", output);
    printf("Input1    : %s\n", input1);
    printf("Input2    : %s\n", input2);
}

else if(strcmp(word,"xnor")==0)
{
    char *gateName;
    char *output;
    char *input1;
    char *input2;

    gateName = next_gate_token();
    output = next_gate_token();
    input1 = next_gate_token();
    input2 = next_gate_token();

    if(gateName != NULL &&
       output != NULL &&
       input1 != NULL &&
       input2 != NULL &&
       current_module.gate_count < MAX_GATES)
    {
        Gate *gate = &current_module.gates[current_module.gate_count];

        strcpy(gate->type, "XNOR");
        strcpy(gate->instance, gateName);
        strcpy(gate->output, output);
        strcpy(gate->input1, input1);
        strcpy(gate->input2, input2);

        current_module.gate_count++;
    }

    printf("\n");
    printf("Gate Type : XNOR\n");
    printf("Gate Name : %s\n", gateName);
    printf("Output    : %s\n", output);
    printf("Input1    : %s\n", input1);
    printf("Input2    : %s\n", input2);
}

    else if(strcmp(word,"not")==0)
{
    char *gateName;
    char *output;
    char *input1;

    gateName = next_gate_token();
    output = next_gate_token();
    input1 = next_gate_token();


    if(gateName != NULL &&
       output != NULL &&
       input1 != NULL &&
       current_module.gate_count < MAX_GATES)
    {
        Gate *gate = &current_module.gates[current_module.gate_count];

        strcpy(gate->type, "NOT");
        strcpy(gate->instance, gateName);
        strcpy(gate->output, output);
        strcpy(gate->input1, input1);

        /* NOT gate has only one input */
        gate->input2[0] = '\0';

        current_module.gate_count++;
    }

    printf("\n");
    printf("Gate Type : NOT\n");
    printf("Gate Name : %s\n",gateName);
    printf("Output    : %s\n",output);
    printf("Input1    : %s\n",input1);
}

    else if(strcmp(word,"endmodule")==0)
    {
        printf("End of Module Found\n");
    }

    else
    {
    printf("Warning: Unknown statement or keyword : %s\n", word);
    }

}

void print_module(const Module *module)
{
    int i;

    printf("\n");
    printf("========== PARSED MODULE ==========\n");

    printf("\nModule Name : %s\n", module->name);

    printf("\nInputs:\n");

    for(i = 0; i < module->input_count; i++)
    {
        printf("  %d. %s\n",
               i + 1,
               module->inputs[i].name);
    }

    printf("\nOutputs:\n");

    for(i = 0; i < module->output_count; i++)
    {
        printf("  %d. %s\n",
               i + 1,
               module->outputs[i].name);
    }

    printf("\nGates:\n");

    for(i = 0; i < module->gate_count; i++)
    {
        printf("\n");
        printf("  Gate %d\n", i + 1);
        printf("    Type   : %s\n", module->gates[i].type);
        printf("    Name   : %s\n", module->gates[i].instance);
        printf("    Output : %s\n", module->gates[i].output);
        printf("    Input1 : %s\n", module->gates[i].input1);

        if(strlen(module->gates[i].input2) > 0)
        {
            printf("    Input2 : %s\n", module->gates[i].input2);
        }
    }

    printf("\n===================================\n");
}