#ifndef OBJECT
#define OBJECT

#include <string>
#include "ray.h"
#include "vector.h"
#include "texture.h"

using namespace std;

class Object {
public:
    Vector color;
    double kd, ks, ka, kr, kt, nrugo, ior;
    bool have_texture;
    string name;
    Texture* texture; 

    Object(Vector color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior, bool have_texture, string name)
        : color(color), kd(kd), ks(ks), ka(ka), kr(kr), kt(kt), nrugo(nrugo), ior(ior), have_texture(have_texture), name(name), texture(nullptr) {
        if (have_texture) {
            texture = new Texture(name);
        }
    }

    virtual ~Object() {
        if (texture) {
            delete texture;
        }
    }

    virtual double intersect(const ray &r) = 0;
    virtual Vector returnNormal(const ray& r, double t) = 0;
};

#endif

