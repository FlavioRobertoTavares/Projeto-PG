#ifndef SPHEREH
#define SPHEREH

#include <math.h>
#include "vector.h"
#include "point.h"
#include "objects.h"
#include "ray.h"
using namespace std;
#define Not_intersect -1
#define Discard 1e-6

class Sphere: public Object {
public:
    Sphere(Point center, double radius, Vector color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior, bool have_texture, string name) 
        : center(center), radius(radius), Object(color, kd, ks, ka, kr, kt, nrugo, ior, have_texture, name) {}

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
            distance = distance1;

            if(distance1 < Discard){
                if(distance2 < Discard){
                    return Not_intersect;
                }
                distance = distance2;
            }

            if(distance1 > Discard && distance2 > Discard){distance = min(distance1, distance2);}

            return distance;
        }
        return Not_intersect;
    }

    Vector returnNormal(const ray& r, double t) override {
        Point intersection_point = r.at(t);
        Vector outward_normal = intersection_point - center;
        return outward_normal;
    }

    Vector getTextureColor(const ray& r, double t) override {
        double u, v, erre, g, b;
        int i, j, index;

        Vector normal = returnNormal(r, t);
        normal.make_unit_vector();
        u = 0.5 + atan2(normal.z, normal.x) / (2 * M_PI);
        v = 0.5 - asin(normal.y) / M_PI;

        i = static_cast<int>(u * texture->width);
        j = static_cast<int>(v * texture->height);

        i = std::max(0, std::min(i, texture->width - 1));
        j = std::max(0, std::min(j, texture->height - 1));
        
        index = (j * texture->width + i) * 3;
        
        //precisa normalizar aqui? Porque eu normalizo no phong já
        erre = texture->image[index] / 255.0;
        g = texture->image[index + 1] / 255.0;
        b = texture->image[index + 2] / 255.0;
        
        return Vector(erre, g, b);
    }

    Point center;
    double radius;
};

#endif