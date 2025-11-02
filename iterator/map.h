#ifndef MAP_H
#define MAP_H

typedef struct Map Map;
typedef struct MapIter MapIter;

// MapEntry must be exposed to allow the user to access cur->key and cur->value
// in the main function's iteration loop. We only expose the public fields.
typedef struct MapEntry
{
    char *key;
    int value;
    // Implementation details like 'next' and 'prev' are hidden in map.c
} MapEntry;

// MapIter structure: The abstract iterator object
struct MapIter
{
    void *__priv; // Pointer to private data (MapIterPriv *)
    MapEntry *(*next)(MapIter *self);
    void (*del)(MapIter *self);
};

// Map structure: The main object with all its method pointers
struct Map
{
    void *__priv; // Pointer to private data (MapPriv *)

    void (*put)(Map *self, char *key, int value);
    int (*get)(Map *self, char *key, int defaultValue);
    int (*size)(Map *self);
    void (*dump)(Map *self);
    void (*del)(Map *self);

    // New iterator method
    MapIter *(*iter)(Map *self);
};

// Constructor prototype
Map *Map_new(void);

#endif