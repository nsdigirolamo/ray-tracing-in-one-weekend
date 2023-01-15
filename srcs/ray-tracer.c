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
    const int samples_per_pixel = 500;
    const int max_depth = 50;
    
    // Camera

    point3 lookfrom = Point3(13, 2, 3);
    point3 lookat = Point3(0, 0, 0);
    vector3 vup = Vector3(0, 1, 0);
    double vfov = 20.0;
    double aspect_ratio = (double)image_width / image_height;
    double dist_to_focus = 10.0;
    double aperture = 0.1;
    
    camera cam = Camera(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus);

    // Spheres

    size_t spheres_len = 900;
    sphere spheres [spheres_len];

    material ground_mat = Material(Color(0.5, 0.5, 0.5), false, 0.0, false, 0.0);
    sphere ground = Sphere(Point3(0.0, -1000, -1.0), 1000, ground_mat);

    material glass = Material(Color(1, 1, 1), false, 0.0, true, 1.5);
    sphere g = Sphere(Point3(0, 1, 0), 1.0, glass);

    material lambertian = Material(Color(0.4, 0.2, 0.1), false, 0.0, false, 0.0);
    sphere l = Sphere(Point3(-4, 1, 0), 1.0, lambertian);

    material metal = Material(Color(0.7, 0.6, 0.5), true, 0.0, false, 0.0);
    sphere m = Sphere(Point3(4, 1, 0), 1.0, metal);

    spheres[0] = ground;
    spheres[1] = g;
    spheres[2] = l;
    spheres[3] = m;

    int x = -15;
    int z = -15;

    for (int i = 4; i < spheres_len; i++) {

        double choose_mat = randDouble(0, 1);
        point3 center = Point3(x, 0.2, z);
        color clr = Color(randDouble(0, 1), randDouble(0, 1), randDouble(0, 1));

        if (15 <= z) {
            z = -15;
            x++;
        }

        z++;

        material m;

        if (choose_mat < 0.5) {
            m = Material(clr, false, 0.0, false, 0.0);
        } else if (choose_mat < 0.75) {
            m = Material(clr, true, randDouble(0, 1), false, 0.0);
        } else {
            m = Material(clr, false, 0.0, true, randDouble(1, 2));
        }

        spheres[i] = Sphere(center, 0.2, m);
    }

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