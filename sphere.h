#ifndef SPHEREH
#define SPHEREH

#include <math.h>
#include "vector.h"
#include "point.h"
#include "ray.h"
using namespace std;

class Sphere {
    public:
        Sphere(Point center, double radius, Vector color) {
            this->center = center;
            this->radius = radius;
            this->color = color;
        }

        double intersect(const ray &r){
            double distance;
            double A = pow(r.direction().x, 2) + pow(r.direction().y, 2) + pow(r.direction().z, 2);
            double B = 2* ( (r.origin().x - center.x) + (r.origin().y - center.y) + (r.origin().z - center.z) );
            double C = pow((r.origin().x - center.x), 2) + pow((r.origin().y - center.y), 2) + pow((r.origin().z - center.z), 2) - pow(radius, 2);
            double Delta = pow(B, 2) - 4*A*C;

            if(Delta == 0){
                distance = (-B+sqrt(Delta)) /  2*A;

            }else if(Delta > 0){
                double distance1 = (-B+sqrt(Delta)) /  2*A;
                double distance2 = (-B-sqrt(Delta)) /  2*A;

                if(distance1 > distance2){
                    distance = distance2;
                }else{
                    distance = distance1;
                }
                
            }else if (Delta < 0){
                distance = 0;
                
            }

            return distance;

        }

        Point center;
        double radius;
        Vector color;
};

int main(){
    Sphere esfera(Point(1, 1, 1), 3, Vector(0, 0, 0));
    ray raio(Point(2, 2, 2), Vector(1, -3, 2));

    double dist = esfera.intersect(raio);
    cout << dist;

}



#endif