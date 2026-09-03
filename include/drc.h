#ifndef DRC_H
#define DRC_H

#include "graph.h"

/* Maximum number of DRC violations */
#define MAX_DRC_VIOLATIONS 100

/* Types of DRC violations */
typedef enum {
    DRC_UNDRIVEN_NET,
    DRC_MULTIPLE_DRIVERS,
    DRC_UNCONNECTED_INPUT,
    DRC_UNCONNECTED_OUTPUT
} DRCViolationType;

/* Structure representing one DRC violation */
typedef struct {
    DRCViolationType type;
    char net_name[50];
    char message[200];
} DRCViolation;

/* DRC result structure */
typedef struct {
    DRCViolation violations[MAX_DRC_VIOLATIONS];
    int violation_count;
} DRC;

/* Initialize DRC */
void init_drc(DRC *drc);

/* Add a DRC violation */
void add_drc_violation(
    DRC *drc,
    DRCViolationType type,
    const char *net_name,
    const char *message
);

/* Run DRC checks on the circuit graph */
void run_drc(DRC *drc, Graph *graph, const Module *module);

/* Print DRC report */
void print_drc_report(DRC *drc);

/* Get violation type as a string */
const char *get_drc_violation_type(DRCViolationType type);

#endif