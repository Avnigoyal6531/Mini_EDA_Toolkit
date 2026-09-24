#include <stdio.h>
#include "parser.h"
#include "graph.h"
#include "ast.h"
#include "sta.h"
#include "drc.h"
#include "optimizer.h"
#include "power.h"

int main(int argc, char *argv[])
{
    FILE *file;
    char line[256];

    Graph graph;
    ASTModule ast;
    STA sta;
    DRC drc;
    OptimizationResult optimization_result;
    PowerReport power_report;
    int order[MAX_NODES];
    int order_count;

    /* Check command-line argument */
    if (argc < 2)
    {
        printf("Usage: %s <verilog_file>\n", argv[0]);
        return 1;
    }

    /* Open Verilog file */
    file = fopen(argv[1], "r");

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

    /* Perform logic optimization */
    optimize_module(&current_module, &optimization_result);

    /* Display optimization report */
    print_optimization_report(&optimization_result);

    /* Build AST from optimized module */
    build_ast(&ast, &current_module);

    /* Display AST */
    print_ast(&ast);

    /* Initialize graph */
    init_graph(&graph);

    /* Build graph from parsed module */
    build_graph_from_module(&graph, &current_module);

    /* Display graph */
    print_graph(&graph);

    /* Initialize Design Rule Checker */
    init_drc(&drc);

    /* Perform Design Rule Checks */
    run_drc(&drc, &graph, &current_module);

    /* Display DRC report */
    print_drc_report(&drc);

    /* Perform DFS starting from node 0 */
    dfs(&graph, 0);

    /* Perform BFS starting from node 0 */
    bfs(&graph, 0);

    /* Perform Topological Sort */
    topological_sort(&graph);

    /* Initialize Static Timing Analysis */
    init_sta(&sta);

    /* Add graph nodes to STA */
    for (int i = 0; i < graph.node_count; i++)
    {
        add_sta_node(&sta,
                 graph.nodes[i].name,
                 graph.nodes[i].type,
                 0.0);
    }

    /* Get topological order */
    order_count = get_topological_order(&graph, order);

    /* Perform arrival-time analysis */
    if (order_count == graph.node_count)
    {
        calculate_arrival_times(&sta, &graph, order);

        calculate_required_times(&sta,
                         &graph,
                         order,
                         order_count);

        calculate_slack(&sta);

        print_sta_report(&sta);

        find_critical_path(&sta,
                   &graph,
                   order,
                   order_count);
    }
    else
    {
        printf("\nError: Circuit contains a cycle. STA cannot be performed.\n");
    }
        /* Initialize Power Estimation */
    init_power_report(&power_report);

    /* Add graph nodes for power estimation */
    for (int i = 0; i < graph.node_count; i++)
    {
        add_power_node(&power_report,
                       graph.nodes[i].name,
                       graph.nodes[i].type,
                       0.5,
                       1.0,
                       1.0,
                       1000000.0);
    }

    /* Calculate estimated power */
    calculate_power(&power_report);

    /* Display power report */
    print_power_report(&power_report);

    /* Generate CSV report */
    if (generate_power_csv(&power_report, "power_report.csv"))
    {
        printf("Power CSV report generated successfully.\n");
    }
    else
    {
        printf("Error: Could not generate power CSV report.\n");
    }

    return 0;
}