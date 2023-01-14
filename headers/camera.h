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
    vector3 w;
    vector3 u;
    vector3 v;
    point3 origin;
    vector3 horizontal;
    vector3 vertical;
    point3 lower_left_corner;
    double lens_radius;
} typedef camera;

camera Camera (point3 look_from, point3 look_at, vector3 view_up, double vertical_fov, double aspect_ratio, double aperture, double focus_distance);

ray getCameraRay (camera c, double h_scale, double v_scale);

#endif