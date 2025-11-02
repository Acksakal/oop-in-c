#ifndef POINT_H
#define POINT_H

// Forward declaration of the struct Point.
// This is the Opaque Pointer pattern: the client code (main.c) 
// only knows that 'Point' exists, but not what it contains.
typedef struct Point Point;

// --- Public API Functions ---

/**
 * @brief Constructs and returns a new Point object.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return A pointer to the newly created Point object, or NULL on failure.
 */
Point *point_new(double x, double y);

/**
 * @brief Prints the coordinates and memory address of the Point object.
 * @param self A pointer to the Point object.
 */
void point_dump(const Point *self);

/**
 * @brief Calculates the distance of the point from the origin (0, 0).
 * @param self A pointer to the Point object.
 * @return The distance from the origin.
 */
double point_origin(const Point *self);

/**
 * @brief Destroys the Point object and frees its allocated memory.
 * @param self A pointer to the Point object.
 */
void point_del(Point *self);

#endif // POINT_H
