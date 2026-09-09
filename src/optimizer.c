#include <stdio.h>
#include <string.h>
#include "optimizer.h"

void init_optimization_result(OptimizationResult *result)
{
    result->optimized_count = 0;
    result->removed_count = 0;

    result->and_identity_count = 0;
    result->or_identity_count = 0;
    result->and_zero_count = 0;
    result->or_one_count = 0;
    result->redundant_count = 0;

    result->not_zero_count = 0;
    result->not_one_count = 0;
    result->double_not_count = 0;
}

static int find_gate_by_output(const Module *module, const char *signal)
{
    int i;

    for (i = 0; i < module->gate_count; i++)
    {
        if (strcmp(module->gates[i].output, signal) == 0)
        {
            return i;
        }
    }

    return -1;
}

void optimize_module(Module *module, OptimizationResult *result)
{
    int i;

    init_optimization_result(result);

    for (i = 0; i < module->gate_count; i++)
    {
        Gate *gate = &module->gates[i];

        if (strcmp(gate->type, "AND") == 0)
        {
            /* A AND 0 -> 0 */
            if (strcmp(gate->input1, "1'b0") == 0 ||
                strcmp(gate->input2, "1'b0") == 0)
            {
                strcpy(gate->type, "CONST");
                strcpy(gate->input1, "1'b0");
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->and_zero_count++;
            }

            /* A AND 1 -> A */
            else if (strcmp(gate->input1, "1'b1") == 0)
            {
                strcpy(gate->type, "BUF");
                strcpy(gate->input1, gate->input2);
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->and_identity_count++;
            }

            else if (strcmp(gate->input2, "1'b1") == 0)
            {
                strcpy(gate->type, "BUF");
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->and_identity_count++;
            }

            /* A AND A -> A */
            else if (strcmp(gate->input1, gate->input2) == 0)
            {
                strcpy(gate->type, "BUF");
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->redundant_count++;
            }
        }

        else if (strcmp(gate->type, "OR") == 0)
        {
            /* A OR 1 -> 1 */
            if (strcmp(gate->input1, "1'b1") == 0 ||
                strcmp(gate->input2, "1'b1") == 0)
            {
                strcpy(gate->type, "CONST");
                strcpy(gate->input1, "1'b1");
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->or_one_count++;
            }

            /* A OR 0 -> A */
            else if (strcmp(gate->input1, "1'b0") == 0)
            {
                strcpy(gate->type, "BUF");
                strcpy(gate->input1, gate->input2);
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->or_identity_count++;
            }

            else if (strcmp(gate->input2, "1'b0") == 0)
            {
                strcpy(gate->type, "BUF");
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->or_identity_count++;
            }

            /* A OR A -> A */
            else if (strcmp(gate->input1, gate->input2) == 0)
            {
                strcpy(gate->type, "BUF");
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->redundant_count++;
            }
        }

        else if (strcmp(gate->type, "NOT") == 0)
        {
            int source_gate;

            /* NOT 0 -> 1 */
            if (strcmp(gate->input1, "1'b0") == 0)
            {
                strcpy(gate->type, "CONST");
                strcpy(gate->input1, "1'b1");
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->not_zero_count++;
            }

            /* NOT 1 -> 0 */
            else if (strcmp(gate->input1, "1'b1") == 0)
            {
                strcpy(gate->type, "CONST");
                strcpy(gate->input1, "1'b0");
                gate->input2[0] = '\0';

                result->optimized_count++;
                result->not_one_count++;
            }

            /* NOT(NOT(A)) -> A */
            else
            {
                source_gate = find_gate_by_output(module, gate->input1);

                if (source_gate >= 0 &&
                    strcmp(module->gates[source_gate].type, "NOT") == 0)
                {
                    strcpy(gate->type, "BUF");
                    strcpy(gate->input1,
                        module->gates[source_gate].input1);
                    gate->input2[0] = '\0';

                    result->optimized_count++;
                    result->double_not_count++;
                }
            }
        }
    }
}

void print_optimization_report(const OptimizationResult *result)
{
    printf("\n===== LOGIC OPTIMIZATION REPORT =====\n");

    printf("Optimizations Applied : %d\n", result->optimized_count);
    printf("Nodes Removed         : %d\n", result->removed_count);

    printf("\nOptimization Details:\n");
    printf("AND with 1            : %d\n",
           result->and_identity_count);
    printf("OR with 0             : %d\n",
           result->or_identity_count);
    printf("AND with 0            : %d\n",
           result->and_zero_count);
    printf("OR with 1             : %d\n",
           result->or_one_count);
    printf("Redundant gates       : %d\n",
           result->redundant_count);
    printf("NOT 0                 : %d\n",
           result->not_zero_count);
    printf("NOT 1                 : %d\n",
           result->not_one_count);
    printf("Double NOT             : %d\n",
           result->double_not_count);
    printf("=====================================\n");
}