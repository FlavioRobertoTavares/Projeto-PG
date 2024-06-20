#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"   
#include "vector.h"  

class Light {
    public:
        Point origin;
        Vector intensity; //ILn=light intensity
        Vector ambient_colour; //Ia=ambient colour
        
        Light(const Point& origin, const Vector& intensity, const Vector& ambient_colour)
            : origin(origin), intensity(intensity), ambient_colour(ambient_colour) {}
        
        void print(){
            std::cout << "Light origin: ";
            origin.print();
            std::cout << "Light intensity: ";
            intensity.print();
            std::cout << "Ambient colour: ";
            ambient_colour.print();
        }
};

#endif // LIGHT_H
