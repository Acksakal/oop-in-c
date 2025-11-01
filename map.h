#ifndef MAP_H
#define MAP_H

typedef struct MapEntry {
    char *key;                 /* public */
    int value;                 /* public */
    struct MapEntry *__prev;
    struct MapEntry *__next;
} MapEntry;

typedef struct Map {
    /* Private attributes */
    struct MapEntry *__head;
    struct MapEntry *__tail;
    int __count;

    /* Public methods */
    void (*put)(struct Map *self, char *key, int value);
    int  (*get)(struct Map *self, char *key, int def);
    int  (*size)(struct Map *self);
    void (*dump)(struct Map *self);
    void (*del)(struct Map *self);
} Map;

/* Public constructor */
struct Map *Map_new(void);

#endif
