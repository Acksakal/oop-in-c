#include "map.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Map *map = Map_new();
    MapEntry *cur;
    MapIter *iter;

    // 1. Test Map Operations
    map->put(map, "y", 2);
    map->put(map, "b", 3);
    map->put(map, "a", 4);
    map->put(map, "z", 1);

    // Test overwrite (z) and new key (x)
    map->put(map, "z", 25);
    map->put(map, "x", 42);

    map->dump(map); // Should print z=1, y=2, b=3, a=4, x=42

    printf("\nMap test\n");
    printf("z=%d\n", map->get(map, "z", 42));
    printf("x=%d\n", map->get(map, "x", 42));

    // 2. Test Abstract Iterator
    printf("\nIterate\n");

    // Get the iterator object
    iter = map->iter(map);

    // Loop until the iterator returns NULL
    while (1)
    {
        // Advance the iterator and get the current MapEntry
        cur = iter->next(iter);

        if (cur == NULL)
            break;

        // Access key and value directly from the exposed MapEntry struct
        printf(" %s=%d\n", cur->key, cur->value);
    }

    // Delete the iterator object
    iter->del(iter);

    // 3. Clean up the Map object
    map->del(map);

    return 0;
}