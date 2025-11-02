#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/* ---------- Internal definitions ---------- */

typedef struct lnode
{
    char *text;
    struct lnode *next;
} Node;

struct pylist
{
    Node *head;
    Node *tail;
    int count;
};

/* ---------- Utility string functions ---------- */

static size_t my_strlen(const char *s)
{
    const char *p = s;
    while (*p)
        p++;
    return (size_t)(p - s);
}

static int my_strcmp(const char *a, const char *b)
{
    while (*a && (*a == *b))
    {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

static char *str_copy(const char *s)
{
    size_t n = my_strlen(s);
    char *copy = malloc(n + 1);
    if (!copy)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    char *dst = copy;
    while (*s)
        *dst++ = *s++;
    *dst = '\0';
    return copy;
}

/* ---------- List API ---------- */

PyList *pylist_new(void)
{
    PyList *p = malloc(sizeof(*p));
    if (!p)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    return p;
}

void pylist_del(PyList *self)
{
    Node *cur = self->head;
    while (cur)
    {
        Node *next = cur->next;
        free(cur->text);
        free(cur);
        cur = next;
    }
    free(self);
}

void pylist_append(PyList *self, const char *text)
{
    Node *n = malloc(sizeof(*n));
    if (!n)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    n->text = str_copy(text);
    n->next = NULL;

    if (self->tail)
        self->tail->next = n;
    else
        self->head = n;

    self->tail = n;
    self->count++;
}

void pylist_print(const PyList *self)
{
    printf("[");
    Node *cur = self->head;
    while (cur)
    {
        printf("'%s'", cur->text);
        if (cur->next)
            printf(", ");
        cur = cur->next;
    }
    printf("]\n");
}

int pylist_len(const PyList *self)
{
    return self->count;
}

int pylist_index(const PyList *self, const char *text)
{
    Node *cur = self->head;
    int idx = 0;
    while (cur)
    {
        if (my_strcmp(cur->text, text) == 0)
            return idx;
        cur = cur->next;
        idx++;
    }
    return -1;
}
