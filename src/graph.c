#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "parser.h"

void init_graph(Graph *graph)
{
    graph->node_count = 0;

    for (int i = 0; i < MAX_NODES; i++)
    {
        graph->nodes[i].id = -1;
        graph->nodes[i].name[0] = '\0';
        graph->nodes[i].type[0] = '\0';
        graph->nodes[i].connection_count = 0;

        for (int j = 0; j < MAX_CONNECTIONS; j++)
        {
            graph->nodes[i].connections[j] = -1;
        }
    }
}

int add_node(Graph *graph, const char *name, const char *type)
{
    if (graph->node_count >= MAX_NODES)
    {
        printf("Error: Maximum number of graph nodes reached.\n");
        return -1;
    }

    int id = graph->node_count;

    graph->nodes[id].id = id;

    snprintf(graph->nodes[id].name,
             sizeof(graph->nodes[id].name),
             "%s",
             name);

    snprintf(graph->nodes[id].type,
             sizeof(graph->nodes[id].type),
             "%s",
             type);

    graph->nodes[id].connection_count = 0;

    graph->node_count++;

    return id;
}

void add_edge(Graph *graph, int from, int to)
{
    if (from < 0 || from >= graph->node_count ||
        to < 0 || to >= graph->node_count)
    {
        printf("Error: Invalid graph node.\n");
        return;
    }

    if (graph->nodes[from].connection_count >= MAX_CONNECTIONS)
    {
        printf("Error: Maximum connections reached for node %d.\n", from);
        return;
    }

    graph->nodes[from].connections[
        graph->nodes[from].connection_count
    ] = to;

    graph->nodes[from].connection_count++;
}

void print_graph(Graph *graph)
{
    printf("\n========== CIRCUIT GRAPH ==========\n");

    for (int i = 0; i < graph->node_count; i++)
    {
        printf("Node %d: %s (%s)", 
               graph->nodes[i].id,
               graph->nodes[i].name,
               graph->nodes[i].type);

        if (graph->nodes[i].connection_count == 0)
        {
            printf(" -> No connections");
        }
        else
        {
            printf(" -> ");

            for (int j = 0;
                 j < graph->nodes[i].connection_count;
                 j++)
            {
                int next = graph->nodes[i].connections[j];

                printf("%s",
                       graph->nodes[next].name);

                if (j < graph->nodes[i].connection_count - 1)
                {
                    printf(", ");
                }
            }
        }

        printf("\n");
    }

    printf("===================================\n");
}

void build_graph_from_module(Graph *graph, const Module *module)
{
    int i;
    int j;

    /* Add every gate as a graph node */
    for (i = 0; i < module->gate_count; i++)
    {
        add_node(graph,
                 module->gates[i].instance,
                 module->gates[i].type);
    }

    /* Connect gates using signal names */
    for (i = 0; i < module->gate_count; i++)
    {
        for (j = 0; j < module->gate_count; j++)
        {
            if (i != j)
            {
                if (module->gates[i].output[0] != '\0' &&
                    (strcmp(module->gates[i].output,
                            module->gates[j].input1) == 0 ||
                     strcmp(module->gates[i].output,
                            module->gates[j].input2) == 0))
                {
                    add_edge(graph, i, j);
                }
            }
        }
    }
}

void dfs(Graph *graph, int start)
{
    int i;
    int j;

    int visited[MAX_NODES] = {0};

    int stack[MAX_NODES];
    int top = -1;

    /* Push starting node */
    stack[++top] = start;

    printf("\nDFS Traversal: ");

    while (top >= 0)
    {
        int current = stack[top--];

        /* Skip if already visited */
        if (visited[current])
        {
            continue;
        }

        visited[current] = 1;

        printf("%s", graph->nodes[current].name);

        /* Print separator */
        if (top >= -1)
        {
            printf(" ");
        }

        /* Push connected nodes */
        for (i = graph->nodes[current].connection_count - 1;
             i >= 0;
             i--)
        {
            j = graph->nodes[current].connections[i];

            if (!visited[j])
            {
                stack[++top] = j;
            }
        }
    }

    printf("\n");
}

void bfs(Graph *graph, int start)
{
    int i;
    int current;
    int next;

    int visited[MAX_NODES] = {0};

    int queue[MAX_NODES];
    int front = 0;
    int rear = 0;

    /* Add starting node to queue */
    queue[rear++] = start;
    visited[start] = 1;

    printf("\nBFS Traversal: ");

    while (front < rear)
    {
        current = queue[front++];

        printf("%s ", graph->nodes[current].name);

        /* Add connected nodes to queue */
        for (i = 0;
             i < graph->nodes[current].connection_count;
             i++)
        {
            next = graph->nodes[current].connections[i];

            if (!visited[next])
            {
                visited[next] = 1;
                queue[rear++] = next;
            }
        }
    }

    printf("\n");
}

void topological_sort(Graph *graph)
{
    int indegree[MAX_NODES] = {0};
    int queue[MAX_NODES];

    int front = 0;
    int rear = 0;

    int i;
    int j;
    int current;
    int next;

    /* Calculate indegree of every node */
    for (i = 0; i < graph->node_count; i++)
    {
        for (j = 0;
             j < graph->nodes[i].connection_count;
             j++)
        {
            next = graph->nodes[i].connections[j];
            indegree[next]++;
        }
    }

    /* Add nodes with indegree 0 */
    for (i = 0; i < graph->node_count; i++)
    {
        if (indegree[i] == 0)
        {
            queue[rear++] = i;
        }
    }

    printf("\nTopological Sort: ");

    /* Process nodes */
    while (front < rear)
    {
        current = queue[front++];

        printf("%s ", graph->nodes[current].name);

        for (j = 0;
             j < graph->nodes[current].connection_count;
             j++)
        {
            next = graph->nodes[current].connections[j];

            indegree[next]--;

            if (indegree[next] == 0)
            {
                queue[rear++] = next;
            }
        }
    }

    printf("\n");
}

int get_topological_order(Graph *graph, int order[])
{
    int indegree[MAX_NODES] = {0};
    int queue[MAX_NODES];

    int front = 0;
    int rear = 0;
    int count = 0;

    int i;
    int j;
    int current;
    int next;

    /* Calculate indegree of every node */
    for (i = 0; i < graph->node_count; i++)
    {
        for (j = 0;
             j < graph->nodes[i].connection_count;
             j++)
        {
            next = graph->nodes[i].connections[j];
            indegree[next]++;
        }
    }

    /* Add nodes with indegree 0 */
    for (i = 0; i < graph->node_count; i++)
    {
        if (indegree[i] == 0)
        {
            queue[rear++] = i;
        }
    }

    /* Generate topological order */
    while (front < rear)
    {
        current = queue[front++];

        order[count++] = current;

        for (j = 0;
             j < graph->nodes[current].connection_count;
             j++)
        {
            next = graph->nodes[current].connections[j];

            indegree[next]--;

            if (indegree[next] == 0)
            {
                queue[rear++] = next;
            }
        }
    }

    return count;
}