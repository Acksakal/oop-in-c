#include "list.h"
#include <stdio.h>

int main(void)
{
    PyList *lst = pylist_new();

    pylist_append(lst, "Hello world");
    pylist_print(lst);

    pylist_append(lst, "Catch phrase");
    pylist_print(lst);

    pylist_append(lst, "Brian");
    pylist_print(lst);

    printf("Length = %d\n", pylist_len(lst));
    printf("Brian? %d\n", pylist_index(lst, "Brian"));
    printf("Bob? %d\n", pylist_index(lst, "Bob"));

    pylist_del(lst);
    return 0;
}
