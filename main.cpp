#include <bits/stdc++.h>
#include <iostream>
#include "vector.h"
#include "point.h"
#include "cam.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"

using namespace std;

int main(){
    //Coisas acontecerão aqui
    double x, y, z;

    //cout << "CAMERA: \n";

    //cout << "ORIGEM: ";
    cin >> x >> y >> z;
    Point origin = Point(x, y, z);

    //cout << "TARGET: ";
    cin >> x >> y >> z;
    Point target = Point(x, y, z);

    //cout << "UP: ";
    cin >> x >> y >> z;
    Vector up = Vector(x, y, z);
    
    //cout << "COR: ";
    cin >> x >> y >> z;
    Vector cor = Vector(x, y, z);

    double height;
    double foo;
    //cout << "ALTURA: ";
    cin >> foo;
    height = foo;

    double length;
    //cout << "COMPRIMENTO: ";
    cin >> foo;
    length = foo;

    double distance = 1;


    CAM cam = CAM(origin, target, up, cor, height, length, distance);

//SPHERE 1:
    //CENTER:
    cin >> x >> y >> z;
    Point center = Point(x, y, z);
    
    cin >> x;
    double radius = x;

    cin >> x >> y >> z;
    Vector sp_color = Vector(x, y ,z);
    Sphere sphere = Sphere(center, radius, sp_color);


    //SPHERE 2:
    cin >> x >> y >> z;
    Point center2 = Point(x, y, z);

    cin >> x;
    double radius2 = x;

    cin >> x >> y >> z;
    Vector sp_color2 = Vector(x, y, z);

    Sphere sphere2 = Sphere(center2, radius2, sp_color2);

    cin >> x >> y >> z;
    Point plane_origin = Point(x, y, z);

    cin >> x >> y >> z;
    Vector plane_normal = Vector(x, y, z);
    cin >> x >> y >> z;
    Vector plane_cor = Vector(x, y, z);
    
    Plane plane = Plane(plane_origin, plane_normal, plane_cor);

    Vector sup_esquerdo = cam.W*(cam.distance) + cam.V - cam.U ;
    Vector passo_x = cam.U*(2/(height-1));    
    Vector passo_y = cam.V*(2/(length-1));    

    cout << "P3\n" << length << " " << height << "\n255\n";
    
    for(double y = 0; y < height; y++){
        for(double x = 0; x < length; x++){
            ray raio = ray(cam.origin, sup_esquerdo + (passo_x*x) - (passo_y*y));
            double intersect_s = sphere.intersect(raio);
            double intersect_s2 = sphere2.intersect(raio);
            double intersect_p = plane.intersect(raio);
            double intersect;
            
            //Fica mt grande o if pra usar o max com distâncias = 0 quando não tiver interseção
            //Então eu troquei os 0's por INT_MAX só pra a gente poder testar msm
            //Mas depois que tudo tiver certo, temos que refazer essa parte de um jeito bem melhor, usando vectors ou tuplas e tals

            if(intersect_p == 0){
                intersect_p = INT16_MAX;

            }
            if(intersect_s == 0){
                intersect_s = INT16_MAX;
            
            }
            if(intersect_s2 == 0){
                intersect_s2 = INT16_MAX;

            }

            intersect = min(intersect_p, min(intersect_s, intersect_s2));
            
            if(intersect == INT16_MAX){
                cout << cam.cor.x << ' ' << cam.cor.y << ' ' << cam.cor.z << '\n';

            }else{
                if (intersect == intersect_p)
                    cout << plane.color.x << ' ' << plane.color.y << ' ' << plane.color.z << '\n';

                else if(intersect == intersect_s) {
                    cout << sphere.color.x << ' ' << sphere.color.y << ' ' << sphere.color.z << '\n';

                }else{
                    cout << sphere2.color.x << ' ' << sphere2.color.y << ' ' << sphere2.color.z << '\n';

                }
            
            }

        }
    }

    return 0;
}