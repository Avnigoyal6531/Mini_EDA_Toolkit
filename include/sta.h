#ifndef STA_H
#define STA_H

#include "graph.h"

#define MAX_STA_NODES 100

typedef struct
{
    char name[50];
    char type[20];

    float delay;
    float arrival_time;
    float required_time;
    float slack;

} STANode;

typedef struct
{
    STANode nodes[MAX_STA_NODES];
    int node_count;

    float clock_period;

} STA;

void init_sta(STA *sta);
void add_sta_node(STA *sta, const char *name, const char *type, float delay);
void calculate_arrival_times(STA *sta, Graph *graph, int order[]);
void calculate_required_times(STA *sta, Graph *graph, int order[], int order_count);
void calculate_slack(STA *sta);
void print_sta_report(STA *sta);

float get_gate_delay(const char *type);
void find_critical_path(STA *sta, Graph *graph, int order[], int order_count);

#endif