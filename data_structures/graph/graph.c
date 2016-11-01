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
    unsigned int i;

    assert(g != NULL);
    assert(nodes_max > 0);
    assert(edges_max > 0);

    g->nds_max = nodes_max;
    g->edgs_max = edges_max;

    /* count special nodes before the first node */
    g->nds_max += GRAPH_ND_FIRST;
    g->edgs_max += GRAPH_EDG_FIRST;

    /* first edge leaving node */
    g->edg_first = malloc(g->nds_max * sizeof(*(g->edg_first)));
    if (g->edg_first == NULL) {
        return 1;
    }
    memset(g->edg_first, GRAPH_EDG_NULL, g->nds_max * sizeof(*(g->edg_first)));

    /* next edge leaving node */
    g->edgs_nxt = malloc(g->edgs_max * sizeof(*(g->edgs_dst)));
    if (g->edgs_nxt == NULL) {
        return 1;
    }

    /* contain the node destination of an arc */
    g->edgs_dst = malloc(g->edgs_max * sizeof(*(g->edgs_dst)));
    if (g->edgs_nxt == NULL) {
        return 1;
    }

    /* edges data */
    g->edgs = malloc(g->edgs_max * sizeof(*(g->edgs)));
    if (g->edgs == NULL) {
        return 1;
    }
    edges_reset_seen(g->edgs, g->edgs_max);

    /* nodes data */
    g->nds = malloc(g->nds_max * sizeof(*(g->nds)));
    if (g->nds == NULL) {
        return 1;
    }
    nodes_reset_seen(g->nds, g->nds_max);

    /* arbitrary value */
    stack_init(&g->edgs_free, g->edgs_max);
    stack_init(&g->nds_free, g->edgs_max);

    for (i = GRAPH_EDG_FIRST ; i < edges_max ; i++) {
        stack_push(&g->edgs_free, i);
    }
    for (i = GRAPH_ND_FIRST ; i < nodes_max ; i++) {
        stack_push(&g->nds_free, i);
    }

    return 0;
}

void
graph_clean(struct graph* g) {
    assert(g != NULL);

    free(g->edg_first);
    free(g->edgs_nxt);
    free(g->edgs_dst);
    stack_clean(&g->edgs_free);
    stack_clean(&g->nds_free);
    free(g->nds);
    free(g->edgs);
}

int
graph_add_node(struct graph* g) {
    unsigned int nd_id;

    assert(g != NULL);

    if (stack_is_empty(&g->nds_free)) {
        err_print("graph nodes full\n");
        return 1;
    }

    nd_id = stack_pop(&g->nds_free); 
    node_reset(&(g->nds)[nd_id]);

    return 0;
}

int
graph_add_edge(struct graph* g, unsigned int u, unsigned int v) {
    unsigned int edg_id;

    assert(g != NULL);
    assert(!graph_edges_full(g));

    if (stack_is_empty(&g->edgs_free)) {
        err_print("graph edges full\n");
        return 1;
    }

    edg_id = stack_pop(&g->edgs_free); 
    edge_reset(&(g->edgs)[edg_id]);

    /* fill edge linked list */
    (g->edgs_dst)[edg_id] = v;

    (g->edgs_nxt)[edg_id] = (g->edg_first)[u];
    (g->edg_first)[u] = (edg_id)++;
    return 0;
}

int
graph_remove_edge(struct graph* g, unsigned int u, unsigned int v) {
    unsigned int i, i_prev;
    unsigned int edg_id;

    assert(g != NULL);
    assert(!graph_edges_empty(g));
    assert(u < graph_nodes_count(g));
    assert(v < graph_nodes_count(g));

    if (graph_edges_empty(g)) {
        err_print("graph edges empty\n");
        return 1;
    }

    /* retrieve edge_id */
    edg_id = GRAPH_EDG_NULL;
    i = g->edg_first[u];
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

    /* free'd element are stored in a stack */
    stack_push(&g->edgs_free, edg_id);

    /* if last added edge */
    if (edg_id == (g->edg_first)[u]) {
        (g->edg_first)[u] = g->edgs_nxt[(g->edg_first)[u]];
        return 0;
    } else {
        g->edgs_nxt[i_prev] = g->edgs_nxt[i];
    }

    return 0;
}

/* TODO
int
graph_remove_node() {

    stack_push(&g->nds_free, nd_id);
}
*/

int
graph_is_cyclic(struct graph* g, unsigned int first_nd) {
    unsigned int nh;
    unsigned int i, i_edg;
    int ret;
    struct stack stk = {0};

    assert(g != NULL);
    assert(first_nd < graph_nodes_count(g));

    stack_init(&stk, graph_nodes_count(g));
    stack_push(&stk, first_nd);

    ret = 0;
    while (!stack_is_empty(&stk)) {
        i = stack_pop(&stk);

        /* detect cycle in marking visited edges :
         * 1. mark each edges leaving node at index i
         * 2. stack each neighbour of node at index i
         */
        i_edg = g->edg_first[i];
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
