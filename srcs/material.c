/**
    Author: Nicholas DiGirolamo
    Created: January 11, 2023
*/

#include "material.h"
#include "color.h"

#include <stdbool.h>

material Material (color albedo, bool isReflective, double reflectivity) {
    material m;
    m.albedo = albedo;
    m.isReflective = isReflective;
    m.reflectivity = reflectivity;
    return m;
}