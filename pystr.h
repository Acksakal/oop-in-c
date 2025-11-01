#ifndef PYSTR_H
#define PYSTR_H

#include <stddef.h> // For size_t

typedef struct pystr pystr;

pystr *pystr_new(void);

void pystr_del(pystr *self);

int pystr_assign(pystr *self, const char *str);

int pystr_append(pystr *self, char ch);

int pystr_appends(pystr *self, const char *str);

int pystr_len(const pystr *self);

char *pystr_str(const pystr *self); 

void pystr_dump(const pystr *self);

#endif // PYSTR_H