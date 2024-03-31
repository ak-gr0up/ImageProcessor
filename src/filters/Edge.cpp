#include "filters/Edge.h"
#include "filters/Grayscale.h"
#include "filters/ApplyMatrix.h"

const std::vector<std::vector<float>> EDGE_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

Edge::Edge(float threshold) : threshold_(threshold) {
}

Image Edge::Apply(const Image &image) const {
    Grayscale gs{};
    Image new_image = gs.Apply(image);
    new_image = ApplyMatrix::Apply(new_image, EDGE_MATRIX);

    for (int32_t row = 0; row < new_image.GetHeight(); row++) {
        for (int32_t column = 0; column < new_image.GetWidth(); column++) {
            Pixel &p = new_image(row, column);
            p = (p > threshold_ ? Pixel(1) : Pixel(0));
        }
    }

    return new_image;
}