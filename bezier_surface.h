#ifndef BEZIER_SURFACE_H
#define BEZIER_SURFACE_H

#include <iostream>
#include <vector>
#include <cmath>  //pow()
#include <tuple>
#include <map>
#include "point.h"
#include "vector.h"
#include "ray.h"
#include "plane.h"
#include "objects.h"
#include "mesh.h"
using namespace std;
#define Not_intersect -1
#define Discard 1e-6

// Define a simple 3D point structure
/*struct Point3D {
    double x, y, z;
};*/

/*struct Triangle {
    int v1, v2, v3;
};*/

/*class Triangle {
public:
    Triangle(int idx1, int idx2, int idx3)
        : index1(idx1), index2(idx2), index3(idx3) {}

    int index1, index2, index3;
};*/


class Bezier: public Object {
    
    public:
    vector<vector<Point>> controlPoints; //a Bezier surface is a grid of control points
    vector<Triangle> triangles; //triangle mesh
    //map<tuple<double,double,double>, pair<double,double>> st;

    /*pair<double, double> getST(Point vertice) {
        return st[{vertice.x(), vertice.y(), vertice.z()}];
    }*/
  
    Bezier(vector<vector<Point>> controlPoints, Vector color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior)
        : Object(color, kd, ks, ka, kr, kt, nrugo, ior) {
            this->controlPoints = controlPoints;
            //this->triangles = generateTriangles(controlPoints, 0.1);
            //this->triangles = generateTriangles(flattenControlPoints(controlPoints), 0.1);
            this -> triangles = generateTriangles(0.1);
        }
        //~Bezier() = default;

    double intersect(const ray& r) override { //intersect mesh
        double dist;
        double menor_dist = INT_FAST16_MAX;
        for(Triangle tri : triangles){
            dist = tri.intersect(r);
            if(dist < menor_dist && dist > 0){menor_dist = dist;}
        }
        if(menor_dist == INT_FAST16_MAX){return 0;}
        return menor_dist;
    }

    Vector returnNormal(const ray& r, double t) override {
        for (Triangle tri : triangles) {
            double distance = tri.intersect(r);
            if (distance > 0 && distance == t) {
                Vector normal = (tri.B - tri.A) % (tri.C - tri.A);
                    
                // inverte a direção da normal se ela for igual a direção do raio
                if(r.direction().dot(normal.x, normal.y, normal.z) > 0){normal = normal*(-1);}

                normal.make_unit_vector();
                // retorna a normal desse triangulo na posição de interseção
                return normal;
            }
        }
        return Vector(0, 0, 0); // Return zero vector if no intersection found
    }

    //Código redundante para facilitar meu entendimento

