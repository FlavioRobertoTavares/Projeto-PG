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
#include "light.h"
using namespace std;


//Organiza a lista do menor pro maior, mas se for 0, ele coloca no final da lista
bool return_min_dist(const pair<double, Object*> &dist1, const pair<double, Object*> &dist2){
    if(dist1.first == 0){return false;}
    if(dist2.first == 0){return true;}
    return dist1.first < dist2.first;
}

Vector Phong(CAM cam, Object* Object, ray raio, double t, vector<Light> Lights){

    double ka, ks, kd, kr, kt, nrugo, espec, difuse;
    Vector ambient_light, Od, normal, ILi, Li, Ri, V, Difusa, Especular, I;
    
    ambient_light = cam.ambient_light;
    
    ka = Object->ka; //Retorna o ka do Phong, só fazer o mesmo para os outros
    ks = Object->ks;
    kd = Object->kd;
    //double kr = Object->kr;
    //double kt = Object->kt;
    nrugo = Object->nrugo;

    Od = Object->color;

    normal = Object->returnNormal(raio, t);
    normal.make_unit_vector();

    for(Light& light: Lights){
        ILi = light.intensity;
        Li = (light.origin - raio.at(t));
        Li.make_unit_vector();
        Ri = ((normal*2)*(Li.dot(normal.x, normal.y, normal.z))- Li);
        Ri.make_unit_vector();

        V = cam.origin - raio.at(t);
        V.make_unit_vector();
        difuse = normal.dot(Li.x, Li.y, Li.z);
        if (difuse > 0) {
            I = I + ILi*Od*kd*difuse;
        }
        espec = Ri.dot(V.x, V.y, V.z);
        if (espec > 0) {
            I = I + ILi*ks*pow(espec, nrugo);
        }
        // Difusa = ILi*Od*kd*(normal.dot(Li.x, Li.y, Li.z));
        // Especular = ILi*ks*pow(Ri.dot(V.x, V.y, V.z), nrugo);

    }

    I = (ambient_light*ka)*Od + I;

    return I;
}


//Vai passar por todas as esferas e planos da lista Spheres e Planes, para então ver qual tem a menor dist entre eles
//E então printa a cor na tela
void Render(const CAM &cam, const vector<Object*> &Objects, const ray &raio, const vector<Light> &Lights){
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
        RGB = Phong(cam, Object, raio, dist, Lights);
    }
    
    cout << RGB.x << ' ' << RGB.y << ' ' << RGB.z << '\n';
}

int main(){
    //Coisas acontecerão aqui
    double x, y, z, foo, height, length, distance;
    vector<Sphere> Spheres;
    vector<Plane> Planes;
    vector<Mesh> Meshs;
    vector<Light> Lights;

    int nTriangles;
    int nVertex;
    vector<Point> Vertices;
    Vector color;
    Vector ambient_light;
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

    cin >> x >> y >> z;
    ambient_light = Vector(x, y, z);

    CAM cam = CAM(origin, target, up, cor, height, length, distance, ambient_light);
    Vector sup_esquerdo = cam.W*(cam.distance) + cam.V - cam.U ;
    Vector passo_x = cam.U*(2/(length-1));
    Vector passo_y = cam.V*(2/(height-1));    

    for(string input = ""; input != "generate"; cin >> input){

        if (input == "light"){

            cin >> x >> y >> z;
            Point light_origin = Point (x, y, z);

            cin >> x >> y >> z;
            Vector light_intensity = Vector (x, y, z);

            // cin >> x >> y >> z;
            // Vector ambient_colour = Vector (x, y, z);

            Light light (light_origin, light_intensity);
            Lights.push_back(light);

        } else if(input == "sphere"){
        
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
            Render(cam, Objects, raio, Lights);
        }
    }

    return 0;
}