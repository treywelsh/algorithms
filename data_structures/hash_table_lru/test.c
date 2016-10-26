#include <stdio.h>
#include <stdlib.h>

#include "hash.h"


int
main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int ret;
    ht_t ht;
    ht_elt_t *result_lookup;
    const char * filename = "test_file";

    ret = ht_init(&ht, 10, 5);
    if (ret != SUCCESS ) {
        return ret;
    }

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("error: cannnot open %s\n", filename);
        exit(1);
    }

    /* Each line of the file is inserted in hash */
    while ((read = getline(&line, &len, fp)) != -1) {

        printf("adding \"%s\" len=%zu\n", line, read);
        line[6] = '\0';
        result_lookup = ht_lookup(&ht, line);
        (result_lookup->count)++;
        printf("%s with count %u\n", line, result_lookup->count);
        printf("==========================LRU========================\n");
        ht_print_lru_content(&ht);
        printf("=====================================================\n");
    }

    fclose(fp);
    if (line)
        free(line);

    ht_clean(&ht);

    return 0;
}
