#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Private internal types ---------- */
// The full definition of MapEntry for internal use (includes list pointers)
typedef struct MapEntryInternal
{
    char *key;
    int value;
    struct MapEntryInternal *next;
    struct MapEntryInternal *prev;
} MapEntryInternal;

// Private data for the Map object (hides implementation details)
typedef struct MapPriv
{
    MapEntryInternal *head;
    MapEntryInternal *tail;
    int count;
} MapPriv;

// Private data for the MapIter object (hides iteration state)
typedef struct MapIterPriv
{
    MapEntryInternal *current;
} MapIterPriv;

/* ---------- Private helper functions ---------- */
static int str_eq(const char *a, const char *b)
{
    return (strcmp(a, b) == 0);
}

static char *str_copy(const char *source)
{
    char *copy = strdup(source);
    return copy;
}

// Note: returns MapEntryInternal*
static MapEntryInternal *find_entry(MapPriv *privateData, const char *key)
{
    MapEntryInternal *current = privateData->head;
    while (current)
    {
        if (str_eq(current->key, key))
            return current;
        current = current->next;
    }
    return NULL;
}

/* ---------- MapIter Methods (Internal) ---------- */
static MapEntry *__MapIter_next(MapIter *self)
{
    MapIterPriv *privateData = (MapIterPriv *)self->__priv;
    MapEntryInternal *internalEntry = privateData->current;

    if (internalEntry == NULL)
        return NULL;

    // Advance the internal pointer
    privateData->current = internalEntry->next;

    // Cast the internal entry to the public MapEntry structure for return.
    // This works because the public MapEntry is a subset (key, value)
    // of the internal structure and appears first.
    return (MapEntry *)internalEntry;
}

static void __MapIter_del(MapIter *self)
{
    free(self->__priv);
    free(self);
}

/* ---------- Map Method: Iterator Builder ---------- */
static MapIter *__Map_iter(Map *self)
{
    Map *map = (Map *)self;
    MapPriv *mapPriv = (MapPriv *)map->__priv;
    MapIter *iter;
    MapIterPriv *iterPriv;

    // 1. Allocate and initialize the private state
    iterPriv = (MapIterPriv *)malloc(sizeof(*iterPriv));
    if (!iterPriv)
        return NULL;
    iterPriv->current = mapPriv->head;

    // 2. Allocate and initialize the public MapIter struct
    iter = (MapIter *)malloc(sizeof(*iter));
    if (!iter)
    {
        free(iterPriv);
        return NULL;
    }

    iter->__priv = iterPriv;
    iter->next = &__MapIter_next;
    iter->del = &__MapIter_del;

    return iter;
}

/* ---------- Map OOP-style methods ---------- */
static void __Map_put(Map *self, char *key, int value)
{
    MapPriv *privateData;
    MapEntryInternal *existingEntry;
    MapEntryInternal *newEntry;

    privateData = (MapPriv *)self->__priv;
    existingEntry = find_entry(privateData, key);

    if (existingEntry)
    {
        existingEntry->value = value;
        return;
    }

    newEntry = (MapEntryInternal *)malloc(sizeof(*newEntry));
    if (!newEntry)
        return;

    newEntry->key = str_copy(key);
    newEntry->value = value;
    newEntry->next = NULL;
    newEntry->prev = privateData->tail;

    if (privateData->tail)
        privateData->tail->next = newEntry;
    else
        privateData->head = newEntry;

    privateData->tail = newEntry;
    privateData->count++;
}

static int __Map_get(Map *self, char *key, int defaultValue)
{
    MapPriv *privateData;
    MapEntryInternal *entry;

    privateData = (MapPriv *)self->__priv;
    entry = find_entry(privateData, key);

    if (entry)
        return entry->value;

    return defaultValue;
}

static int __Map_size(Map *self)
{
    MapPriv *privateData = (MapPriv *)self->__priv;
    return privateData->count;
}

static void __Map_dump(Map *self)
{
    MapPriv *privateData;
    MapEntryInternal *current;

    privateData = (MapPriv *)self->__priv;
    printf("Testing Map class\n");
    printf("Object Map count=%d\n", privateData->count);

    current = privateData->head;
    while (current)
    {
        printf(" %s=%d\n", current->key, current->value);
        current = current->next;
    }
}

static void __Map_del(Map *self)
{
    MapPriv *privateData;
    MapEntryInternal *current;
    MapEntryInternal *next;

    privateData = (MapPriv *)self->__priv;
    current = privateData->head;

    while (current)
    {
        next = current->next;
        free(current->key);
        free(current);
        current = next;
    }

    free(privateData);
    free(self);
}

/* ---------- Constructor ---------- */
Map *Map_new(void)
{
    Map *map;
    MapPriv *privateData;

    map = (Map *)malloc(sizeof(*map));
    if (!map)
        return NULL;

    privateData = (MapPriv *)calloc(1, sizeof(*privateData));
    if (!privateData)
    {
        free(map);
        return NULL;
    }

    map->__priv = privateData;
    map->put = &__Map_put;
    map->get = &__Map_get;
    map->size = &__Map_size;
    map->dump = &__Map_dump;
    map->del = &__Map_del;

    // Set the new iterator builder function
    map->iter = &__Map_iter;

    return map;
}