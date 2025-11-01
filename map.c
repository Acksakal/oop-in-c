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
        if (*a++ != *b++)
            return 0;
    return *a == *b;
}

static char *str_copy(const char *s)
{
    int n = 0;
    while (s[n])
        n++;
    char *r = malloc(n + 1);
    for (int i = 0; i <= n; i++)
        r[i] = s[i];
    return r;
}

static MapEntry *find_entry(MapPriv *p, const char *key)
{
    for (MapEntry *cur = p->head; cur; cur = cur->next)
        if (str_eq(cur->key, key))
            return cur;
    return NULL;
}

/* ---------- OOP-style methods ---------- */
static void __Map_put(Map *self, char *key, int value)
{
    MapPriv *p = self->__priv;
    MapEntry *e = find_entry(p, key);
    if (e)
    {
        e->value = value;
        return;
    }

    MapEntry *ne = malloc(sizeof(*ne));
    ne->key = str_copy(key);
    ne->value = value;
    ne->next = NULL;
    ne->prev = p->tail;

    if (p->tail)
        p->tail->next = ne;
    else
        p->head = ne;
    p->tail = ne;
    p->count++;
}

static int __Map_get(Map *self, char *key, int def)
{
    MapPriv *p = self->__priv;
    MapEntry *e = find_entry(p, key);
    return e ? e->value : def;
}

static int __Map_size(Map *self)
{
    return ((MapPriv *)self->__priv)->count;
}

static void __Map_dump(Map *self)
{
    MapPriv *p = self->__priv;
    printf("Object map count=%d\n", p->count);
    for (MapEntry *cur = p->head; cur; cur = cur->next)
        printf("  %s=%d\n", cur->key, cur->value);
}

static void __Map_del(Map *self)
{
    MapPriv *p = self->__priv;
    MapEntry *cur = p->head;
    while (cur)
    {
        MapEntry *next = cur->next;
        free(cur->key);
        free(cur);
        cur = next;
    }
    free(p);
    free(self);
}

/* ---------- Constructor ---------- */
Map *Map_new(void)
{
    Map *m = malloc(sizeof(*m));
    MapPriv *priv = calloc(1, sizeof(*priv));

    m->__priv = priv;
    m->put = &__Map_put;
    m->get = &__Map_get;
    m->size = &__Map_size;
    m->dump = &__Map_dump;
    m->del = &__Map_del;

    return m;
}
