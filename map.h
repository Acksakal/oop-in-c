#ifndef MAP_H
#define MAP_H

/* OOP-style "methods" */
typedef struct Map
{
    void (*put)(struct Map *self, char *key, int value);
    int (*get)(struct Map *self, char *key, int def);
    int (*size)(struct Map *self);
    void (*dump)(struct Map *self);
    void (*del)(struct Map *self);

    void *__priv; /* pointer to private data */
} Map;

Map *Map_new(void);

#endif
