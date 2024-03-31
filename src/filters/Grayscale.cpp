#include "filters/Grayscale.h"

const float RED_COEFF = 0.299;
const float GREEN_COEFF = 0.587;
const float BLUE_COEFF = 0.114;

Image Grayscale::Apply(const Image &image) const {
    Image new_image{image.GetHeight(), image.GetWidth()};
    for (int32_t row = 0; row < image.GetHeight(); row++) {
        for (int32_t column = 0; column < image.GetWidth(); column++) {
            Pixel p = image(row, column);
            float channel_value =
                p.GetChannel(0) * RED_COEFF + p.GetChannel(1) * GREEN_COEFF + p.GetChannel(2) * BLUE_COEFF;
            Pixel result = Pixel(channel_value);
            result.Normalize();
            new_image(row, column) = result;
        }
    }

    return new_image;
}