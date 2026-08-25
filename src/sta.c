#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "sta.h"

float get_gate_delay(const char *type)
{
    if (strcmp(type, "AND") == 0)
        return 2.0;

    if (strcmp(type, "OR") == 0)
        return 2.0;

    if (strcmp(type, "NOT") == 0)
        return 1.0;

    if (strcmp(type, "NAND") == 0)
        return 1.5;

    if (strcmp(type, "NOR") == 0)
        return 1.5;

    if (strcmp(type, "XOR") == 0)
        return 3.0;

    return 2.0;
}

void init_sta(STA *sta)
{
    sta->node_count = 0;
    sta->clock_period = 10.0;
}

void add_sta_node(STA *sta, const char *name, const char *type, float delay)
{
    if (sta->node_count >= MAX_STA_NODES)
    {
        printf("STA node limit reached.\n");
        return;
    }

    strcpy(sta->nodes[sta->node_count].name, name);
    strcpy(sta->nodes[sta->node_count].type, type);

    if (delay <= 0.0)
        delay = get_gate_delay(type);

    sta->nodes[sta->node_count].delay = delay;
    sta->nodes[sta->node_count].arrival_time = 0.0;
    sta->nodes[sta->node_count].required_time = 0.0;
    sta->nodes[sta->node_count].slack = 0.0;

    sta->node_count++;
}

void calculate_arrival_times(STA *sta, Graph *graph, int order[])
{
    int i;
    int j;
    int current;
    int predecessor;
    float max_arrival;

    for (i = 0; i < sta->node_count; i++)
    {
        current = order[i];
        max_arrival = 0.0;

        /* Find all predecessors of the current node */
        for (j = 0; j < graph->node_count; j++)
        {
            int k;

            for (k = 0;
                 k < graph->nodes[j].connection_count;
                 k++)
            {
                predecessor = j;

                if (graph->nodes[j].connections[k] == current)
                {
                    if (sta->nodes[predecessor].arrival_time > max_arrival)
                    {
                        max_arrival =
                            sta->nodes[predecessor].arrival_time;
                    }
                }
            }
        }

        sta->nodes[current].arrival_time =
            max_arrival + sta->nodes[current].delay;
    }

    printf("\nArrival times calculated successfully.\n");
}

void calculate_required_times(STA *sta,
                              Graph *graph,
                              int order[],
                              int order_count)
{
    int i;
    int j;
    int current;
    int successor;
    float required;

    /* Initialize all required times to the clock period */
    for (i = 0; i < sta->node_count; i++)
    {
        sta->nodes[i].required_time = sta->clock_period;
    }

    /*
     * Process nodes in reverse topological order.
     */
    for (i = order_count - 1; i >= 0; i--)
    {
        current = order[i];
        required = sta->clock_period;

        /*
         * Find all successors of the current node.
         */
        for (j = 0; j < graph->nodes[current].connection_count; j++)
        {
            successor = graph->nodes[current].connections[j];

            /*
             * Required time at the current gate is limited
             * by the required time of its successor minus
             * the successor's delay.
             */
            float candidate =
                sta->nodes[successor].required_time -
                sta->nodes[successor].delay;

            if (candidate < required)
            {
                required = candidate;
            }
        }

        /*
         * If this node has successors, update its required time.
         */
        if (graph->nodes[current].connection_count > 0)
        {
            sta->nodes[current].required_time = required;
        }
    }

    printf("\nRequired times calculated successfully.\n");
}

void calculate_slack(STA *sta)
{
    int i;

    for (i = 0; i < sta->node_count; i++)
    {
        sta->nodes[i].slack =
            sta->nodes[i].required_time -
            sta->nodes[i].arrival_time;
    }

    printf("\nSlack calculated successfully.\n");
}

void print_sta_report(STA *sta)
{
    int i;

    printf("\n===== STATIC TIMING ANALYSIS =====\n");

    printf("Clock Period: %.2f\n\n", sta->clock_period);

    printf("%-10s %-10s %-10s %-15s %-15s %-10s\n",
           "Gate", "Type", "Delay", "Arrival", "Required", "Slack");

    for (i = 0; i < sta->node_count; i++)
    {
        printf("%-10s %-10s %-10.2f %-15.2f %-15.2f %-10.2f\n",
               sta->nodes[i].name,
               sta->nodes[i].type,
               sta->nodes[i].delay,
               sta->nodes[i].arrival_time,
               sta->nodes[i].required_time,
               sta->nodes[i].slack);
    }
}

void find_critical_path(STA *sta,
                        Graph *graph,
                        int order[],
                        int order_count)
{
    int i;
    int current;
    int best_predecessor;
    float best_arrival;

    if (order_count == 0)
    {
        printf("\nNo critical path found.\n");
        return;
    }

    current = order[order_count - 1];

    printf("\n===== CRITICAL PATH =====\n");

    /*
     * Work backwards from the final node.
     */
    printf("%s", sta->nodes[current].name);

    while (1)
    {
        best_predecessor = -1;
        best_arrival = -1.0;

        for (i = 0; i < graph->node_count; i++)
        {
            int j;

            for (j = 0;
                 j < graph->nodes[i].connection_count;
                 j++)
            {
                if (graph->nodes[i].connections[j] == current)
                {
                    if (sta->nodes[i].arrival_time > best_arrival)
                    {
                        best_arrival =
                            sta->nodes[i].arrival_time;

                        best_predecessor = i;
                    }
                }
            }
        }

        if (best_predecessor == -1)
        {
            break;
        }

        current = best_predecessor;

        printf(" <- %s", sta->nodes[current].name);
    }

    printf("\n=========================\n");
}