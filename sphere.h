#ifndef SPHEREH
#define SPHEREH

#include <math.h>
#include "vector.h"
#include "point.h"
#include "objects.h"
#include "ray.h"
using namespace std;

class Sphere: public Object {
    public:
        Sphere(Point center, double radius, Vector color) 
        :  center(center), radius(radius), Object(color) {}

        double intersect(const ray &r) override {
            double distance;
            Vector oc = center - r.origin();
            double A = r.direction().dot(r.direction().x, r.direction().y, r.direction().z);
            double B = -2*r.direction().dot(oc.x, oc.y, oc.z);
            double C = oc.dot(oc.x, oc.y, oc.z) - pow(radius, 2);

            double Delta = pow(B, 2) - 4*A*C;

            if(Delta >= 0){
                double distance1 = (-B+sqrt(Delta)) /  2*A;
                double distance2 = (-B-sqrt(Delta)) /  2*A;
                
                //retorna a menor e se ela não for menor que 0

                if(distance1 < 0){
                    distance = distance2;
                
                }else if(distance2 < 0){
                    distance = distance1;

                }else{
                    distance = min(distance1, distance2);
                }
                
                
            }else{
                distance = 0; 
            }

            return distance;

        }

        Point center;
        double radius;
};

#endif