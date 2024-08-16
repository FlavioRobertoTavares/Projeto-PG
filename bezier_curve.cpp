#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <iostream>
#include <vector>
#include "point.h"
#include "vector.h"
#include "objects.h"
using namespace std;

// Define a simple 3D point structure
/*struct Point3D {
    double x, y, z;
};*/

// Function to compute a cubic Bézier curve point in 3D
Point cubicBezier(Point P0, Point P1, Point P2, Point P3, double t) {
    Point result;
    double oneMinusT = 1.0 - t;
    double t2 = t * t;
    double t3 = t2 * t;
    double oneMinusT2 = oneMinusT * oneMinusT;
    double oneMinusT3 = oneMinusT2 * oneMinusT;

    result.x = oneMinusT3 * P0.x +
               3 * oneMinusT2 * t * P1.x +
               3 * oneMinusT * t2 * P2.x +
               t3 * P3.x;

    result.y = oneMinusT3 * P0.y +
               3 * oneMinusT2 * t * P1.y +
               3 * oneMinusT * t2 * P2.y +
               t3 * P3.y;

    result.z = oneMinusT3 * P0.z +
               3 * oneMinusT2 * t * P1.z +
               3 * oneMinusT * t2 * P2.z +
               t3 * P3.z;

    return result;
}

int main() {
    // Define control points in 3D
    Point P0 = {0.0, 0.0, 0.0};
    Point P1 = {1.0, 2.0, 1.0};
    Point P2 = {2.0, 2.0, -1.0};
    Point P3 = {3.0, 0.0, 0.0};

    double t = 0.5; // Parameter between 0 and 1

    // Compute the point on the curve
    Point result = cubicBezier(P0, P1, P2, P3, t);

    cout << "Point on the cubic Bezier curve at t = " << t << ": ("<< result.x << ", " << result.y << ", " << result.z << ")\n";

    return 0;
}

#endif

//Point on the cubic Bézier curve at t = 0.5: (1.5, 1.5, 0)
