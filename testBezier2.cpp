#include <iostream>
#include <vector>
#include "bezier_surface.h" 
#include "point.h"
#include "vector.h"
#include "ray.h"

using namespace std;

int main() {
    // Define a 4x4 grid of control points for the Bézier surface
    vector<vector<Point>> controlPoints = {
        {Point(0, 0, 0), Point(1, 0, 0), Point(2, 0, 0), Point(3, 0, 0)},
        {Point(0, 1, 1), Point(1, 1, 1), Point(2, 1, 1), Point(3, 1, 1)},
        {Point(0, 2, 2), Point(1, 2, 2), Point(2, 2, 2), Point(3, 2, 2)},
        {Point(0, 3, 3), Point(1, 3, 3), Point(2, 3, 3), Point(3, 3, 3)}
    };

    // Define the color and material properties
    Vector color(1, 0, 0); // Red color
    double kd = 0.8, ks = 0.5, ka = 0.1, kr = 0.0, kt = 0.0, nrugo = 20;
    double ior = 1.0;

    // Create the Bézier surface object
    Bezier bezierSurface(controlPoints, color, kd, ks, ka, kr, kt, nrugo, ior);

    // Define a ray that intersects the Bézier surface
    Point ray_origin(1, 1, -1); // Origin of the ray
    Vector ray_direction(0, 0, 1); // Direction of the ray (pointing towards the surface)
    ray test_ray(ray_origin, ray_direction);

    // Test intersection
    double intersection_distance = bezierSurface.intersect(test_ray);
    cout << "Intersection Distance: " << intersection_distance << endl;

    // Test normal calculation
    if (intersection_distance > 0) {
        Vector normal = bezierSurface.returnNormal(test_ray, intersection_distance);
        cout << "Normal at Intersection: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << endl;
    } else {
        cout << "No intersection detected." << endl;
    }

    return 0;
}

//Intersection Distance: 1.0
//Normal at Intersection: (0, 0, 1)

