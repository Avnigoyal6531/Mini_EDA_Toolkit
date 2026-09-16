#ifndef POWER_H
#define POWER_H

#include "graph.h"

#define MAX_POWER_NODES 100

typedef struct
{
    char name[50];
    char type[20];
    double activity;
    double capacitance;
    double voltage;
    double frequency;
    double power;
} PowerNode;

typedef struct
{
    PowerNode nodes[MAX_POWER_NODES];
    int node_count;
    double total_power;
} PowerReport;

void init_power_report(PowerReport *report);

void add_power_node(PowerReport *report,
                    const char *name,
                    const char *type,
                    double activity,
                    double capacitance,
                    double voltage,
                    double frequency);

void calculate_power(PowerReport *report);

void print_power_report(const PowerReport *report);

int generate_power_csv(const PowerReport *report,
                       const char *filename);

#endif