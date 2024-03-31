#include "filters/Blur.h"
#include "filters/ApplyMatrix.h"
#include <math.h>

Blur::Blur(float sigma) : sigma_(sigma) {
}

Image Blur::Apply(const Image &image) const {
    auto gauss = [this](int32_t dx) {
        return static_cast<float>(std::exp(-(static_cast<float>(dx * dx) / (2 * sigma_ * sigma_))) /
                                  (std::sqrt(2 * M_PI) * sigma_));
    };

    int32_t box_range = std::ceil(3 * sigma_);
    int32_t gauss_size = box_range * 2 + 1;
    std::vector<std::vector<float>> horizontal_gauss_matrix(1, std::vector<float>(gauss_size));
    std::vector<std::vector<float>> vertical_gauss_matrix(gauss_size, std::vector<float>(1));
    for (int32_t x = 0; x < gauss_size; x++) {
        float coeff = gauss(x - box_range);
        horizontal_gauss_matrix[0][x] = coeff;
        vertical_gauss_matrix[x][0] = coeff;
    }

    Image horizontal_blur = ApplyMatrix::Apply(image, horizontal_gauss_matrix);
    Image full_blur = ApplyMatrix::Apply(horizontal_blur, vertical_gauss_matrix);

    return full_blur;
}