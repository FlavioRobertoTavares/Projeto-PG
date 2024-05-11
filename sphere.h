#ifndef SPHEREH
#define SPHEREH

#include "vector.h"
#include "point.h"

class Sphere {
    public:
        Sphere(Point center, double radius, Vector color) {
            this->center = center;
            this->radius = radius;
            this->color = color;
        }

        Point center;
        double radius;
        Vector color;
};

#endif