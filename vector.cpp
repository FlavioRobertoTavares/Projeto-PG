#include <bits/stdc++.h>
#include <iostream>

//classe do vetor
class Vector{
        public:
           double x, y, z;

            Vector(double x, double y, double z) : x(x), y(y), z(z) {}

            Vector(){
                x = 0;
                y = 0;
                z = 0;
            }   
            
            double norm(){
                double norm = sqrt(x*x + y*y + z*z);
                return norm;
            }

            void dot(double a, double b, double c){
                x *= a;
                y *= b;
                z *= c;
            }

            void cross(double a, double b, double c){
                double x = this->x;
                double y = this->y;
                double z = this->z;

                this->x = y*c - z*b;
                this->y = z*a - x*c;
                this->z = x*b - y*a;
            }

            void make_unit_vector(){
                double norma = norm();
                x = x/norma;
                y = y/norma;
                z = z/norma;
            }

            void print(){
                std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
            }
};

//overload das operações com vetor
Vector operator+(const Vector& v1, const Vector& v2){
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector operator-(const Vector& v1, const Vector& v2){
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector operator*(const Vector& v1, const Vector& v2){
    return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector operator*(const Vector& v, double n){
    return Vector(v.x * n, v.y * n, v.z * n);
}

Vector operator/(const Vector& v1, const Vector& v2){
    return Vector(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vector operator/(const Vector& v, double n){
    return Vector(v.x / n, v.y / n, v.z / n);
}

int main (){

    Vector vetor1(1, 2, 3);
    Vector vetor2(2, 5, 4);
    Vector null;

//Test vector
    vetor1.print();
    vetor2.print();

//Test constructor
    null.print();

//Test times multiplication
    vetor1 = vetor1 * 3;
    vetor1.print();

    vetor1 = vetor1 * vetor2;
    vetor1.print();

//Test vector plusition
    vetor1 = vetor1 + vetor2;
    vetor1.print();

//Test dot product
    vetor1.dot(3, 2, 1);
    vetor1.print();

//Test cross product
    vetor1.cross(1, 2, 3);
    vetor1.print();

    return 0;
    
}
