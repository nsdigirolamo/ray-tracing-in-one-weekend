/**
    Author: Nicholas DiGirolamo
    Created: January 10, 2023
*/

#include "camera.h"

#include <math.h>

camera Camera (double vfov, double aspect_ratio) {
    double theta = vfov * (M_PI / 180.0);
    double h = tan(theta / 2.0);
    camera c;
    c.viewport_height = 2.0 * h;
    c.viewport_width = aspect_ratio * c.viewport_height;
    c.focal_length = 1.0;
    c.origin = Point3(0.0, 0.0, 0.0);
    c.horizontal = Vector3(c.viewport_width, 0.0, 0.0);
    c.vertical = Vector3(0.0, c.viewport_height, 0.0);
    c.lower_left_corner = sub(c.origin, scale(c.horizontal, 0.5));
    c.lower_left_corner = sub(c.lower_left_corner, scale(c.vertical, 0.5));
    c.lower_left_corner = sub(c.lower_left_corner, Vector3(0.0, 0.0, c.focal_length));
    return c;
}

ray getCameraRay (camera c, double h_scale, double v_scale) {
    vector3 direction = add(c.lower_left_corner, scale(c.horizontal, h_scale));
    direction = add(direction, scale(c.vertical, v_scale));
    direction = sub(direction, c.origin);
    ray r;
    r.origin = c.origin;
    r.direction = direction;
    return r;
}