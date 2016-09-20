#include <stdio.h>

#include <err.h>

#include "graph.h"
#include "graph_traversal.h"

/* test cases */
int test_case_loop(void);
int test_case_topo_sort(void);

int
test_case_loop(void) {
    unsigned int i;
    struct graph g;

    graph_init(&g, 20, 20);

    for (i = 0 ; i < 10 ; i++) {
        graph_insert_node(&g);
    }

    graph_insert_edge(&g, 3, 1);
    graph_insert_edge(&g, 1, 5);
    graph_insert_edge(&g, 1, 2);
    graph_insert_edge(&g, 5, 4);
    graph_insert_edge(&g, 5, 2);

    /* TEST LOOP */
    printf("add loop and make dfs :\n");
    graph_insert_edge(&g, 4, 3);
    for (i = 0; i < graph_get_nodes_count(&g); i++) {
        if (graph_is_cyclic(&g, i)) {
            printf("--> loop detected %d\n", i);
            break;
        }
    }

    printf("remove loop and make dfs :\n");
    graph_remove_edge(&g, 4, 3);
    for (i = 0; i < graph_get_nodes_count(&g); i++) {
        if (graph_is_cyclic(&g, i)) {
            printf("--> error : loop detected %d\n", i);
            break;
        }
    }

    graph_clean(&g);

    return 0;
}

int
test_case_topo_sort(void) {
    unsigned int i;
    unsigned int nds[4];
    unsigned int nds_cnt;
    struct graph g;
    struct graph_tsort_iter * tsort_it = NULL;

    graph_init(&g, 20, 20);

    for (i = 0 ; i < 10 ; i++) {
        graph_insert_node(&g);
    }

    graph_insert_edge(&g, 3, 1);
    graph_insert_edge(&g, 1, 5);
    graph_insert_edge(&g, 1, 2);
    graph_insert_edge(&g, 5, 4);
    graph_insert_edge(&g, 5, 2);
    graph_insert_edge(&g, 4, 8);

    /* TEST DFS  */

    printf("topo sort greedy (3 elements max at a time) :\n");
    graph_tsort_create(&g, &tsort_it);
    while ((nds_cnt = graph_tsort_next(tsort_it, nds, 4)) > 0) {
        for (i = 0; i < nds_cnt; i++) {
            printf("%u ", nds[i]);
        }
        printf("\n");
    }
    graph_tsort_destroy(tsort_it);

    printf("remove edge 4->8 and make same topo sort :\n");
    graph_remove_edge(&g, 4, 8);

    if (graph_tsort_create(&g, &tsort_it)) {
        printf("graph_tsort_create failed, maybe a cycle in graph ?\n");
        return 1;
    }
    while ((nds_cnt = graph_tsort_next(tsort_it, nds, 4)) > 0) {
        for (i = 0; i < nds_cnt; i++) {
            printf("%u ", nds[i]);
        }
        printf("\n");
    }
    graph_tsort_destroy(tsort_it);

    graph_clean(&g);
    return 0;
}


INIT_ERR();

int
main (int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    SET_ERR(stdout);

    test_case_loop();
    test_case_topo_sort();

    return 0;
}
