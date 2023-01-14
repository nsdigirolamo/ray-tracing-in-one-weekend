/**
    Author: Nicholas DiGirolamo
    Created: January 10, 2023
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"
#include "point3.h"
#include "ray.h"

struct camera {
    double viewport_height;
    double viewport_width;
    double focal_length;
    point3 origin;
    vector3 horizontal;
    vector3 vertical;
    point3 lower_left_corner;
} typedef camera;

camera Camera (double vfov, double aspect_ratio);

ray getCameraRay (camera c, double h_scale, double v_scale);

#endif