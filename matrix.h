#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include "vector.h"
#include "point.h"
#include "ray.h"
using namespace std;

class Matrix{
    public:
        vector<vector<double>> elements;
        vector<vector<double>> elements_inverse;
        Matrix(){
            this->elements(4, vector<double>(4, 0))



        }
        

        ray transform_ray(const ray &r){
            double x, y, z;
            x = r.origin.x*elements_inverse[0][0] + r.origin.y*elements_inverse[0][1] + r.origin.z*elements_inverse[0][2];
            y = r.origin.x*elements_inverse[1][0] + r.origin.y*elements_inverse[1][1] + r.origin.z*elements_inverse[1][2];
            z = r.origin.x*elements_inverse[2][0] + r.origin.y*elements_inverse[2][1] + r.origin.z*elements_inverse[2][2];
            Point origin = Point(x, y, z);

            x = r.direction.x*elements_inverse[0][0] + r.direction.y*elements_inverse[0][1] + r.direction.z*elements_inverse[0][2];
            y = r.direction.x*elements_inverse[1][0] + r.direction.y*elements_inverse[1][1] + r.direction.z*elements_inverse[1][2];
            z = r.direction.x*elements_inverse[2][0] + r.direction.y*elements_inverse[2][1] + r.direction.z*elements_inverse[2][2];
            Vector direction = Vector(x, y, z);
            
            return ray(origin, direction);
        }

};