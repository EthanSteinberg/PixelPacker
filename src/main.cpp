#include <iostream>
#include "pixelPak.h"

#include <lodepng.h>
#include <fstream>

int main(int argv, char **argc) {
    std::vector<std::string> files;

    for (int i = 1; i < argv; i++) {
      files.push_back(argc[i]);
    }

    auto result = process(files);

    auto& image = result.first;

    unsigned error = lodepng::encode("pixelPacker.png", image.pixels, image.width, image.height);

    if (error) {
        std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
    }

    std::ofstream outputJson("pixelPacker.json");

    outputJson << result.second;
}
