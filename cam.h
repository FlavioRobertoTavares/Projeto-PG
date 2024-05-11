#ifndef CAMH
#define CAMH

#include <bits/stdc++.h>
#include <iostream>
#include "vector.h"
#include "point.h"

class CAM{
    public:
        CAM(Point origin, Point target, Vector up, Vector cor, double height, double length, double distance){
            this->origin = origin;
            this->target = target;
            this->up = up;
            this->cor = cor;
            this->distance = distance;
            this->height = height;
            this->length = length;
            W = target - origin;
            V = W.cross(up.x, up.y, up.z);
            U = V.cross(W.x, W.y, W.z);

        }

        Point origin;
        Point target;
        Vector up;
        Vector W;
        Vector V;
        Vector U;
        Vector cor;
        double distance;
        double height;
        double length;

};

#endif