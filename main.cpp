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
    if(dist == 0){RGB = cam.cor;}
    
    cout << RGB.x << ' ' << RGB.y << ' ' << RGB.z << '\n';
}

int main(){
    //Sempre que criar algo novo, só precisa dar um push_back aqui
    vector<Sphere> Spheres;
    vector<Plane> Planes;
    
    //Criação da câmera
    Point origin = Point(0, 0, 0);
    Point target = Point(1, 0, 0);
    Vector up = Vector(0, 1, 0);
    Vector cor = Vector(0, 0, 0);
    double height = 500;
    double length = 500;
    double distance = 1;
    CAM cam = CAM(origin, target, up, cor, height, length, distance);

    //Criação da esfera 1 e sua adição a lista de Esferas
    Point center = Point(3.5, 0, -0.7);
    double radius = 1.5;
    Vector sp_color = Vector(20, 20, 20);
    Sphere sphere = Sphere(center, radius, sp_color);
    Spheres.push_back(sphere);

    //Criação da esfera 2 e sua adição a lista de Esferas
    Point center2 = Point(7, 0, 1);
    double radius2 = 3;
    Vector sp_color2 = Vector(200, 20, 0);
    Sphere sphere2 = Sphere(center2, radius2, sp_color2);
    Spheres.push_back(sphere2);

    //Criação do plano e sua adição a lista de Planos
    Point plane_origin = Point(0, 1, 0);
    Vector plane_normal = Vector(0, 1, 0);
    Vector plane_cor = Vector(20, 20, 190);
    Plane plane = Plane(plane_origin, plane_normal, plane_cor);
    Planes.push_back(plane);

    //Criação do ponto inicial de varredura e dos vetores de varredura
    Vector sup_esquerdo = cam.W*(cam.distance) + cam.V - cam.U ;
    Vector passo_x = cam.U*(2/(height-1));    
    Vector passo_y = cam.V*(2/(length-1));    

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