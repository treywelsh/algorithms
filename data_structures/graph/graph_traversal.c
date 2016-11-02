#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph_traversal.h"
#include "stack.h"

/*
struct graph_dfs_iter {
    struct graph * g;
    struct stack st_edg;
};

int
graph_dfs_init(struct graph* g, struct graph_dfs_iter * it, uint32_t first_nd);
    stack_init(it->st_edg);
    it->g = g;
}

int
graph_dfs(uint32_t first_nd,
        uint32_t * ndret,
        uint32_t ndsz) {

}

*/

/*
 * Topological sort
 */

struct graph_tsort_iter {
    struct graph * g; /* original graph, use "seen" variables */
    struct graph g_rev; /* partial graph containing reversed edges */
    uint32_t * adj_cnt; /* array containing counter of adjacent nodes */
};

int
graph_tsort_create(struct graph* g, struct graph_tsort_iter ** it)
{
    uint32_t nd, nh;
    uint32_t i;
    struct graph_tsort_iter * it_tmp;

    assert(g != NULL);
    assert(it != NULL);

    /* Prerequisite : graph without cycle */
    for (i = 0; i < graph_nodes_count(g); i++) {
        if (graph_is_cyclic(g, i)) {
            return 1;
        }
    }

    it_tmp = malloc(sizeof(*it_tmp));
    if (it_tmp == NULL) {
        return 1;
    }
    it_tmp->adj_cnt = malloc(graph_nodes_count(g) * sizeof(*(it_tmp->adj_cnt)));
    if (it_tmp->adj_cnt == NULL) {
        return 1;
    }

    /* Initialize adjacent nodes count and
     * initialize reversed edges graph
     */
   /* 
    for (i = 0; i < graph_nodes_count(g); i++) {
        (it_tmp->adj_cnt)[i] = 0;
    }*/

    graph_init(&(it_tmp->g_rev), graph_nodes_count(g), g->edgs_count);
    graph_nodes_count(&it_tmp->g_rev) = graph_nodes_count(g);

    /* 1. count adjacent nodes to nd
     * 2. reverse edges : (nd -> nh) become (nh -> nd) in g_rev graph*/
    for (nd = 0 ; nd < graph_nodes_count(g) ; nd++) {
        (it_tmp->adj_cnt)[nd] = 0;

        graph_foreach_neighbor(g, nd, nh) {
            (it_tmp->adj_cnt)[nd] += 1;
            graph_add_edge(&(it_tmp->g_rev), nh, nd);
        }
    }

    it_tmp->g = g;
    *it = it_tmp;

    return 0;
}

uint32_t
graph_tsort_next(struct graph_tsort_iter * it,
                 uint32_t * ndret,
                 uint32_t ndsz)
{
    uint32_t nd, nh;
    uint32_t nds_cnt;
    struct graph_node * nds;

    assert(ndret != NULL);
    assert(it != NULL);

    nds = it->g->nds;
    for (nd = GRAPH_ND_FIRST, nds_cnt = 0
         ; nd < graph_nodes_count(&it->g_rev) && nds_cnt < ndsz
         ; nd++) {

        /* if it remains some dependencies or if node is already seen
         * don't return it */
        if (nds[nd].seen || (it->adj_cnt)[nd] > 0) {
            continue;
        }
        nds[nd].seen = 1;

        /* return at most ndsz elements */
        ndret[nds_cnt++] = nd;
    }

    /* for each neighbour of elements in ndret array,
     * decrement dependency count */
    for (nd = 0; nd < nds_cnt ; nd++) {
        graph_foreach_neighbor(&(it->g_rev), ndret[nd], nh) {
            if ((it->adj_cnt)[nh] > 0) {
                (it->adj_cnt)[nh] -= 1;
            }
        }
    }

    return nds_cnt;
}

void
graph_tsort_destroy(struct graph_tsort_iter * it) {
    struct graph * g;

    assert(it != NULL);
    g = it->g;

    nodes_reset_seen(g);
    free(it->adj_cnt);
    graph_clean(&(it->g_rev));
    free(it);
}
