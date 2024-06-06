#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include "vector.h"
#include "point.h"
#include "ray.h"
using namespace std;

class Matrix{
    public:
        Matrix() = default;
        vector<vector<double>> elements(4, vector<double>(4, 0));
        vector<vector<double>> elements_inverse;

        ray transform_ray(const ray &r){
            double x, y, z;
            x = r.origin.x*elements_inverse[0][0] + r.origin.y*elements_inverse[0][1] + r.origin.z*elements_inverse[0][2] + elements_inverse[0][3];
            y = r.origin.x*elements_inverse[1][0] + r.origin.y*elements_inverse[1][1] + r.origin.z*elements_inverse[1][2] + elements_inverse[1][3];
            z = r.origin.x*elements_inverse[2][0] + r.origin.y*elements_inverse[2][1] + r.origin.z*elements_inverse[2][2] + elements_inverse[2][3];
            Point origin = Point(x, y, z);

            x = r.direction.x*elements_inverse[0][0] + r.direction.y*elements_inverse[0][1] + r.direction.z*elements_inverse[0][2];
            y = r.direction.x*elements_inverse[1][0] + r.direction.y*elements_inverse[1][1] + r.direction.z*elements_inverse[1][2];
            z = r.direction.x*elements_inverse[2][0] + r.direction.y*elements_inverse[2][1] + r.direction.z*elements_inverse[2][2];
            Vector direction = Vector(x, y, z);
            
            return ray(origin, direction);
        }

};


