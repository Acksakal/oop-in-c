#include "map.h"
#include <stdio.h>

int main(void) {
    struct Map *m = Map_new();

    m->put(m, "x", 42);
    m->put(m, "y", 99);
    m->put(m, "x", 123);

    m->dump(m);

    printf("Size: %d\n", m->size(m));
    printf("Get x: %d\n", m->get(m, "x", -1));
    printf("Get z (default): %d\n", m->get(m, "z", -1));

    m->del(m);
    return 0;
}
