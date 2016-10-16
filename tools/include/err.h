#ifndef ERR_H_
#define ERR_H_

#include <stdio.h>

/* Common error codes */
enum {
    SUCCESS = 0,
    ERROR = 1,
};

extern FILE *fdout;

#define SET_ERR(FD) fdout = FD
#define INIT_ERR() FILE *fdout

#if defined(DEBUG)
    #define dbg_print(FMT, ...) fprintf(fdout, \
        "DEBUG(%s:%d <%s>): " FMT, \
        __FILE__, __LINE__, __func__, ##__VA_ARGS__)
    #define err_print(FMT, ...) fprintf(fdout, \
        "ERROR(%s:%d <%s>): " FMT, \
        __FILE__, __LINE__, __func__, ##__VA_ARGS__)
    #define print(FMT, ...) fprintf(fdout, \
        "%s:%d <%s>: " FMT, \
        __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define dbg_print(...)
    #define err_print(FMT, ...) fprintf(fdout, \
        "ERROR: " FMT, ##__VA_ARGS__)
    #define print(FMT, ...) fprintf(fdout, \
        FMT, ##__VA_ARGS__)
#endif

#endif /* ERR_H_ */
