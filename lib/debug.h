#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define DEBUGGING 1
#else
#define DEBUGGING 0
#endif

#define debug(str) \
        do { if (DEBUGGING) fprintf(stderr, "%s:%d:%s(): " str, __FILE__, \
                                __LINE__, __func__); } while (0)

#define debugf(fmt, ...) \
        do { if (DEBUGGING) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

#endif /* ifndef DEBUG_H */
