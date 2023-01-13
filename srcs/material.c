/**
    Author: Nicholas DiGirolamo
    Created: January 11, 2023
*/

#include "material.h"
#include "color.h"

#include <stdbool.h>

material Material (color albedo, bool isReflective, double reflectivity, bool isRefractive, double refractionIndex) {
    material m;
    m.albedo = albedo;
    m.isReflective = isReflective;
    m.reflectivity = reflectivity;
    m.isRefractive = isRefractive;
    m.refractionIndex = refractionIndex;
    return m;
}