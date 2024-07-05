#ifndef PLANEH
#define PLANEH

#include "vector.h"
#include "point.h"
#include "objects.h"
#include "ray.h"
using namespace std;

class Plane: public Object {
public:
    double a, b, c, d; // Coeficientes do plano
    Point point;
    Vector normal;

    Plane(const Point& point, const Vector& normal, const Vector& color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior) 
    : point(point), normal(normal), Object(color, kd, ks, ka, kr, kt, nrugo, ior) {
        a = normal.x;
        b = normal.y;
        c = normal.z;
        //a*x + b*y + c*z + d = 0 -> d = -(a*x + b*y + c*z)
        d = -(a * point.x + b * point.y + c * point.z);
    }

    double intersect(const ray &r) override {
        
         //Agora só retorna se não for menor que 0
        if(normal.dot(r.direction().x, r.direction().y, r.direction().z) != 0){
            double distance = (normal.dot(point.x, point.y, point.z) - normal.dot(r.origin().x, r.origin().y, r.origin().z)) / normal.dot(r.direction().x, r.direction().y, r.direction().z);
            if(distance < 0){
                return 0;
            }
            return distance;

        }
        return 0;

    }

    // retorna a normal que definida na inicialização
    // é constante ao longo de todo o plano
    Vector returnNormal(const ray& r, double t) override {

         // inverte a direção da normal se ela for igual a direção do raio
        if(r.direction().dot(normal.x, normal.y, normal.z) > 0){normal = normal*(-1);}

        return normal;
    }

    Vector normalVector() const {
        return Vector(a, b, c);
    }

    bool contains(const Point& point) const {
        return (a * point.x + b * point.y + c * point.z + d) == 0;
    }
};

#endif
