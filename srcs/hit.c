/**
    Author: Nicholas DiGirolamo
    Created: January 9, 2023
*/

#include "vector3.h"
#include "hit.h"
#include "material.h"
#include "sphere.h"
#include "random_utils.h"

#include <math.h>
#include <stdbool.h>

void setFaceNormal (hit *h, ray r, vector3 outward_normal) {
    h->front_face = dot(r.direction, outward_normal) < 0;
    h->normal = h->front_face ? outward_normal : scale(outward_normal, -1.0);
}

double reflectance (double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance
    double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    r0 = r0 * r0;
    return r0 + ((1.0 - r0) * pow((1.0 - cosine), 5.0));
}

void scatter (ray r, hit h, color *attenuation, ray *scattered) {
        if (h.mat.isReflective) {
            
            vector3 reflected = reflect(normal(r.direction), h.normal);
            reflected = add(reflected, scale(randPointOnUnitSphere(), h.mat.reflectivity));
            *scattered = Ray(h.point, reflected);
            *attenuation = h.mat.albedo;

        } else if (h.mat.isRefractive) {

            *attenuation = Color(1.0, 1.0, 1.0);
            double refraction_ratio = h.front_face ? (1.0 / h.mat.refractionIndex) : h.mat.refractionIndex;

            vector3 unit_direction = normal(r.direction);
            double cos_theta = fmin(dot(scale(unit_direction, -1.0), h.normal), 1.0);
            double sin_theta = sqrt(1.0 - (cos_theta * cos_theta));

            bool cannot_refract = (refraction_ratio * sin_theta) > 1.0;
            vector3 direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randDouble(0.0, 1.0)) {
                direction = reflect(unit_direction, h.normal);
            } else {
                direction = refract(unit_direction, h.normal, refraction_ratio);
            }

            *scattered = Ray(h.point, direction);

        } else {
            
            vector3 scatter_direction = add(h.normal, randPointOnUnitSphere());
            if (nearZero(scatter_direction)) scatter_direction = h.normal;
            *scattered = Ray(h.point, scatter_direction);
            *attenuation = h.mat.albedo;

        }
}