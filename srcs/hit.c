/**
    Author: Nicholas DiGirolamo
    Created: January 9, 2023
*/

#include "vector3.h"
#include "hit.h"
#include "material.h"
#include "sphere.h"

#include <stdbool.h>

hit Hit (double t, point3 point, vector3 normal, material mat) {
    hit h;
    h.t = t;
    h.point = point;
    h.normal = normal;
    h.mat = mat;
    return h;
}

void scatter (ray r, hit h, color *attenuation, ray *scattered) {
        if (h.mat.isReflective) {
            vector3 reflected = reflect(normal(r.direction), h.normal);
            reflected = add(reflected, scale(randPointOnUnitSphere(), h.mat.reflectivity));
            *scattered = Ray(h.point, reflected);
            *attenuation = h.mat.albedo;
        } else {
            vector3 scatter_direction = add(h.normal, randPointOnUnitSphere());
            if (nearZero(scatter_direction)) scatter_direction = h.normal;
            *scattered = Ray(h.point, scatter_direction);
            *attenuation = h.mat.albedo;
        }
}