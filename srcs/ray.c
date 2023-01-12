/**
    Author: Nicholas DiGirolamo
    Created: January 5, 2023
*/

#include "ray.h"

ray Ray (point3 origin, vector3 direction) {
    ray r;
    r.origin = origin;
    r.direction = direction;
    return r;
}

vector3 getRayPoint (ray r, double t) {
    return add(r.origin, scale(r.direction, t)); // P(t) = origin + (t * direction)
};