#ifndef GRAPH_H
#define GRAPH_H

#include "parser.h"

#define MAX_NODES 100
#define MAX_CONNECTIONS 10

typedef struct
{
    int id;
    char name[50];
    char type[20];

    int connections[MAX_CONNECTIONS];
    int connection_count;

} GraphNode;

typedef struct
{
    GraphNode nodes[MAX_NODES];
    int node_count;

} Graph;

/* Graph functions */
void init_graph(Graph *graph);

int add_node(Graph *graph, const char *name, const char *type);
void add_edge(Graph *graph, int from, int to);

void print_graph(Graph *graph);
void build_graph_from_module(Graph *graph, const Module *module);

void dfs(Graph *graph, int start);
void bfs(Graph *graph, int start);
void topological_sort(Graph *graph);

#endif