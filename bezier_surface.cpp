#ifndef BEZIER_SURFACE_H
#define BEZIER_SURFACE_H

#include <iostream>
#include <vector>
#include "point.h"
//#include "vector.h"
#include "objects.h"
using namespace std;

// Define a simple 3D point structure
/*struct Point3D {
    double x, y, z;
};*/

struct Triangle {
    int v1, v2, v3;
};

// Compute Bernstein polynomial B_{i,n}(t)
double bernstein(int i, int n, double t) {
    double coef = 1.0;
    for (int j = 0; j < i; ++j)
        coef *= (n - j) / static_cast<double>(j + 1);
    return coef * pow(t, i) * pow(1 - t, n - i);
}

//com parâmetros s e t -> 1 ponto na superfície
// Compute a bicubic Bézier surface point
Point bicubicBezier(const vector<vector<Point>>& controlPoints, double u, double v) {
    Point result = {0.0, 0.0, 0.0};
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

// Wrapper function to get a point on the surface given s and t
Point surface_point(double s, double t) {
    // Example 4x4 grid of control points
    vector<vector<Point>> controlPoints = {
        {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}},
        {{0, 1, 0}, {1, 1, 1}, {2, 1, 1}, {3, 1, 0}},
        {{0, 2, 0}, {1, 2, 1}, {2, 2, 1}, {3, 2, 0}},
        {{0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0}}
    };

    // Compute the point on the surface
    return bicubicBezier(controlPoints, s, t);
}

//Você calcula os pontos de bezier com os parâmetros s e t seguindo um nível de tolerância (tamanho do "passo" 
//entre um triângulo e outro), que define quão detalhado vai ser a superfície (número de triângulos usados)
//iterar sobre s e t, s e t entre 0 e 1 -> pontos da superfície de bezier
vector<Point> getPointsFromSurface(double tolerance){
    vector<Point> bezier_points;
    for(double s=0; s<=1; s+=tolerance){
        for(double t=0; t<=1; t+=tolerance){
            bezier_points.push_back(surface_point(s,t));
            Point p = surface_point(s, t);
            bezier_points.push_back(p);
            cout << "Point: (" << p.x << ", " << p.y << ", " << p.z << ")\n"; // Debugging print
        }
    }
    return bezier_points;
}

// Function to generate triangles from Bézier surface points
vector<Triangle> generateTriangles(const vector<Point>& bezier_points, double tolerance) {
    vector<Triangle> listTriangles;

    int n = static_cast<int>(1 / tolerance); // Number of divisions along one axis
    int numPointsPerRow = n + 1; // Number of points per row in the grid

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Calculate indices for the current grid cell
            int index1 = i * numPointsPerRow + j;
            int index2 = (i + 1) * numPointsPerRow + j;
            int index3 = i * numPointsPerRow + j + 1;
            int index4 = (i + 1) * numPointsPerRow + j + 1;

            // Create two triangles for the current grid cell
            listTriangles.push_back({ index1, index2, index3 });
            listTriangles.push_back({ index2, index4, index3 });
        }
    }

    return listTriangles;
}

int main() {
    // Example 4x4 grid of control points
    /*vector<vector<Point>> controlPoints = {
        {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}},
        {{0, 1, 0}, {1, 1, 1}, {2, 1, 1}, {3, 1, 0}},
        {{0, 2, 0}, {1, 2, 1}, {2, 2, 1}, {3, 2, 0}},
        {{0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0}}
    };

    double u = 0.5; // Parameter between 0 and 1
    double v = 0.5; // Parameter between 0 and 1

    Point result = bicubicBezier(controlPoints, u, v);

    cout << "Point on the surface at u = " << u << ", v = " << v << ": ("<< result.x << ", " << result.y << ", " << result.z << ")\n";

    // Example usage
    double tolerance = 0.1;
    vector<Point> bezier_points = {
        // Example points; in practice, populate this with actual Bézier surface points
        {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0},
        {0, 1, 0}, {1, 1, 1}, {2, 1, 1}, {3, 1, 0},
        {0, 2, 0}, {1, 2, 1}, {2, 2, 1}, {3, 2, 0},
        {0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0}
    };

    vector<Triangle> triangles = generateTriangles(bezier_points, tolerance);

    // Print triangles for debugging
    for (const auto& triangle : triangles) {
        cout << "Triangle: " << triangle.v1 << ", " << triangle.v2 << ", " << triangle.v3 << '\n';
    }*/
   
    double tolerance = 0.1;
    vector<Point> bezier_points = getPointsFromSurface(tolerance);
    vector<Triangle> triangles = generateTriangles(bezier_points, tolerance);

    // Print triangles for debugging
    for (const auto& triangle : triangles) {
        cout << "Triangle: " << triangle.v1 << ", " << triangle.v2 << ", " << triangle.v3 << '\n';
    }

    return 0;
}



//vai armazenando os pontos em uma lista e usa essa lista para construir os triângulos
       /* int n = int(1/tolerance);
        int numberOfPoints = bezier_points.size();

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                listTriangles.push_back({i * (n+1) + j, (i+1) * (n+1) + j, i * (n+1) + j + 1}); 
                listTriangles.push_back({(i+1) * (n+1) + j, (i+1) * (n+1) + j + 1, i * (n+1) + j + 1}); 
            }
        }*/

//depois de armazenar os triângulos, você pode desenhar a superfície de bezier
    /*for(auto triangle : listTriangles){
        glBegin(GL_TRIANGLES);
        glVertex3f(bezier_points[triangle[0]].x, bezier_points[triangle[0]].y, bezier_points[triangle[0]].z);
        glVertex3f(bezier_points[triangle[1]].x, bezier_points[triangle[1]].y, bezier_points[triangle[1]].z);
        glVertex3f(bezier_points[triangle[2]].x, bezier_points[triangle[2]].y, bezier_points[triangle[2]].z);
        glEnd();
    }*/

//pontos que definem a superficie -> criar os triângulos; quais os 3 pontos que formam um triângulo para adicionar na mesh
//superficies parametrizadas -> dominio da função, parametros s e t, variam entre 0 e 1
//os pontos para cada valor de s e t, todos os pontos que fazem parte da surperfice
//os 3 pontos que formam o triangulo dependem de s e t
//passar triângulos para a mesh -> mesh recebe os indices dos vertices
//cada triângulo é formado por 3 indices, cada indice é um ponto da superficie

#endif