    // Function to compute the interpolation between two points
    // Computes a point between two points based on parameter t
    Point interpolation(const Point& p1, const Point& p2, double t) {
        return { p1.x * (1 - t) + p2.x * t, p1.y * (1 - t) + p2.y * t, p1.z * (1 - t) + p2.z * t };
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
    double old_bernstein(int n, int i, double t) {
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
                double b = old_bernstein(n, i, u) * old_bernstein(m, j, v);
                point.x += b * curves[i][j].x;
                point.y += b * curves[i][j].y;
                point.z += b * curves[i][j].z;
            }
        }
        return point;
    }
    // Generate and print Bézier curve points
    void generateBezierCurve(const vector<Point>& controlPoints, int evaluationsNumber) {
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
    void generateBezierSurface(const vector<vector<Point>>& curves, int evaluationsNumber) {
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
    //Código redundante para facilitar meu entendimento

    // Compute Bernstein polynomial B_{i,n}(t)
    double bernstein(int i, int n, double t) {
        // Calculate the binomial coefficient (n choose i)
        double coef = 1.0;
        for (int j = 0; j < i; ++j){
            coef *= (n - j) / static_cast<double>(j + 1);
        }
         // Calculate the Bernstein polynomial B_{i,n}(t)
        return coef * pow(t, i) * pow(1 - t, n - i);
    }
    //com parâmetros s e t -> 1 ponto na superfície
    // Compute a bicubic Bézier surface point
    //Point bicubicBezier(const vector<vector<Point>>& controlPoints, double u, double v) {
    Point surface_point(double u, double v) { //double s,t
        int n = controlPoints.size(); // n=3 Degree of the polynomial (cubic)
        Point result = Point (0.0, 0.0, 0.0);
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
    /*Point surface_point(double s, double t) {
        // Example 4x4 grid of control points
        int nControlPoints= controlPoints.size();
        Point point = {0.0, 0.0, 0.0};
        vector<vector<Point>> controlPoints = {
            {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}},
            {{0, 1, 0}, {1, 1, 1}, {2, 1, 1}, {3, 1, 0}},
            {{0, 2, 0}, {1, 2, 1}, {2, 2, 1}, {3, 2, 0}},
            {{0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0}}
        };
        // Compute the point on the surface
        return bicubicBezier(controlPoints, s, t);
    }*/
    //Você calcula os pontos de bezier com os parâmetros s e t seguindo um nível de tolerância (tamanho do "passo" 
    //entre um triângulo e outro), que define quão detalhado vai ser a superfície (número de triângulos usados)
    //iterar sobre s e t, s e t entre 0 e 1 -> pontos da superfície de bezier
    vector<Point> getPointsFromSurface(double tolerance){
        vector<Point> bezier_points;
        for(double s=0; s<=1; s+=tolerance){
            for(double t=0; t<=1; t+=tolerance){
                bezier_points.push_back(surface_point(s,t));
                /*Point p = surface_point(s, t);
                bezier_points.push_back(p);
                cout << "Point: (" << p.x << ", " << p.y << ", " << p.z << ")\n"; // Debugging print*/
            }
        }
        return bezier_points;
    }

    vector<Point> flattenControlPoints(const vector<vector<Point>>& controlPoints) {
        vector<Point> points;
        for (const auto& row : controlPoints) {
            points.insert(points.end(), row.begin(), row.end());
        }
        return points;
    }

    // Function to generate triangles from Bézier surface points
    //vector<Triangle> generateTriangles(const vector<Point>& bezier_points, double tolerance) {
    vector<Triangle> generateTriangles(double tolerance) {
        vector<Triangle> listTriangles;
        int n = static_cast<int>(1 / tolerance); // Number of divisions along one axis
        int numPointsPerRow = n + 1; // Number of points per row in the grid
        vector<Point> bezier_points = getPointsFromSurface(tolerance);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Calculate indices for the current grid cell
                int index1 = i * numPointsPerRow + j;
                int index2 = (i + 1) * numPointsPerRow + j;
                int index3 = i * numPointsPerRow + j + 1;
                int index4 = (i + 1) * numPointsPerRow + j + 1;
                
                // Create two triangles for the current grid cell
                //listTriangles.push_back({ index1, index2, index3 });
                //listTriangles.push_back({ index2, index4, index3 });
                //listTriangles.push_back(Triangle(index1, index2, index3));
                //listTriangles.push_back(Triangle(index2, index4, index3));
                // Create two triangles for the current grid cell
                // Ensure indices are within bounds
                if (index1 < bezier_points.size() && index2 < bezier_points.size() && index3 < bezier_points.size() && index4 < bezier_points.size()) {
                    listTriangles.push_back(Triangle(bezier_points[index1], bezier_points[index2], bezier_points[index3]));
                    listTriangles.push_back(Triangle(bezier_points[index2], bezier_points[index4], bezier_points[index3]));
                }
            }
        }
        return listTriangles;
    }
};

//int main() {
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
   
    /*double tolerance = 0.1;
    vector<Point> bezier_points = getPointsFromSurface(tolerance);
    vector<Triangle> triangles = generateTriangles(bezier_points, tolerance);

    // Print triangles for debugging
    for (const auto& triangle : triangles) {
        cout << "Triangle: " << triangle.v1 << ", " << triangle.v2 << ", " << triangle.v3 << '\n';
    }

    return 0;
}
*/



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


