#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Full, private definition of the Point structure. 
// Only visible within this file.
struct Point {
    double x;
    double y;
    // The internal fields are defined here.
};

// --- API Implementations ---

Point *point_new(double x, double y) {
    Point *p = (Point *)malloc(sizeof(struct Point));
    if (p == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in point_new.\n");
        return NULL;
    }

    p->x = x;
    p->y = y;

    return p;
}

void point_dump(const Point *self) {
    if (self == NULL) {
        printf("Error: Cannot dump NULL Point object.\n");
        return;
    }
    printf("Object point@%p x=%.6f y=%.6f\n",
           (const void *)self, self->x, self->y);
}

double point_origin(const Point *self) {
    if (self == NULL) {
        fprintf(stderr, "Error: Cannot calculate origin for NULL Point object.\n");
        return 0.0;
    }
    return sqrt(self->x * self->x + self->y * self->y);
}

void point_del(Point *self) {
    if (self != NULL) {
        free((void*)self);
    }
}
