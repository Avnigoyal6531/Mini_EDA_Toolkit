#include <stdio.h>
#include <string.h>

#include "power.h"

void init_power_report(PowerReport *report)
{
    if (report == NULL)
        return;

    report->node_count = 0;
    report->total_power = 0.0;
}

void add_power_node(PowerReport *report,
                    const char *name,
                    const char *type,
                    double activity,
                    double capacitance,
                    double voltage,
                    double frequency)
{
    PowerNode *node;

    if (report == NULL || name == NULL || type == NULL)
        return;

    if (report->node_count >= MAX_POWER_NODES)
        return;

    node = &report->nodes[report->node_count];

    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';

    strncpy(node->type, type, sizeof(node->type) - 1);
    node->type[sizeof(node->type) - 1] = '\0';

    node->activity = activity;
    node->capacitance = capacitance;
    node->voltage = voltage;
    node->frequency = frequency;
    node->power = 0.0;

    report->node_count++;
}

void calculate_power(PowerReport *report)
{
    int i;

    if (report == NULL)
        return;

    report->total_power = 0.0;

    for (i = 0; i < report->node_count; i++)
    {
        PowerNode *node = &report->nodes[i];

        /*
         * Dynamic power estimation:
         *
         * P = alpha * C * V^2 * f
         *
         * alpha       = switching activity
         * C           = capacitance
         * V           = supply voltage
         * f           = operating frequency
         */
        node->power =
            node->activity *
            node->capacitance *
            node->voltage *
            node->voltage *
            node->frequency;

        report->total_power += node->power;
    }
}

void print_power_report(const PowerReport *report)
{
    int i;

    if (report == NULL)
        return;

    printf("\n===== POWER ESTIMATION =====\n");

    for (i = 0; i < report->node_count; i++)
    {
        printf("Gate %-10s Type: %-8s Power: %.6f\n",
               report->nodes[i].name,
               report->nodes[i].type,
               report->nodes[i].power);
    }

    printf("----------------------------------\n");
    printf("Total Estimated Power : %.6f\n", report->total_power);
    printf("==================================\n");
}

int generate_power_csv(const PowerReport *report,
                       const char *filename)
{
    FILE *file;
    int i;

    if (report == NULL || filename == NULL)
        return 0;

    file = fopen(filename, "w");

    if (file == NULL)
        return 0;

    fprintf(file,
            "Gate,Type,Activity,Capacitance,Voltage,Frequency,Power\n");

    for (i = 0; i < report->node_count; i++)
    {
        const PowerNode *node = &report->nodes[i];

        fprintf(file,
                "%s,%s,%.4f,%.4f,%.4f,%.4f,%.6f\n",
                node->name,
                node->type,
                node->activity,
                node->capacitance,
                node->voltage,
                node->frequency,
                node->power);
    }

    fprintf(file, "TOTAL,,,,,,%.6f\n", report->total_power);

    fclose(file);

    return 1;
}