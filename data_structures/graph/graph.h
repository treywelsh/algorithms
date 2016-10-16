#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdint.h>

#include <err.h>
#include <stack.h>

/* node data */
struct graph_node {
    uint32_t seen:1;
    uint32_t unused:31;
};

#define node_init(n) do{ \
    (n)->seen = 0; \
}while(0)

#define nodes_reset_seen(nds, nds_cnt) \
    for (unsigned int nd_rst_i = 0; nd_rst_i < (nds_cnt); nd_rst_i++) { \
        (nds)[nd_rst_i].seen = 0; \
    }

/* edge data */
struct graph_edge {
    uint32_t seen:1;
    uint32_t weight:15;
    uint32_t unused:16;
};

#define edge_init(e) do{ \
    (e)->seen = 0; \
    (e)->weight = 0; \
}while(0)

#define edges_reset_seen(edgs, edgs_cnt) \
    for (unsigned int edg_rst_i = 1; edg_rst_i < (edgs_cnt); edg_rst_i++) { \
        (edgs)[edg_rst_i].seen = 0; \
    }

struct graph {

    /* nodes */
    struct graph_node * nds;
    unsigned int nds_count;
    unsigned int nds_max;

    /* edges */
    struct graph_edge * edgs;
    unsigned int edgs_count;
    unsigned int edgs_max;

    /* edges metadata */
    unsigned int * first_edg; /* first edge leaving node */
    unsigned int * edgs_nxt; /* next edge leaving node */
    unsigned int * edgs_dst; /* contain the node destination of an arc */
    struct stack deleted; /* TODO when stack full, reorder all edges */
};
#define GRAPH_EDG_NULL 0
#define graph_nodes_full(g) ((g)->nds_count == (g)->nds_max - 1)
#define graph_edges_full(g) ((g)->edgs_count == (g)->edgs_max)
#define graph_nodes_empty(g) ((g)->nds_count == 0)
#define graph_edges_empty(g) ((g)->edgs_count == 1) /* first edge is null */
#define graph_foreach_neighbor(g, nd, nh) \
    for (unsigned int idx = (g)->first_edg[nd] ; \
            idx != GRAPH_EDG_NULL && (nh = (g)->edgs_dst[idx], 1) ; \
            idx = (g)->edgs_nxt[idx])

#define graph_get_edges_count(g) ((g)->edgs_count - stack_size((g)->deleted))
#define graph_get_nodes_count(g) ((g)->nds_count)

int graph_init(struct graph* g, unsigned int nodes_max, unsigned int edges_max);
void graph_clean(struct graph* g);
int graph_insert_node(struct graph* g);
int graph_insert_edge(struct graph* g, unsigned int src, unsigned int dst);
int graph_remove_edge(struct graph* g, unsigned int rsc, unsigned int dst);

int graph_is_cyclic(struct graph* g, unsigned int node_first);

#endif /* GRAPH_H_ */
