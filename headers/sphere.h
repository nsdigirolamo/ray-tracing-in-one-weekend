/**
    Author: Nicholas DiGirolamo
    Created: January 8, 2023
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "point3.h"
#include "ray.h"
#include "hit.h"
#include "material.h"

struct sphere {
    point3 center;
    double radius;
    material mat;
} typedef sphere;

sphere Sphere (point3 center, double radius, material mat);

bool findSphereHit (sphere s, ray r, double min_t, double max_t, hit *ray_hit);

point3 randPointInUnitSphere ();
point3 randPointOnUnitSphere ();

#endif