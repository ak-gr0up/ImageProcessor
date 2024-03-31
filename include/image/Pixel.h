#pragma once

#include <tuple>
#include <cmath>
#include <stdint.h>
#include <ostream>

class Pixel {
public:
    static const size_t CHANNELS = 3;

private:
    float color_[Pixel::CHANNELS]{};

public:
    Pixel() = default;

    Pixel(uint8_t r, uint8_t g, uint8_t b);

    explicit Pixel(float value);

    Pixel(float r, float g, float b);

    float GetChannel(size_t channel) const;

    std::tuple<uint8_t, uint8_t, uint8_t> RGBValue() const;

    void Normalize();

    Pixel operator+(const Pixel& other) const;

    Pixel operator*(float coeff) const;

    Pixel operator/(float coeff) const;

    Pixel& operator+=(const Pixel& other);

    bool operator>(float value);
};