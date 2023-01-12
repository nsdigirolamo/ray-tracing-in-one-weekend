/**
    Author: Nicholas DiGirolamo
    Created: January 10, 2023
*/

#include "camera.h"

camera Camera (double aspect_ratio, double viewport_height, double focal_length, point3 origin) {
    camera c;
    c.aspect_ratio = aspect_ratio;
    c.viewport_height = viewport_height;
    c.viewport_width = aspect_ratio * viewport_height;
    c.focal_length = focal_length;
    c.origin = origin;
    c.horizontal = Vector3(c.viewport_width, 0, 0);
    c.vertical = Vector3(0, c.viewport_height, 0);
    point3 lower_left_corner = sub(origin, scale(c.horizontal, 0.5));
    lower_left_corner = sub(lower_left_corner, scale(c.vertical, 0.5));
    lower_left_corner = sub(lower_left_corner, Vector3(0, 0, c.focal_length));
    c.lower_left_corner = lower_left_corner;
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