/*
PARTE DE INVERTER
double det;
    vector<vector<double> inv(4, vector<double>(4, 0))

    inv[0][0] = m[1][1]  * m[2][2] * m[3][3] - 
             m[1][1]  * m[2][3] * m[3][2] - 
             m[2][1]  * m[1][2]  * m[3][3] + 
             m[2][1]  * m[1][3]  * m[3][2] +
             m[3][1] * m[1][2]  * m[2][3] - 
             m[3][1] * m[1][3]  * m[2][2];

    inv[1][0] = -m[1][0]  * m[2][2] * m[3][3] + 
              m[1][0]  * m[2][3] * m[3][2] + 
              m[2][0]  * m[1][2]  * m[3][3] - 
              m[2][0]  * m[1][3]  * m[3][2] - 
              m[3][0] * m[1][2]  * m[2][3] + 
              m[3][0] * m[1][3]  * m[2][2];

    inv[2][0] = m[1][0]  * m[2][1] * m[3][3] - 
             m[1][0]  * m[2][3] * m[3][1] - 
             m[2][0]  * m[1][1] * m[3][3] + 
             m[2][0]  * m[1][3] * m[3][1] + 
             m[3][0] * m[1][1] * m[2][3] - 
             m[3][0] * m[1][3] * m[2][1];

    inv[3][0] = -m[1][0]  * m[2][1] * m[3][2] + 
               m[1][0]  * m[2][2] * m[3][1] +
               m[2][0]  * m[1][1] * m[3][2] - 
               m[2][0]  * m[1][2] * m[3][1] - 
               m[3][0] * m[1][1] * m[2][2] + 
               m[3][0] * m[1][2] * m[2][1];

    inv[0][1] = -m[0][1]  * m[2][2] * m[3][3] + 
              m[0][1]  * m[2][3] * m[3][2] + 
              m[2][1]  * m[0][2] * m[3][3] - 
              m[2][1]  * m[0][3] * m[3][2] - 
              m[3][1] * m[0][2] * m[2][3] + 
              m[3][1] * m[0][3] * m[2][2];

    inv[1][1] = m[0][0]  * m[2][2] * m[3][3] - 
             m[0][0]  * m[2][3] * m[3][2] - 
             m[2][0]  * m[0][2] * m[3][3] + 
             m[2][0]  * m[0][3] * m[3][2] + 
             m[3][0] * m[0][2] * m[2][3] - 
             m[3][0] * m[0][3] * m[2][2];

    inv[2][1] = -m[0][0]  * m[2][1] * m[3][3] + 
              m[0][0]  * m[2][3] * m[3][1] + 
              m[2][0]  * m[0][1] * m[3][3] - 
              m[2][0]  * m[0][3] * m[3][1] - 
              m[3][0] * m[0][1] * m[2][3] + 
              m[3][0] * m[0][3] * m[2][1];

    inv[3][1] = m[0][0]  * m[2][1] * m[3][2] - 
              m[0][0]  * m[2][2] * m[3][1] - 
              m[2][0]  * m[0][1] * m[3][2] + 
              m[2][0]  * m[0][2] * m[3][1] + 
              m[3][0] * m[0][1] * m[2][2] - 
              m[3][0] * m[0][2] * m[2][1];

    inv[0][2] = m[0][1]  * m[1][2] * m[3][3] - 
             m[0][1]  * m[1][3] * m[3][2] - 
             m[1][1]  * m[0][2] * m[3][3] + 
             m[1][1]  * m[0][3] * m[3][2] + 
             m[3][1] * m[0][2] * m[1][3] - 
             m[3][1] * m[0][3] * m[1][2];

    inv[1][2] = -m[0][0]  * m[1][2] * m[3][3] + 
              m[0][0]  * m[1][3] * m[3][2] + 
              m[1][0]  * m[0][2] * m[3][3] - 
              m[1][0]  * m[0][3] * m[3][2] - 
              m[3][0] * m[0][2] * m[1][3] + 
              m[3][0] * m[0][3] * m[1][2];

    inv[2][2] = m[0][0]  * m[1][1] * m[3][3] - 
              m[0][0]  * m[1][3] * m[3][1] - 
              m[1][0]  * m[0][1] * m[3][3] + 
              m[1][0]  * m[0][3] * m[3][1] + 
              m[3][0] * m[0][1] * m[1][3] - 
              m[3][0] * m[0][3] * m[1][1];

    inv[3][2] = -m[0][0]  * m[1][1] * m[3][2] + 
               m[0][0]  * m[1][2] * m[3][1] + 
               m[1][0]  * m[0][1] * m[3][2] - 
               m[1][0]  * m[0][2] * m[3][1] - 
               m[3][0] * m[0][1] * m[1][2] + 
               m[3][0] * m[0][2] * m[1][1];

    inv[0][3] = -m[0][1] * m[1][2] * m[2][3] + 
              m[0][1] * m[1][3] * m[2][2] + 
              m[1][1] * m[0][2] * m[2][3] - 
              m[1][1] * m[0][3] * m[2][2] - 
              m[2][1] * m[0][2] * m[1][3] + 
              m[2][1] * m[0][3] * m[1][2];

    inv[1][3] = m[0][0] * m[1][2] * m[2][3] - 
             m[0][0] * m[1][3] * m[2][2] - 
             m[1][0] * m[0][2] * m[2][3] + 
             m[1][0] * m[0][3] * m[2][2] + 
             m[2][0] * m[0][2] * m[1][3] - 
             m[2][0] * m[0][3] * m[1][2];

    inv[2][3] = -m[0][0] * m[1][1] * m[2][3] + 
               m[0][0] * m[1][3] * m[2][1] + 
               m[1][0] * m[0][1] * m[2][3] - 
               m[1][0] * m[0][3] * m[2][1] - 
               m[2][0] * m[0][1] * m[1][3] + 
               m[2][0] * m[0][3] * m[1][1];

    inv[3][3] = m[0][0] * m[1][1] * m[2][2] - 
              m[0][0] * m[1][2] * m[2][1] - 
              m[1][0] * m[0][1] * m[2][2] + 
              m[1][0] * m[0][2] * m[2][1] + 
              m[2][0] * m[0][1] * m[1][2] - 
              m[2][0] * m[0][2] * m[1][1];

    det = m[0][0] * inv[0][0] + m[0][1] * inv[1][0] + m[0][2] * inv[2][0] + m[0][3] * inv[3][0];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++){
            invOut[i][j] = inv[i][j] * det;
        }  

    return true;

*/