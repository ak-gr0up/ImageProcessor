#include "filters/Negative.h"

Image Negative::Apply(const Image &image) const {
    Image new_image{image.GetHeight(), image.GetWidth()};
    for (int32_t row = 0; row < image.GetHeight(); row++) {
        for (int32_t column = 0; column < image.GetWidth(); column++) {
            Pixel p = image(row, column);
            new_image(row, column) = Pixel(1 - p.GetChannel(0), 1 - p.GetChannel(1), 1 - p.GetChannel(2));
        }
    }

    return new_image;
}