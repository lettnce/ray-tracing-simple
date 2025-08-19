#include <iostream>

int main() {
    
    const int imageWidth = 256;
    const int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i(imageHeight-1); i >= 0; i--) {
        std::cerr << "Scanlines remaining: " << i << '\n';
        for (int j(0); j < imageWidth; j++) {
            auto r = double(j) / (imageWidth-1);
            auto g = double(i) / (imageHeight-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::cerr << "\nDone.\n";
}
