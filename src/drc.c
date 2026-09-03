#include <stdio.h>
#include <string.h>
#include "drc.h"

/* Initialize DRC structure */
void init_drc(DRC *drc)
{
    if (drc == NULL)
        return;

    drc->violation_count = 0;
}

/* Convert violation type to string */
const char *get_drc_violation_type(DRCViolationType type)
{
    switch (type)
    {
        case DRC_UNDRIVEN_NET:
            return "UNDRIVEN NET";

        case DRC_MULTIPLE_DRIVERS:
            return "MULTIPLE DRIVERS";

        case DRC_UNCONNECTED_INPUT:
            return "UNCONNECTED INPUT";

        case DRC_UNCONNECTED_OUTPUT:
            return "UNCONNECTED OUTPUT";

        default:
            return "UNKNOWN";
    }
}

/* Add a DRC violation */
void add_drc_violation(
    DRC *drc,
    DRCViolationType type,
    const char *net_name,
    const char *message)
{
    if (drc == NULL)
        return;

    if (drc->violation_count >= MAX_DRC_VIOLATIONS)
        return;

    drc->violations[drc->violation_count].type = type;

    strncpy(
        drc->violations[drc->violation_count].net_name,
        net_name,
        sizeof(drc->violations[drc->violation_count].net_name) - 1
    );

    drc->violations[drc->violation_count]
        .net_name[sizeof(drc->violations[drc->violation_count].net_name) - 1] = '\0';

    strncpy(
        drc->violations[drc->violation_count].message,
        message,
        sizeof(drc->violations[drc->violation_count].message) - 1
    );

    drc->violations[drc->violation_count]
        .message[sizeof(drc->violations[drc->violation_count].message) - 1] = '\0';

    drc->violation_count++;
}

/* Run basic DRC checks */
void run_drc(DRC *drc, Graph *graph, const Module *module)
{
    int i;
    int j;
    int is_module_output;

    if (drc == NULL || graph == NULL || module == NULL)
        return;

    for (i = 0; i < graph->node_count; i++)
    {
        GraphNode *node = &graph->nodes[i];

        is_module_output = 0;

        /*
         * Find the corresponding gate in the parsed module.
         * The graph node name is the gate instance name.
         */
        for (j = 0; j < module->gate_count; j++)
        {
            if (strcmp(node->name, module->gates[j].instance) == 0)
            {
                /*
                 * Check whether this gate drives a declared
                 * module output.
                 */
                int k;

                for (k = 0; k < module->output_count; k++)
                {
                    if (strcmp(module->gates[j].output,
                               module->outputs[k].name) == 0)
                    {
                        is_module_output = 1;
                        break;
                    }
                }

                break;
            }
        }

        /*
         * A node with no outgoing gate connection is valid
         * when its output is a module output.
         */
        if (node->connection_count == 0 && !is_module_output)
        {
            add_drc_violation(
                drc,
                DRC_UNCONNECTED_OUTPUT,
                node->name,
                "Gate output is not connected to another gate or module output."
            );
        }
    }
}

/* Print DRC report */
void print_drc_report(DRC *drc)
{
    int i;

    if (drc == NULL)
        return;

    printf("\n===== DRC REPORT =====\n");

    if (drc->violation_count == 0)
    {
        printf("No DRC violations found.\n");
        return;
    }

    printf("Total Violations : %d\n\n", drc->violation_count);

    for (i = 0; i < drc->violation_count; i++)
    {
        printf("Violation %d\n", i + 1);

        printf("Type    : %s\n",
               get_drc_violation_type(drc->violations[i].type));

        printf("Net     : %s\n",
               drc->violations[i].net_name);

        printf("Message : %s\n\n",
               drc->violations[i].message);
    }
}