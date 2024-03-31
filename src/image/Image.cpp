#include "image/Image.h"

Image::Image(int32_t height, int32_t width) : height_(height), width_(width) {
    table_.resize(static_cast<size_t>(height_) * width_);
}

const Pixel& Image::operator()(int32_t row, int32_t col) const {
    return table_[static_cast<size_t>(height_) * row + col];
}

Pixel& Image::operator()(int32_t row, int32_t col) {
    return table_[static_cast<size_t>(height_) * row + col];
}

int32_t Image::GetHeight() const {
    return height_;
}

int32_t Image::GetWidth() const {
    return width_;
}