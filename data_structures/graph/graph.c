#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <err.h>
#include <stack.h>

#include "graph.h"

/*
 * See another graph implem : https://rosettacode.org/wiki/Dijkstra's_algorithm#C
 */

int
graph_init(struct graph* g, unsigned int nodes_max, unsigned int edges_max) {
    assert(g != NULL);
    assert(nodes_max > 0);
    assert(edges_max > 0);

    g->nds_max = nodes_max;
    g->edgs_max = ++edges_max;
    g->nds_count = 0;
    g->edgs_count = 1; /* Use edge at index 0 as null edge in order to
                          avoid using -1 value */

    /* first edge leaving node */
    g->first_edg = malloc(nodes_max * sizeof(*(g->first_edg)));
    if (g->first_edg == NULL) {
        return 1;
    }
    memset(g->first_edg, GRAPH_EDG_NULL, nodes_max * sizeof(*(g->first_edg)));

    /* next edge leaving node */
    g->edgs_nxt = malloc(edges_max * sizeof(*(g->edgs_dst)));
    if (g->edgs_nxt == NULL) {
        return 1;
    }

    /* contain the node destination of an arc */
    g->edgs_dst = malloc(edges_max * sizeof(*(g->edgs_dst)));
    if (g->edgs_nxt == NULL) {
        return 1;
    }

    /* edges data */
    g->edgs = malloc(edges_max * sizeof(*(g->edgs)));
    if (g->edgs == NULL) {
        return 1;
    }
    edges_reset_seen(g->edgs, edges_max);

    /* nodes data */
    g->nds = malloc(nodes_max * sizeof(*(g->nds)));
    if (g->nds == NULL) {
        return 1;
    }
    nodes_reset_seen(g->nds, nodes_max);

    /* arbitrary value */
    stack_init(&(g->deleted), (unsigned int)(edges_max / 2));

    return 0;
}

void
graph_clean(struct graph* g) {
    assert(g != NULL);

    free(g->first_edg);
    free(g->edgs_nxt);
    free(g->edgs_dst);
    stack_clean(&(g->deleted));
    free(g->nds);
    free(g->edgs);
}

int
graph_insert_node(struct graph* g) {
    assert(g != NULL);
    if (graph_nodes_full(g)) {
        err_print("graph nodes full\n");
        return 1;
    }
    node_init(&(g->nds)[g->nds_count]);
    (g->nds_count)++;
    return 0;
}

int
graph_insert_edge(struct graph* g, unsigned int u, unsigned int v) {

    assert(g != NULL);
    assert(!graph_edges_full(g));
    assert(u < g->nds_count);
    assert(v < g->nds_count);

    if (graph_edges_full(g)) {
        err_print("graph edges full\n");
        return 1;
    }


    edge_init(&(g->edgs)[g->edgs_count]);

    (g->edgs_dst)[g->edgs_count] = v;

    (g->edgs_nxt)[g->edgs_count] = (g->first_edg)[u];
    (g->first_edg)[u] = (g->edgs_count)++;
    return 0;
}

int
graph_remove_edge(struct graph* g, unsigned int u, unsigned int v) {
    unsigned int i, i_prev;
    unsigned int edg_id;

    assert(g != NULL);
    assert(!graph_edges_empty(g));
    assert(u < g->nds_count);
    assert(v < g->nds_count);

    if (graph_edges_empty(g)) {
        err_print("graph edges empty\n");
        return 1;
    }

    /* retrieve edge_id */
    edg_id = GRAPH_EDG_NULL;
    i = g->first_edg[u];
    i_prev = i;
    while (i != GRAPH_EDG_NULL) {
        if (g->edgs_dst[i] == v) {
            edg_id = i;
            break;
        }
        i_prev = i;
        i = g->edgs_nxt[i];
    }

    assert(edg_id != GRAPH_EDG_NULL);

    /* keep for later graph reordering */
    stack_push(&(g->deleted), edg_id);

    /* if last added edge */
    if (edg_id == (g->first_edg)[u]) {
        (g->first_edg)[u] = g->edgs_nxt[(g->first_edg)[u]];
        return 0;
    } else {
        g->edgs_nxt[i_prev] = g->edgs_nxt[i];
    }

    return 0;
}

/* TODO
int
graph_reorder_edge() {

    g->edgs_dst[edg_id] = ; No null node value ???
    g->edgs_count -= 1;
}

int
graph_remove_node() {}

int
graph_reorder_node() {}
*/

int
graph_is_cyclic(struct graph* g, unsigned int first_nd) {
    unsigned int nh;
    unsigned int i, i_edg;
    int ret;
    struct stack stk;

    assert(g != NULL);
    assert(first_nd < g->nds_count);

    stack_init(&stk, g->nds_count);
    stack_push(&stk, first_nd);

    ret = 0;
    while (!stack_is_empty(&stk)) {
        i = stack_pop(&stk);

        /* detect cycle in marking visited edges :
         * 1. mark each edges leaving node at index i
         * 2. stack each neighbour of node at index i
         */
        i_edg = g->first_edg[i];
        while (i_edg != GRAPH_EDG_NULL) {

            /* visit edge only once */
            if ((g->edgs)[i_edg].seen) {
                ret = 1;
                goto clean;
            }
            (g->edgs)[i_edg].seen = 1;

            /* push node */
            nh = g->edgs_dst[i_edg];
            stack_push(&stk, nh);

            i_edg = g->edgs_nxt[i_edg];
        }
    }

    /* reset after use */
clean:
    edges_reset_seen(g->edgs, g->edgs_max);
    stack_clean(&stk);

    return ret;
}
