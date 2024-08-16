#ifndef BEZIER_SURFACE1_H
#define BEZIER_SURFACE1_H

#include <iostream>
#include <vector>
#include <cmath>
#include "point.h"
#include "vector.h"
#include "objects.h"
using namespace std;

// Define a simple 3D point structure
/*struct Point3D {
    double x, y, z;
};*/

// Function to compute the interpolation between two points
// Computes a point between two points based on parameter t
Point interpolation(const Point& p1, const Point& p2, double t) {
    return { p1.x * (1 - t) + p2.x * t, 
             p1.y * (1 - t) + p2.y * t, 
             p1.z * (1 - t) + p2.z * t };
}

// Function for De Casteljau's algorithm to compute Bézier curve points
Point deCasteljau(const vector<Point>& points, double t) {
    size_t grade = points.size() - 1;
    if (grade == 1) {
        return interpolation(points[0], points[1], t);
    } else {
        vector<Point> auxPoints;
        for (size_t i = 0; i < grade; ++i) {
            auxPoints.push_back(interpolation(points[i], points[i + 1], t));
        }
        return deCasteljau(auxPoints, t);
    }
}

// Compute the factorial of a number
int factorial(int x) {
    int f = 1;
    for (int i = 2; i <= x; ++i) f *= i;
    return f;
}

// Compute the Bernstein polynomial
double bernstein(int n, int i, double t) {
    return factorial(n) / (factorial(i) * factorial(n - i)) * pow(t, i) * pow(1 - t, n - i);
}

// Compute a cubic Bézier curve point
Point cubicBezier(const vector<Point>& controlPoints, double t) {
    return deCasteljau(controlPoints, t);
}

// Compute a point on a Bézier surface
Point bezierSurface(const vector<vector<Point>>& curves, double u, double v) {
    int n = curves.size() - 1;
    int m = curves[0].size() - 1;
    Point point = {0, 0, 0};

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            double b = bernstein(n, i, u) * bernstein(m, j, v);
            point.x += b * curves[i][j].x;
            point.y += b * curves[i][j].y;
            point.z += b * curves[i][j].z;
        }
    }

    return point;
}

// Generate and print Bézier curve points
void drawBezierCurve(const vector<Point>& controlPoints, int evaluationsNumber) {
    vector<Point> bezierPoints;
    for (int i = 0; i <= evaluationsNumber; ++i) {
        double t = i / static_cast<double>(evaluationsNumber);
        bezierPoints.push_back(cubicBezier(controlPoints, t));
    }

    // Print curve points for debugging
    for (const auto& point : bezierPoints) {
        cout << "Curve Point: (" << point.x << ", " << point.y << ", " << point.z << ")\n";
    }
}

// Generate and print Bézier surface points
void drawBezierSurface(const vector<vector<Point>>& curves, int evaluationsNumber) {
    for (int i = 0; i <= evaluationsNumber; ++i) {
        double v = i / static_cast<double>(evaluationsNumber);
        vector<Point> rowPoints;
        for (int j = 0; j <= evaluationsNumber; ++j) {
            double u = j / static_cast<double>(evaluationsNumber);
            rowPoints.push_back(bezierSurface(curves, u, v));
        }

        // Print surface points for debugging
        for (const auto& point : rowPoints) {
            cout << "Surface Point: (" << point.x << ", " << point.y << ", " << point.z << ")\n";
        }
    }
}

int main() {
    // Example control points for Bézier curve
    vector<Point> curveControlPoints = {
        {0, 0, 0},
        {1, 2, 1},
        {2, 2, -1},
        {3, 0, 0}
    };

    // Example control points for Bézier surface
    vector<vector<Point>> surfaceControlPoints = {
        { {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0} },
        { {0, 1, 0}, {1, 1, 1}, {2, 1, 1}, {3, 1, 0} },
        { {0, 2, 0}, {1, 2, 1}, {2, 2, 1}, {3, 2, 0} },
        { {0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0} }
    };

    int evaluationsNumber = 10;

    // Draw Bézier curve
    drawBezierCurve(curveControlPoints, evaluationsNumber);

    // Draw Bézier surface
    drawBezierSurface(surfaceControlPoints, evaluationsNumber);

    return 0;
}

#endif