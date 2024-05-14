#ifndef PLANEH
#define PLANEH

#include "vector.h"
#include "point.h"

class Plane {
public:
    double a, b, c, d; // Coeficientes do plano
    Point point;
    Vector normal;
    Vector color;

    Plane(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

    Plane(const Point& point, const Vector& normal, const Vector& color): point(point), normal(normal), color(color) {
        a = normal.x;
        b = normal.y;
        c = normal.z;
        //a*x + b*y + c*z + d = 0 -> d = -(a*x + b*y + c*z)
        d = -(a * point.x + b * point.y + c * point.z);
    }

    Vector normalVector() const {
        return Vector(a, b, c);
    }

    bool contains(const Point& point) const {
        return (a * point.x + b * point.y + c * point.z + d) == 0;
    }
};

#endif
