#include <algorithm>
#include "filters/ApplyMatrix.h"

Image ApplyMatrix::Apply(const Image& image, const vector<vector<float>>& matrix) {
    int32_t n = static_cast<int32_t>(matrix.size());
    int32_t m = static_cast<int32_t>(matrix.at(0).size());
    int32_t mid_row = n / 2;
    int32_t mid_column = m / 2;

    auto get_pixel = [&image](int32_t row, int32_t column) {
        row = std::clamp(row, 0, image.GetHeight() - 1);
        column = std::clamp(column, 0, image.GetWidth() - 1);
        return image(row, column);
    };

    Image new_image = Image(image.GetHeight(), image.GetWidth());
    for (int32_t row = 0; row < new_image.GetHeight(); row++) {
        for (int32_t column = 0; column < new_image.GetWidth(); column++) {
            Pixel p{0};
            for (int32_t i = 0; i < n; i++) {
                for (int32_t j = 0; j < m; j++) {
                    p += get_pixel(row + i - mid_row, column + j - mid_column) * matrix[i][j];
                }
            }
            p.Normalize();
            new_image(row, column) = p;
        }
    }
    return new_image;
}