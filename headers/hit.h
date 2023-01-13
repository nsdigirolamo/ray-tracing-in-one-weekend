/**
    Author: Nicholas DiGirolamo
    Created: January 9, 2023
*/

#ifndef HIT_H
#define HIT_H

#include "vector3.h"
#include "point3.h"
#include "material.h"
#include "ray.h"

#include <stdbool.h>

struct hit {
    double t;
    point3 point;
    vector3 normal;
    material mat;
    bool front_face;
} typedef hit;

void setFaceNormal (hit *h, ray r, vector3 outward_normal);

void scatter (ray r, hit h, color *attenuation, ray *scattered);

#endif