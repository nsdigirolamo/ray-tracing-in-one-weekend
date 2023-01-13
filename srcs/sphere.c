/**
    Author: Nicholas DiGirolamo
    Created: January 8, 2023
*/

#include "sphere.h"
#include "vector3.h"
#include "hit.h"
#include "material.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

sphere Sphere (point3 center, double radius, material mat) {
    sphere s;
    s.center = center;
    s.radius = radius;
    s.mat = mat;
    return s;
}

bool findSphereHit (sphere s, ray r, double t_min, double t_max, hit *ray_hit) {
    /*
        TODO: Page 19 has a "simplified" implementation of this function but
        it's a bit harder to wrap my brain around and I don't want to put it
        here until I completely understand it. 
        
        Below is basically just turning an expanded version of the sphere
        equation from page 14 into a quadratic formula, which is easier for me 
        to understand.
    */
    double a = dot(r.direction, r.direction);
    point3 oc_sub = sub(r.origin, s.center);
    double b = 2.0 * dot(r.direction, oc_sub);
    double c = dot(oc_sub, oc_sub) - s.radius * s.radius;
    double discriminant = (b * b) - (4.0 * a * c);
    
    // discriminant < 0 then the ray misses the sphere
    // discriminant = 0 then the ray is tangental to the sphere (hits once)
    // discriminant > 0 then the ray passes through the sphere (hits twice)
    if (discriminant < 0) {
        return false;
    }

    double root = (-b - sqrt(discriminant)) / (2.0 * a);
    if (root < t_min || t_max < root) {
        root = (-b + sqrt(discriminant)) / (2.0 * a);
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    ray_hit->t = root;
    ray_hit->point = getRayPoint(r, ray_hit->t);
    ray_hit->mat = s.mat;
    vector3 outward_normal = scale(sub(ray_hit->point, s.center), 1.0 / s.radius);
    setFaceNormal(ray_hit, r, outward_normal);
    return true;
}

point3 randPointInUnitSphere () {
    while (true) {
        point3 p = randVector(-1, 1);
        if (magSquared(p) >= 1) continue;
        return p;
    }
}

point3 randPointOnUnitSphere () {
    return normal(randPointInUnitSphere());
}