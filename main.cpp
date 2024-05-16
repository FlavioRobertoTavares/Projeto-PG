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
 
    Point origin = Point(0, 0, 0);
    Point target = Point(1, 0, 0);
    Vector up = Vector(0, 1, 0);
    Vector cor = Vector(0, 0, 0);
    double height = 500;
    double length = 500;
    double distance = 1;
    CAM cam = CAM(origin, target, up, cor, height, length, distance);

    Point center = Point(3.5, 0, -0.7);
    double radius = 1.5;
    Vector sp_color = Vector(200, 50, 0);
    Sphere sphere = Sphere(center, radius, sp_color);

    Point center2 = Point(7, 0, 1);
    double radius2 = 3;
    Vector sp_color2 = Vector(200, 250, 0);
    Sphere sphere2 = Sphere(center2, radius2, sp_color2);

    Point plane_origin = Point(0, 1, 0);
    Vector plane_normal = Vector(0, 1, 0);
    Vector plane_cor = Vector(20, 20, 150);
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