#include <vector>
#include <algorithm>
#include <cmath>
#include "filters/Oil.h"

Oil::Oil(int32_t radius, int32_t intensity) : radius_(radius), intensity_(intensity) {
}

Image Oil::Apply(const Image &image) const {
    Image new_image = Image(image.GetHeight(), image.GetWidth());
    for (int32_t row = 0; row < image.GetHeight(); row++) {
        for (int32_t column = 0; column < image.GetWidth(); column++) {
            std::vector<Pixel> intensity_sum(intensity_);
            std::vector<int64_t> intensity_count(intensity_);
            for (int32_t i = std::max(0, row - radius_); i <= std::min(image.GetHeight() - 1, row + radius_); i++) {
                for (int32_t j = std::max(0, column - radius_); j <= std::min(image.GetWidth() - 1, column + radius_);
                     j++) {
                    Pixel p = image(i, j);
                    float p_intensity = 0;
                    for (size_t channel = 0; channel < Pixel::CHANNELS; channel++) {
                        p_intensity += p.GetChannel(channel);
                    }
                    p_intensity /= Pixel::CHANNELS;
                    p_intensity *= static_cast<float>(intensity_);
                    int32_t intensity_block = std::floor(p_intensity);
                    intensity_block = std::min(intensity_block, intensity_ - 1);
                    intensity_sum[intensity_block] += p;
                    intensity_count[intensity_block]++;
                }
            }
            int32_t avg_intensity_block = static_cast<int32_t>(
                std::max_element(intensity_count.begin(), intensity_count.end()) - intensity_count.begin());
            Pixel result =
                intensity_sum[avg_intensity_block] / static_cast<float>(intensity_count[avg_intensity_block]);
            result.Normalize();
            new_image(row, column) = result;
        }
    }
    return new_image;
}