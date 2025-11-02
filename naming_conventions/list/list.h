#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct pylist PyList;

PyList *pylist_new(void);
void pylist_del(PyList *self);

void pylist_append(PyList *self, const char *text);
void pylist_print(const PyList *self);
int pylist_len(const PyList *self);
int pylist_index(const PyList *self, const char *text);

#endif
