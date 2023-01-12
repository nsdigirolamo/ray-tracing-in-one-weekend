/**
    Author: Nicholas DiGirolamo
    Created: January 11, 2023
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

#include <stdbool.h>

struct material {
    color albedo;
    bool isReflective;
    double reflectivity;
} typedef material;

material Material (color albedo, bool isReflective, double reflectivity);

#endif