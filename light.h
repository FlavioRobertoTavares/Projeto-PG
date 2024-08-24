#ifndef LIGHT_H
#define LIGHT_H

#include <utility>
#include "point.h"   
#include "vector.h"
#include "ray.h"
#define Not_intersect -1
using namespace std;

bool return_min_dist(const pair<double, Object*> &dist1, const pair<double, Object*> &dist2){
    if(dist1.first == 0){return false;}
    if(dist2.first == 0){return true;}
    return dist1.first < dist2.first;

}

class Light {
    public:
        Point origin;
        Vector intensity;
        Vector largura;
        Vector altura;
        int numPontos;
        bool extense;

        
        Light(const Point& origin, const Vector& intensity, const Vector& largura, const Vector& altura, int numPontos, bool extense)
            : origin(origin), intensity(intensity), largura(largura), altura(altura), numPontos(numPontos), extense(extense) {}
        
        void print(){
            cout << "Light origin: ";
            origin.print();
            cout << "Light intensity: ";
            intensity.print();
        }

        bool no_shadow(Point Colisao, vector<Object*> Objects, Vector L){
            auto raio = ray(Colisao, L);
            vector<pair<double, Object*>> distances;
            double dist;

            for(const auto& object : Objects){
                dist = object->intersect(raio);
                if(dist != Not_intersect){distances.push_back(make_pair(dist, object));}             
            }

            if(distances.empty()){return true;}
            sort(distances.begin(), distances.end(), return_min_dist);
            dist = distances[0].first;

            auto in = (origin - Colisao).dot(L.x, L.y, L.z);

            return  in < dist;
        }
};

#endif // LIGHT_H
