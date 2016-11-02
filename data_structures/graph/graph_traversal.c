#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errcodes.h"
#include "graph.h"
#include "graph_traversal.h"
#include "stack.h"

struct graph_dfs_iter {
    struct graph * g;
    struct stack st_nd;
};

int
graph_dfs_create(struct graph* g, struct graph_dfs_iter ** it, uint32_t first_nd) {
    assert(g != NULL);
    assert(it != NULL);

    *it = malloc(sizeof(**it));
    if (it == NULL) {
        return GRAPH_MALLOC_ERROR;
    }

    if (stack_init(&(*it)->st_edg, graph_nodes_count(g))) {
       return ERROR; 
    }

    stack_push(&it->st_nd, first_nd);
    (*it)->g = g;
    (*it)->first_nd = first_nd;

    return SUCCESS;
}

void
graph_dfs_destroy(struct graph_dfs_iter * it) {
    
    assert(it != NULL);

    nodes_reset_seen(it->g);
    edges_reset_seen(it->g);

    stack_clean(&it->st_edg);
    free(it);
}

int
graph_dfs_next(struct graph_dfs_iter * it,
        uint32_t * ndret,
        uint32_t ndsz) {
    uint32_t nh;
    uint32_t i, i_edg;
    uint32_t nd_id;
    uint32_t ndret_count;

    assert(it != NULL);
    assert(it->first_nd < graph_nodes_count(it->g));
    assert(ndret != NULL);


    ndret_count = 0;
    while (!stack_is_empty(&it->st_nd)) {
        i = stack_pop(&it->st_nd);

        /* Loop on each neighbour, and mark visited edges and nodes */
        i_edg = (it->g->edg_first)[i];
        while (i_edg != GRAPH_EDG_NULL) {

            /* mark edge to visit it only once and so, avoid loop */
            if ((it->g->edgs)[i_edg].seen) {
                i_edg = (it->g->edgs_nxt)[i_edg];
                continue;
            }
            (it->g->edgs)[i_edg].seen = 1;

            /* mark node in order to visit it only once */
            nd_id = (it->g->edgs_dst)[i_edg];
            if ((it->g->nds)[nd_id].seen) {
                i_edg = (it->g->edgs_nxt)[i_edg];
                continue;
            }
            (it->g->nds)[nd_id].seen = 1;

            /* fill return array with node */
            ndret[ndret_count] = nd_id;
            ndret_count++;

            /* push neighbour node for later processing */
            nh = (it->g->edgs_dst)[i_edg];
            stack_push(&it->st_nd, nh);

            /* if return array is full, return func here */
            if (ndret_count == ndsz) {
                return ndret_count;
            }

            /* next edge */
            i_edg = (it->g->edgs_nxt)[i_edg];
        }
        /* when all neighbour processed, pop node */
    }

    return SUCCESS;
}

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
