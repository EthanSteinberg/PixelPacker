#include <iostream>
#include "pixelPak.h"

#include <lodepng.h>
#include <fstream>

int main(int argv, char **argc) {
    std::vector<std::string> files;

    bool premultipy_alpha = false;

    for (int i = 1; i < argv; i++) {
        if (argc[i] == std::string("-premultipy")) {
            premultipy_alpha = true;
        } else {
           files.push_back(argc[i]);
        }
    }

    auto result = process(files);

    auto& image = result.first;

    if (premultipy_alpha) {
        for (unsigned int x = 0; x < image.width; x++) {
           for (unsigned int y = 0; y < image.height; y++) {
                for (int c = 0; c < 3; c++) {
                    image.pixels[y * image.width * 4 + x * 4 + c] *= image.pixels[y * image.width * 4 + x * 4 + 3]/255.0;
                }
            }
        }
    }

    unsigned error = lodepng::encode("pixelPacker.png", image.pixels, image.width, image.height);

    if (error) {
        std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
    }

    std::ofstream outputJson("pixelPacker.json");

    outputJson << result.second;
}
