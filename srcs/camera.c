/**
    Author: Nicholas DiGirolamo
    Created: January 10, 2023
*/

#include "camera.h"

#include <math.h>

camera Camera (point3 look_from, point3 look_at, vector3 view_up, double vertical_fov, double aspect_ratio, double aperture, double focus_distance) {
    double theta = vertical_fov * (M_PI / 180.0);
    double h = tan(theta / 2.0);
    camera c;
    c.viewport_height = 2.0 * h;
    c.viewport_width = aspect_ratio * c.viewport_height;

    c.w = normal(sub(look_from, look_at));
    c.u = normal(cross(view_up, c.w));
    c.v = cross(c.w, c.u);

    c.origin = look_from;
    c.horizontal = scale(c.u, c.viewport_width);
    c.horizontal = scale(c.horizontal, focus_distance);
    c.vertical = scale(c.v, c.viewport_height);
    c.vertical = scale(c.vertical, focus_distance);
    
    c.lower_left_corner = sub(c.origin, scale(c.horizontal, 0.5));
    c.lower_left_corner = sub(c.lower_left_corner, scale(c.vertical, 0.5));
    c.lower_left_corner = sub(c.lower_left_corner, scale(c.w, focus_distance));

    c.lens_radius = aperture / 2.0;
    return c;
}

ray getCameraRay (camera c, double h_scale, double v_scale) {
    vector3 rand_direction = scale(randInUnitDisk(), c.lens_radius);
    vector3 offset = add(scale(c.u, rand_direction.x), scale(c.v, rand_direction.y));
    
    ray r;
    r.origin = add(c.origin, offset);
    vector3 direction = add(c.lower_left_corner, scale(c.horizontal, h_scale));
    direction = add(direction, scale(c.vertical, v_scale));
    direction = sub(direction, c.origin);
    direction = sub(direction, offset);
    r.direction = direction;
    return r;
}