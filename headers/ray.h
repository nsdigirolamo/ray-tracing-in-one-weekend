/**
    Author: Nicholas DiGirolamo
    Created: January 5, 2023
*/

#ifndef RAY_H
#define RAY_H

#include "vector3.h"
#include "point3.h"

typedef struct ray {
    point3 origin;
    vector3 direction;
} ray;

ray Ray (point3 origin, vector3 direction);

vector3 getRayPoint (ray r, double t);

#endif