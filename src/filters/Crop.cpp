#include "filters/Crop.h"

Crop::Crop(int32_t new_height, int32_t new_width) : new_height_(new_height), new_width_(new_width) {
}

Image Crop::Apply(const Image &image) const {
    Image new_image = Image(std::min(new_height_, image.GetHeight()), std::min(new_width_, image.GetWidth()));
    for (int32_t row = 0; row < new_image.GetHeight(); row++) {
        for (int32_t column = 0; column < new_image.GetWidth(); column++) {
            new_image(row, column) = image(row, column);
        }
    }
    return new_image;
}