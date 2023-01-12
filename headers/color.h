/**
    Author: Nicholas DiGirolamo
    Created: January 7, 2023
*/

#ifndef COLOR_H
#define COLOR_H

#include "vector3.h"

typedef vector3 color;

color Color (double r, double g, double b);

double clamp (double x, double min, double max);

void writeColor (color c, int samples);



#endif