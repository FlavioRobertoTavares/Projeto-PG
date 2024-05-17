#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "vector.h"
#include "point.h"
#include "cam.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
using namespace std;

//Organiza a lista do menor pro maior, mas se for 0, ele coloca no final da lista
bool return_min_dist(const pair<double, Vector> &dist1, const pair<double, Vector> &dist2){
    if(dist1.first == 0){return false;}
    if(dist2.first == 0){return true;}
    return dist1.first < dist2.first;
}

//Vai passar por todas as esferas e planos da lista Spheres e Planes, para então ver qual tem a menor dist entre eles
//E então printa a cor na tela
void Render(const CAM &cam, const vector<Sphere> &Spheres, vector<Plane> &Planes, const ray &raio){
    vector<pair<double, Vector>> distances;
    double dist;
    Vector RGB;

    for(Sphere sphere : Spheres){
        dist = sphere.intersect(raio);
        RGB = sphere.color;
        distances.push_back(make_pair(dist, RGB));
    }

    for(Plane plane : Planes){
        dist = plane.intersect(raio);
        RGB = plane.color;
        distances.push_back(make_pair(dist, RGB));
    }

    //Aqui ele organiza para pegar a menor dist, a de indice 0, se tal dist for == 0, ele coloca a cor da câmera
    sort(distances.begin(), distances.end(), return_min_dist);
    dist = distances[0].first;
    RGB = distances[0].second;
    //Se der algum erro, pode ser aqui
    if( (dist == 0) || (dis < cam.distance) ){RGB = cam.cor;}
    
    cout << RGB.x << ' ' << RGB.y << ' ' << RGB.z << '\n';
}

int main(){
    //Coisas acontecerão aqui
    double x, y, z, foo, height, length, distance;
    vector<Sphere> Spheres;
    vector<Plane> Planes;

    cin >> x >> y >> z;
    Point origin = Point(x, y, z);

    cin >> x >> y >> z;
    Point target = Point(x, y, z);

    cin >> x >> y >> z;
    Vector up = Vector(x, y, z);

    cin >> x >> y >> z;
    Vector cor = Vector(x, y, z);

    cin >> foo;
    height = foo;

    cin >> foo;
    length = foo;

    cin >> foo;
    distance = foo;

    CAM cam = CAM(origin, target, up, cor, height, length, distance);
    Vector sup_esquerdo = cam.W*(cam.distance) + cam.V - cam.U ;
    Vector passo_x = cam.U*(2/(length-1));
    Vector passo_y = cam.V*(2/(height-1));    

    for(string input = ""; input != "generate"; cin >> input){

        if(input == "sphere"){
        
            cin >> x >> y >> z;
            Point center = Point(x, y, z);
            
            cin >> x;
            double radius = x;

            cin >> x >> y >> z;
            Vector sp_color = Vector(x, y ,z);
            
            Sphere sphere = Sphere(center, radius, sp_color);
            Spheres.push_back(sphere);
        
        }else if(input == "plane"){

            cin >> x >> y >> z;
            Point plane_origin = Point(x, y, z);

            cin >> x >> y >> z;
            Vector plane_normal = Vector(x, y, z);

            cin >> x >> y >> z;
            Vector plane_cor = Vector(x, y, z);
            
            Plane plane = Plane(plane_origin, plane_normal, plane_cor);
            Planes.push_back(plane);
        }
    }
    
    cout << "P3\n" << length << " " << height << "\n255\n";
    
    for(double y = 0; y < height; y++){
        for(double x = 0; x < length; x++){
            ray raio = ray(cam.origin, sup_esquerdo + (passo_x*x) - (passo_y*y));
            //Aqui ele manda o raio pra renderizar a cor certa na tela
            Render(cam, Spheres, Planes, raio);
        }
    }

    return 0;
}
