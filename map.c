#include "map.h"
#include <stdio.h>
#include <stdlib.h>

/* ---------- Private internal types ---------- */
typedef struct MapEntry
{
    char *key;
    int value;
    struct MapEntry *next;
    struct MapEntry *prev;
} MapEntry;

typedef struct MapPriv
{
    MapEntry *head;
    MapEntry *tail;
    int count;
} MapPriv;

/* ---------- Private helper functions ---------- */
static int str_eq(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (*a++ != *b++)
            return 0;
    }
    return *a == *b;
}

static char *str_copy(const char *source)
{
    int length = 0;
    char *copy;
    int i;

    while (source[length])
        length++;

    copy = (char *)malloc(length + 1);
    if (!copy)
        return NULL;

    for (i = 0; i <= length; i++)
        copy[i] = source[i];

    return copy;
}

static MapEntry *find_entry(MapPriv *privateData, const char *key)
{
    MapEntry *current = privateData->head;
    while (current)
    {
        if (str_eq(current->key, key))
            return current;
        current = current->next;
    }
    return NULL;
}

/* ---------- OOP-style methods ---------- */
static void __Map_put(Map *self, char *key, int value)
{
    MapPriv *privateData;
    MapEntry *existingEntry;
    MapEntry *newEntry;

    privateData = (MapPriv *)self->__priv;
    existingEntry = find_entry(privateData, key);

    if (existingEntry)
    {
        existingEntry->value = value;
        return;
    }

    newEntry = (MapEntry *)malloc(sizeof(*newEntry));
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
    MapEntry *entry;

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
    MapEntry *current;

    privateData = (MapPriv *)self->__priv;
    printf("Object map count=%d\n", privateData->count);

    current = privateData->head;
    while (current)
    {
        printf("  %s=%d\n", current->key, current->value);
        current = current->next;
    }
}

static void __Map_del(Map *self)
{
    MapPriv *privateData;
    MapEntry *current;
    MapEntry *next;

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

    return map;
}
