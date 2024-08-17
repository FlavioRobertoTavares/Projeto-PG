#include <iostream>
#include <vector>
#include "mesh.h"
#include "ray.h"
#include "point.h"
#include "vector.h"
#include "plane.h"
#include "objects.h"

using namespace std;

int main() {
    // Step 1: Define vertices
    vector<Point> vertices;
    vertices.push_back(Point(0, 0, 0)); // Vertex A
    vertices.push_back(Point(1, 0, 0)); // Vertex B
    vertices.push_back(Point(0, 1, 0)); // Vertex C
    
    // Step 2: Define triangles
    vector<vector<int>> triangles;
    triangles.push_back({0, 1, 2}); // Triangle using vertices A, B, C

    // Step 3: Define the mesh color and material properties
    Vector color(1, 0, 0); // Red color
    double kd = 0.8, ks = 0.5, ka = 0.1, kr = 0.0, kt = 0.0, nrugo = 20;
    double ior = 1.0;

    // Step 4: Construct the Mesh object
    Mesh mesh(1, 3, vertices, triangles, color, kd, ks, ka, kr, kt, nrugo, ior);

    // Step 5: Define a ray that intersects the triangle
    Point ray_origin(0.5, 0.5, -1); // Origin of the ray
    Vector ray_direction(0, 0, 1);   // Direction of the ray (pointing towards the triangle)
    ray test_ray(ray_origin, ray_direction);

    // Step 6: Test intersection
    double intersection_distance = mesh.intersect(test_ray);
    cout << "Intersection Distance: " << intersection_distance << endl;

    // Step 7: Test normal calculation
    if (intersection_distance > 0) {
        Vector normal = mesh.returnNormal(test_ray, intersection_distance);
        cout << "Normal at Intersection: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << endl;
    } else {
        cout << "No intersection detected." << endl;
    }

    return 0;
}

//Intersection Distance: 1
//Normal at Intersection: (-0, -0, -1)
