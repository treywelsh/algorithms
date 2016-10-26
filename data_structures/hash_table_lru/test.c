#include <stdio.h>
#include <stdlib.h>

#include "hash.h"


int
main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ht_key_t key;
    ssize_t read;
    int ret;
    ht_t ht;
    ht_elt_t *result;
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

        ht_key_init(&key, line, read);

        result = ht_lookup(&ht, &key);

        assert(result != NULL);
        (result->count)++;
        printf("%s present with count %u\n", line, result->count);

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
