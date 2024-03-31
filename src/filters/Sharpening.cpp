#include "filters/Sharpening.h"
#include "filters/ApplyMatrix.h"

const std::vector<std::vector<float>> SHARPENING_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

Image Sharpening::Apply(const Image &image) const {
    return ApplyMatrix::Apply(image, SHARPENING_MATRIX);
}