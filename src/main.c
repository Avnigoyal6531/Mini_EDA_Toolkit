#include <stdio.h>
#include "parser.h"
#include "graph.h"
#include "ast.h"

int main()
{
    FILE *file;
    char line[256];

    Graph graph;
    ASTModule ast;

    /* Open Verilog file */
    file = fopen("input/test_gates.v", "r");

    if (file == NULL)
    {
        printf("Error: Could not open Verilog file.\n");
        return 1;
    }

    /* Initialize parser data */
    current_module.input_count = 0;
    current_module.output_count = 0;
    current_module.gate_count = 0;

    /* Parse the Verilog file line by line */
    while (fgets(line, sizeof(line), file) != NULL)
    {
        parseLine(line);
    }

    fclose(file);

    /* Build AST from parsed module */
    build_ast(&ast, &current_module);

    /* Display AST */
    print_ast(&ast);

    /* Initialize graph */
    init_graph(&graph);

    /* Build graph from parsed module */
    build_graph_from_module(&graph, &current_module);

    /* Display graph */
    print_graph(&graph);

    /* Perform DFS starting from node 0 */
    dfs(&graph, 0);

    /* Perform BFS starting from node 0 */
    bfs(&graph, 0);

    /* Perform Topological Sort */
    topological_sort(&graph);

    return 0;
}