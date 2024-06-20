#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "vector.h"
#include "point.h"
#include "cam.h"
#include "objects.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "mesh.h"
#include "matrix.h"
using namespace std;

//Organiza a lista do menor pro maior, mas se for 0, ele coloca no final da lista
bool return_min_dist(const pair<double, Object*> &dist1, const pair<double, Object*> &dist2){
    if(dist1.first == 0){return false;}
    if(dist2.first == 0){return true;}
    return dist1.first < dist2.first;
}

Vector Phong(CAM cam, Object* Object, ray raio, double t){
    Vector normal = Object->returnNormal(raio, t); //Retorna a normal N que será usada no Phong
    auto example = Object->ka; //Retorna o ka do Phong, só fazer o mesmo para os outros

    //Tá faltando colocar no escopo da função  o Light ligths que é a lista de luzes que vão iterar no sigma de phong
    //Quando vitoria fizer a classe light eu atualizo aqui

    return Vector(0, 0, 0);
}


//Vai passar por todas as esferas e planos da lista Spheres e Planes, para então ver qual tem a menor dist entre eles
//E então printa a cor na tela
void Render(const CAM &cam, const vector<Object*> &Objects, const ray &raio){
    vector<pair<double, Object*>> distances;
    double dist;
    Vector RGB;
    Object* Object;

    for(const auto& object : Objects){
        dist = object->intersect(raio);
        distances.push_back(make_pair(dist, object));
    }

    //Aqui ele organiza para pegar a menor dist, a de indice 0, se tal dist for == 0, ele coloca a cor da câmera
    sort(distances.begin(), distances.end(), return_min_dist);
    dist = distances[0].first;
    Object = distances[0].second;
    
    if( (dist == 0) || (dist < cam.distance) ){
        RGB = cam.cor;
    }else{
        RGB = Phong(cam, Object, raio, dist);
    }
    
    cout << RGB.x << ' ' << RGB.y << ' ' << RGB.z << '\n';
}

int main(){
    //Coisas acontecerão aqui
    double x, y, z, foo, height, length, distance;
    vector<Sphere> Spheres;
    vector<Plane> Planes;
    vector<Mesh> Meshs;

    int nTriangles;
    int nVertex;
    vector<Point> Vertices;
    Vector color;

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

            double kd, ks, ka, kr, kt, nrugo;
            cin >> kd >> ks >> ka >> kr >> kt >> nrugo;
            
            Sphere sphere = Sphere(center, radius, sp_color, kd, ks, ka, kr, kt, nrugo);
            Spheres.push_back(sphere);
        
        }else if(input == "plane"){

            cin >> x >> y >> z;
            Point plane_origin = Point(x, y, z);

            cin >> x >> y >> z;
            Vector plane_normal = Vector(x, y, z);

            cin >> x >> y >> z;
            Vector plane_cor = Vector(x, y, z);

            double kd, ks, ka, kr, kt, nrugo;
            cin >> kd >> ks >> ka >> kr >> kt >> nrugo;
            
            Plane plane = Plane(plane_origin, plane_normal, plane_cor, kd, ks, ka, kr, kt, nrugo);
            Planes.push_back(plane);
        }
        else if(input == "mesh"){
            cin >> nTriangles;
            cin >> nVertex;
            vector<vector<int>> triplas (nTriangles);

            for(int i = 0; i < nVertex; i++){
                cin >> x >> y >> z;
                Point A = Point(x, y, z);
                Vertices.push_back(A);
            }
            for(int i=0; i<nTriangles; i++){
                cin >> x >> y >> z;
                triplas[i].push_back(x);
                triplas[i].push_back(y);
                triplas[i].push_back(z);
            }
            cin >> x >> y >> z;
            Vector mesh_color = Vector(x, y, z);

            double kd, ks, ka, kr, kt, nrugo;
            cin >> kd >> ks >> ka >> kr >> kt >> nrugo;

            Mesh mesh = Mesh(nTriangles, nVertex, Vertices, triplas, mesh_color, kd, ks, ka, kr, kt, nrugo);
            triplas.clear();
            Vertices.clear();

            Meshs.push_back(mesh);

        }else if(input == "transf"){
            string object, eixo;
            int index;
            bool rotate;
            double ang;

            //ex: sphere 2 (a terceira esfera)
            cin >> object >> index >> rotate;

            Matrix matrix = Matrix();
            if(rotate){
                cin >> eixo >> ang;
                matrix.elements = matrix.initialize(eixo, ang);

            }else{
                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        cin >> matrix.elements[i][j];
                    }
                }
            }

            if(object == "sphere"){
                Point center = matrix.transform_point(Spheres[index].center);
                Spheres[index] = Sphere(center, Spheres[index].radius, Spheres[index].color,
                                Spheres[index].kd, Spheres[index].ks, Spheres[index].ka, 
                                Spheres[index].kr, Spheres[index].kt, Spheres[index].nrugo);

            
            }else if(object == "plane"){
                Point origin = matrix.transform_point(Planes[index].point);
                Vector normal = matrix.transform_vector(Planes[index].normal);
                Planes[index] = Plane(origin, normal, Planes[index].color,
                          Planes[index].kd, Planes[index].ks, Planes[index].ka, 
                          Planes[index].kr, Planes[index].kt, Planes[index].nrugo);

            }else if(object == "mesh"){
                vector<Point> newVertices;
                for (Point vertice : Meshs[index].Vertices) {
                    Point newVertice = matrix.transform_point(vertice);
                    newVertices.push_back(newVertice);
                }
                Meshs[index] = Mesh(Meshs[index].nTriangles, Meshs[index].nVertex, newVertices, Meshs[index].triplas, 
                                    Meshs[index].color, Meshs[index].kd, Meshs[index].ks, Meshs[index].ka, 
                                    Meshs[index].kr, Meshs[index].kt, Meshs[index].nrugo);
                newVertices.clear();
            }
        }
    }

    //Unindo todos os objetos em um vector só usando armazenamento polimórfico
    vector<Object*> Objects;
    for(Sphere& sphere : Spheres){Objects.push_back(&sphere);}
    for(Plane& plane : Planes){Objects.push_back(&plane);}
    for(Mesh& mesh : Meshs){Objects.push_back(&mesh);}

    cout << "P3\n" << length << " " << height << "\n255\n";
    
    for(double y = 0; y < height; y++){
        for(double x = 0; x < length; x++){
            ray raio = ray(cam.origin, sup_esquerdo + (passo_x*x) - (passo_y*y));
            //Aqui ele manda o raio pra renderizar a cor certa na tela
            Render(cam, Objects, raio);
        }
    }

    return 0;
}