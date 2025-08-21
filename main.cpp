#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

/* defunct
//function to return instance sphere is hit by ray in terms of a unit vector, elements are taken from sphereintersection in the repo
double hitSphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared(); //updated terms in our original quadratic: b = -2h, solved for h
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;
    
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (h - std::sqrt(discriminant)) / a;
    }
}*/

int main() {
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspectRatio = 16.0/9.0;
    cam.imageWidth = 400;

    cam.render(world);
}
