/**
    Author: Nicholas DiGirolamo
    Created: January 7, 2023
*/

#include "color.h"

#include <stdio.h>
#include <math.h>

color Color (double r, double g, double b) {
    return Vector3(r, g, b);
}

double clamp (double x, double min, double max) {
    if (x < min) return min;
    if (max < x) return max;
    return x;
}

void writeColor (color c, int samples) {
    // Divide by number of samples and gamma correst
    // gamma = 2 so we raise to the power of 1/gamma or 1/2 so sqrt
    double scale = 1.0 / samples;
    double r = sqrt(c.x * scale);
    double g = sqrt(c.y * scale);
    double b = sqrt(c.z * scale);

    r = 256 * clamp(r, 0.0, 0.999);
    g = 256 * clamp(g, 0.0, 0.999);
    b = 256 * clamp(b, 0.0, 0.999);

    printf("%d %d %d\n", (int)r, (int)g, (int)b);
}