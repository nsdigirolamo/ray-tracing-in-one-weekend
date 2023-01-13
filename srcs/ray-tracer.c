/**
    Author: Nicholas DiGirolamo
    Created: January 5, 2023
*/

#include "vector3.h"
#include "point3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hit.h"
#include "camera.h"
#include "random_utils.h"
#include "material.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool findClosestSphere (ray r, size_t len, sphere spheres[len], hit *ray_hit) {
    
    bool isHit = false;
    double closest = 100;
    
    for (int i = 0; i < len; i++) {
        if (findSphereHit(spheres[i], r, 0.001, closest, ray_hit)) {
            isHit = true;
            closest = ray_hit->t;
        }
    }

    return isHit;
}

color ray_color (ray r, int depth, size_t len, sphere spheres[len]) {

    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    hit ray_hit;
    
    if (findClosestSphere(r, len, spheres, &ray_hit)) {
        ray scattered;
        color attenuation;
        scatter(r, ray_hit, &attenuation, &scattered);
        
        color c = ray_color(scattered, depth - 1, len, spheres);
        c.x = c.x * attenuation.x;
        c.y = c.y * attenuation.y;
        c.z = c.z * attenuation.z;
        return c;
    }

    vector3 ray_direction_normal = normal(r.direction);
    double t = 0.5 * (ray_direction_normal.y + 1.0);
    color c1 = scale(Color(0.5, 0.7, 1.0), t);
    color c2 = scale(Color(1.0, 1.0, 1.0), 1.0 - t);
    return add(c1, c2);
}

int main () {

    // Image

    const int image_width = 1920;
    const int image_height = 1080;
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // Camera
    
    double aspect_ratio = (double)image_width / image_height;
    double viewport_height = 2.0;
    double focal_length = 1.0;
    point3 origin = Point3(0, 0, 0);

    camera cam = Camera(aspect_ratio, viewport_height, focal_length, origin);

    // Spheres

    material m1 = Material(Color(0.1, 0.2, 0.5), false, 0.0, false, 1.5);
    sphere center = Sphere(Point3(0.0, 0.0, -1.0), 0.5, m1);

    material m2 = Material(Color(0.8, 0.8, 0.0), false, 0.0, false, 0.0);
    sphere ground = Sphere(Point3(0.0, -100.5, -1.0), 100, m2);

    material m3 = Material(Color(0.8, 0.8, 0.8), false, 0.0, true, 1.5);
    sphere left1 = Sphere(Point3(-1.0, 0.0, -1.0), 0.5, m3);
    sphere left2 = Sphere(Point3(-1.0, 0.0, -1.0), -0.4, m3);

    material m4 = Material(Color(0.8, 0.6, 0.2), true, 0.0, false, 0.0);
    sphere right = Sphere(Point3(1.0, 0.0, -1.0), 0.5, m4);


    sphere spheres [] = {ground, center, left1, left2, right};
    size_t spheres_len = 5;

    // Render

    fprintf(stdout, "P3\n%d %d\n255\n", image_width, image_height);

    for (int row = image_height - 1; 0 <= row; row--) {
        fprintf(stderr, "\r%d scanlines remaining...", row);
        for (int col = 0; col < image_width; col++) {
            color pixel_color = Color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                double h_scale = (randDouble(0, 1) + col) / (image_width - 1.0);
                double v_scale = (randDouble(0, 1) + row) / (image_height - 1.0);
                ray r = getCameraRay(cam, h_scale, v_scale);
                pixel_color = add(pixel_color, ray_color(r, max_depth, spheres_len, spheres));
            }
            writeColor(pixel_color, samples_per_pixel);
        }
    }

    fprintf(stderr, "\nComplete.\n");
    return 0;
}