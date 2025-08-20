#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

//function to return instance sphere is hit by ray in terms of a unit vector, elements are taken from sphereintersection in the repo
double hitSphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - std::sqrt(discriminant)) / (2.0*a);
    }
}

color ray_color(const ray& r) {
    auto t = hitSphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    //image

    auto aspectRatio = 16.0/9.0; //ideal ratio, not actual
    int imageWidth = 400;

    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    //camera
    
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
    auto cameraCenter = point3(0,0,0);

    auto viewportU = vec3(viewportWidth, 0, 0);
    auto viewportV = vec3(0, -viewportHeight, 0);

    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    auto viewportUpperLeft = cameraCenter
                           - vec3(0, 0, focalLength) - viewportU/2 - viewportV/2;
    auto pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    //render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j(0); j < imageHeight; j++) {
        std::cerr << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i(0); i < imageWidth; i++) {
            auto pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
