#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "parser.h"

/* Optimization result */
typedef struct
{
    int optimized_count;
    int removed_count;

    int and_identity_count;
    int or_identity_count;
    int and_zero_count;
    int or_one_count;
    int redundant_count;

    int not_zero_count;
    int not_one_count;
    int double_not_count;

} OptimizationResult;

/* Initialize optimization result */
void init_optimization_result(OptimizationResult *result);

/* Perform logic optimization on the parsed module */
void optimize_module(Module *module, OptimizationResult *result);

/* Print optimization report */
void print_optimization_report(const OptimizationResult *result);

#endif