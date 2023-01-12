/**
    Author: Nicholas DiGirolamo
    Created: January 5, 2023
*/

#include "vector3.h"
#include "random_utils.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

vector3 Vector3 (double x, double y, double z) {
    vector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

vector3 add (vector3 v1, vector3 v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

vector3 sub (vector3 v1, vector3 v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

vector3 scale (vector3 v, double s) {
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return v;
}

bool equals (vector3 v1, vector3 v2) {
    const double limit = 1e-8;
    return (fabs(v1.x - v2.x) < limit) && (fabs(v1.y - v2.y) < limit) && (fabs(v1.z - v2.z) < limit);
}

bool nearZero (vector3 v) {
    const double limit = 1e-8;
    return (fabs(v.x) < limit) && (fabs(v.y) < limit) && (fabs(v.z) < limit);
}

double mag (vector3 v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double magSquared (vector3 v) {
    double m = mag(v);
    return m * m;
}

vector3 normal (vector3 v) {
    return scale(v, 1.0 / mag(v));
}

double dot (vector3 v1, vector3 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

vector3 cross (vector3 v1, vector3 v2) {
    vector3 c;
    c.x = (v1.y * v2.z) - (v1.z * v2.y);
    c.y = (v1.z * v2.x) - (v1.x * v2.z);
    c.z = (v1.x * v2.y) - (v1.y * v2.x);
    return c;
}

vector3 reflect(vector3 v, vector3 normal) {
    return sub(v, scale(normal, 2 * dot(v, normal)));
}

vector3 randVector (double min, double max) {
    return Vector3(randDouble(min, max), randDouble(min, max), randDouble(min, max));
}