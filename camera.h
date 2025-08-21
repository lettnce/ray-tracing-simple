#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"

class camera {
    public:
        double aspectRatio = 1.0;
        int imageWidth = 100;

        void render (const hittable& world) {
            initialize();
            
            std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

            for (int j(0); j < imageHeight; j++) {
                std::cerr << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
                for (int i(0); i < imageWidth; i++) {
                    auto pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
                    auto rayDirection = pixelCenter - cameraCenter;
                    ray r(cameraCenter, rayDirection);

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }

            std::cerr << "\nDone.\n";
        }

    private:
        int imageHeight;
        point3 cameraCenter;
        point3 pixel00Location;
        vec3 pixelDeltaU;
        vec3 pixelDeltaV;

        void initialize() {
            imageHeight = int(imageWidth / aspectRatio);
            imageHeight = (imageHeight < 1) ? 1 : imageHeight;

            cameraCenter = point3(0, 0, 0);
    
            auto focalLength = 1.0;
            auto viewportHeight = 2.0;
            auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);

            auto viewportU = vec3(viewportWidth, 0, 0);
            auto viewportV = vec3(0, -viewportHeight, 0);

            auto pixelDeltaU = viewportU / imageWidth;
            auto pixelDeltaV = viewportV / imageHeight;

            auto viewportUpperLeft = cameraCenter
                                   - vec3(0, 0, focalLength) - viewportU/2 - viewportV/2;
            auto pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
        }

        color ray_color(const ray& r, const hittable& world) const {
            hit_record rec;
    
            if (world.hit(r, interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + color(1, 1, 1));
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};

#endif
