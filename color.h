//color utility function that writes a single pixel's color to output stream
#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //translates [0,1] components into the valid byte range [0, 255]
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    //write out color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
