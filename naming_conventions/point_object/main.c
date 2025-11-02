#include "point.h"
#include <stdio.h>

int main(void) {
    Point *pt = point_new(4.0, 5.0);

    if (pt == NULL) {
        return 1;
    }

    point_dump(pt);

    double distance = point_origin(pt);
    printf("Origin %.6f\n", distance);

    point_del(pt);

    return 0;
}
