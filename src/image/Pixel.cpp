#include <algorithm>
#include "image/Pixel.h"

const int32_t CHANNEL_RANGE = 255;

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b) {
    color_[0] = static_cast<float>(r) / CHANNEL_RANGE;
    color_[1] = static_cast<float>(g) / CHANNEL_RANGE;
    color_[2] = static_cast<float>(b) / CHANNEL_RANGE;
}

Pixel::Pixel(float value) {
    for (size_t i = 0; i < CHANNELS; i++) {
        color_[i] = value;
    }
}

Pixel::Pixel(float r, float g, float b) {
    color_[0] = r;
    color_[1] = g;
    color_[2] = b;
}

float Pixel::GetChannel(size_t channel) const {
    return color_[channel];
}

std::tuple<uint8_t, uint8_t, uint8_t> Pixel::RGBValue() const {
    return std::make_tuple(std::round(color_[0] * CHANNEL_RANGE), std::round(color_[1] * CHANNEL_RANGE),
                           std::round(color_[2] * CHANNEL_RANGE));
}

Pixel Pixel::operator*(float coeff) const {
    Pixel result = *this;
    for (size_t i = 0; i < CHANNELS; i++) {
        result.color_[i] = result.color_[i] * coeff;
    }
    return result;
}

Pixel Pixel::operator/(float coeff) const {
    return (*this) * (1.f / coeff);
}

Pixel& Pixel::operator+=(const Pixel& other) {
    for (size_t i = 0; i < CHANNELS; i++) {
        color_[i] += other.color_[i];
    }
    return *this;
}

Pixel Pixel::operator+(const Pixel& other) const {
    Pixel result = *this;
    result += other;
    return result;
}

void Pixel::Normalize() {
    for (size_t i = 0; i < CHANNELS; i++) {
        color_[i] = std::clamp(color_[i], 0.f, 1.f);
    }
}

bool Pixel::operator>(float value) {
    for (size_t i = 0; i < CHANNELS; i++) {
        if (color_[i] > value) {
            return true;
        }
    }
    return false;
}