/**
    Author: Nicholas DiGirolamo
    Created: January 5, 2023
*/

#ifndef VECTOR3_H
#define VECTOR3_H

#include <stdbool.h>

typedef struct vector3 {
    double x;
    double y;
    double z;
} vector3;

vector3 Vector3 (double x, double y, double z);

vector3 add (vector3 v1, vector3 v2);
vector3 sub (vector3 v1, vector3 v2);
vector3 scale (vector3 v, double s);
bool equals (vector3 v1, vector3 v2);
bool nearZero (vector3 v);

double mag (vector3 v);
double magSquared (vector3 v);
vector3 normal (vector3 v);
double dot (vector3 v1, vector3 v2);
vector3 cross (vector3 v1, vector3 v2);
vector3 reflect (vector3 v, vector3 normal);
vector3 refract (vector3 v, vector3 normal, double refraction_index);

vector3 randVector (double min, double max);

#endif