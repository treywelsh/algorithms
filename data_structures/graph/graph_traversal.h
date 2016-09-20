#ifndef GRAPH_TRAVERSAL_H_
#define GRAPH_TRAVERSAL_H_

#include <stdint.h>

#include "stack.h"
#include "graph.h"

/* Graph traversal */
//TODO dfs traversal

/* Topological sort based on greedy algorithm.
 * It work as an iterator returning several nodes at a time.
 * WARNING: do not modify the graph between
 *      graph_tsort_create and graph_tsort_destroy call.
 */
struct graph_tsort_iter; /* Private struct, use accessors */

int graph_tsort_create(struct graph* g, struct graph_tsort_iter ** it);
void graph_tsort_destroy(struct graph_tsort_iter * it);
unsigned int graph_tsort_next(struct graph_tsort_iter * it, unsigned int * nds,
        unsigned int nds_sz); /* return an array of nodes */

#endif /* GRAPH_TRAVERSAL_H_ */
