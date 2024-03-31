#pragma once

#include <vector>
#include <fstream>
#include "image/Pixel.h"

class Image {
private:
    std::vector<Pixel> table_;
    int32_t height_, width_;

public:
    Image() = default;
    Image(int32_t height, int32_t width);

    Pixel& operator()(int32_t row, int32_t col);
    const Pixel& operator()(int32_t row, int32_t col) const;
    int32_t GetHeight() const;
    int32_t GetWidth() const;
};