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
            double dist;
            Vector oc = center - r.origin();
            double A = r.direction().dot(r.direction().x, r.direction().y, r.direction().z);
            double B = -2*r.direction().dot(oc.x, oc.y, oc.z);
            double C = oc.dot(oc.x, oc.y, oc.z) - pow(radius, 2);

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
                
            }else{
                distance = 0; 
            }

            return distance;

        }

        Point center;
        double radius;
        Vector color;
};

#endif