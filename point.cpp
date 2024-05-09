#include <bits/stdc++.h>
#include <iostream>

class Point{
    public:
        double x, y, z;

        Point(double x, double y, double z) : x(x), y(y), z(z) {}

        Point(){
            x = 0;
            y = 0;
            z = 0;
        }

        void print(){
            std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
        }
};

Point operator+(const Point& p1, const Point& p2){
    return Point(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

Point operator-(const Point& p1, const Point& p2){
    return Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}