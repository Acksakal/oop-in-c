#include "pystr.h"
#include <stdio.h>

int main(void) {
    printf("Testing pystr class\n");

    pystr *x = pystr_new();
    if (x == NULL) {
        fprintf(stderr, "Failed to create pystr object.\n");
        return 1;
    }

    pystr_dump(x);

    pystr_append(x, 'H');
    pystr_dump(x);

    pystr_appends(x, "ello world");
    pystr_dump(x);

    pystr_assign(x, "A completely new string");
    
    printf("String = %s\n", pystr_str(x));
    printf("Length = %d\n", pystr_len(x));
    
    pystr_del(x);
    
    return 0;
}
