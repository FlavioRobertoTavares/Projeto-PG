#ifndef OBJECT
#define OBJECT
#include "ray.h"
#include "vector.h"

class Object {
public:
    Vector color;

    Object(Vector color) : color(color) {}

    virtual ~Object() = default;

    virtual double intersect(const ray &r) = 0;
};

#endif