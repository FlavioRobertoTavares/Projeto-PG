#ifndef BEZIER_TEST_H
#define BEZIER_TEST_H

#include <iostream>
#include <vector>
#include "point.h"
#include "vector.h"

// Define a simple 3D point structure
struct Point3D {
    double x, y, z;
};

// Compute Bernstein polynomial B_{i,n}(t)
double bernstein(int i, int n, double t) {
    double coef = 1.0;
    for (int j = 0; j < i; ++j)
        coef *= (n - j) / static_cast<double>(j + 1);
    return coef * std::pow(t, i) * std::pow(1 - t, n - i);
}

//com parâmetros s e t -> 1 ponto na superfície
// Compute a bicubic Bézier surface point
Point3D bicubicBezier(const std::vector<std::vector<Point3D>>& controlPoints, double u, double v) {
    Point3D result = {0.0, 0.0, 0.0};
    int n = 3; // Degree of the polynomial (cubic)

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            double Bu = bernstein(i, n, u);
            double Bv = bernstein(j, n, v);
            result.x += Bu * Bv * controlPoints[i][j].x;
            result.y += Bu * Bv * controlPoints[i][j].y;
            result.z += Bu * Bv * controlPoints[i][j].z;
        }
    }

    return result;
}

int main() {
    // Example 4x4 grid of control points
    std::vector<std::vector<Point3D>> controlPoints = {
        {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}},
        {{0, 1, 0}, {1, 1, 1}, {2, 1, 1}, {3, 1, 0}},
        {{0, 2, 0}, {1, 2, 1}, {2, 2, 1}, {3, 2, 0}},
        {{0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0}}
    };

    double u = 0.5; // Parameter between 0 and 1
    double v = 0.5; // Parameter between 0 and 1

    Point3D result = bicubicBezier(controlPoints, u, v);

    std::cout << "Point on the surface at u = " << u << ", v = " << v << ": ("
              << result.x << ", " << result.y << ", " << result.z << ")\n";

    return 0;
}