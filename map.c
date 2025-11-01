#include "map.h"
#include <stdio.h>
#include <stdlib.h>

/* ---------- Private string helpers ---------- */

static int str_eq(const char *a, const char *b) {
    while (*a && *b) {
        if (*a != *b)
            return 0;
        a++;
        b++;
    }
    return *a == *b;  // both must end at same time
}

static char *str_copy(const char *src) {
    int len = 0;
    while (src[len])
        len++;

    char *dst = malloc(len + 1);
    if (!dst) return NULL;

    for (int i = 0; i <= len; i++)
        dst[i] = src[i];  // includes '\0'
    return dst;
}

/* ---------- Private helper ---------- */
static MapEntry *__Map_find(struct Map *self, const char *key) {
    for (MapEntry *cur = self->__head; cur != NULL; cur = cur->__next) {
        if (str_eq(cur->key, key))
            return cur;
    }
    return NULL;
}

/* ---------- Private methods ---------- */
static void __Map_put(struct Map *self, char *key, int value) {
    MapEntry *entry = __Map_find(self, key);
    if (entry != NULL) {
        entry->value = value; /* update existing */
        return;
    }

    /* new entry */
    MapEntry *new_entry = malloc(sizeof(MapEntry));
    if (!new_entry) return;

    new_entry->key = str_copy(key);
    new_entry->value = value;
    new_entry->__next = NULL;
    new_entry->__prev = self->__tail;

    if (self->__tail)
        self->__tail->__next = new_entry;
    else
        self->__head = new_entry;

    self->__tail = new_entry;
    self->__count++;
}

static int __Map_get(struct Map *self, char *key, int def) {
    MapEntry *entry = __Map_find(self, key);
    return entry ? entry->value : def;
}

static int __Map_size(struct Map *self) {
    return self->__count;
}

static void __Map_dump(struct Map *self) {
    printf("Object map count=%d\n", self->__count);
    for (MapEntry *cur = self->__head; cur != NULL; cur = cur->__next) {
        printf("  %s=%d\n", cur->key, cur->value);
    }
}

static void __Map_del(struct Map *self) {
    MapEntry *cur = self->__head;
    while (cur) {
        MapEntry *next = cur->__next;
        free(cur->key);
        free(cur);
        cur = next;
    }
    free(self);
}

/* ---------- Public constructor ---------- */
struct Map *Map_new(void) {
    struct Map *p = malloc(sizeof(*p));
    if (!p) return NULL;

    p->__head = NULL;
    p->__tail = NULL;
    p->__count = 0;

    p->put  = &__Map_put;
    p->get  = &__Map_get;
    p->size = &__Map_size;
    p->dump = &__Map_dump;
    p->del  = &__Map_del;

    return p;
}
