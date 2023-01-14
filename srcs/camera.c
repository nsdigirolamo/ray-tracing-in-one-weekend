/**
    Author: Nicholas DiGirolamo
    Created: January 10, 2023
*/

#include "camera.h"

#include <math.h>

camera Camera (point3 look_from, point3 look_at, vector3 view_up, double vertical_fov, double aspect_ratio) {
    double theta = vertical_fov * (M_PI / 180.0);
    double h = tan(theta / 2.0);
    camera c;
    c.viewport_height = 2.0 * h;
    c.viewport_width = aspect_ratio * c.viewport_height;

    vector3 w = normal(sub(look_from, look_at));
    vector3 u = normal(cross(view_up, w));
    vector3 v = cross(w, u);

    c.origin = look_from;
    c.horizontal = scale(u, c.viewport_width);
    c.vertical = scale(v, c.viewport_height);
    
    c.lower_left_corner = sub(c.origin, scale(c.horizontal, 0.5));
    c.lower_left_corner = sub(c.lower_left_corner, scale(c.vertical, 0.5));
    c.lower_left_corner = sub(c.lower_left_corner, w);
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