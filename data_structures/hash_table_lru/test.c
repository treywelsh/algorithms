#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "hash.h"

int
main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    ht_key_t key;
    int ret;
    ht_t ht;
    ht_elt_t *result;
    size_t i;
    size_t len;
    const char * strings[] = {
        "AAAAAA",
        "BBBBBB",
        "CCCCCC",
        "DDDDDD",
        "DDDDDDaaa",
        "EEEEEE",
        "AAAAAA",
        "FFFFFF",
        "BBBBBB"
    };
    size_t strings_count = 8;

    ret = ht_init(&ht, 10, 6);
    if (ret != SUCCESS) {
        return ret;
    }

    /* fill hash from strings */
    for (i = 0; i < strings_count; i++) {
        len = strlen(strings[i]);

        printf("adding \"%s\" len=%zu\n", strings[i], len);

        ret = ht_key_init(&key, (uint8_t *)strings[i], len);
        if (ret != 0) {
            continue;
        }

        result = ht_lookup(&ht, &key);
        assert(result != NULL);

        /* modify value, it's a counter here */
        (result->count)++;
        printf("%s present with value %" PRIu64 "\n", strings[i], result->count);

        printf("==========================LRU========================\n");
        ht_print_lru_content(&ht);
        printf("=====================================================\n");
    }

    ht_clean(&ht);

    return 0;
}
