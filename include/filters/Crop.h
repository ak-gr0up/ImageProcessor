#pragma once

#include <algorithm>
#include "image/Image.h"
#include "filters/Filter.h"

class Crop : public Filter {
private:
    int32_t new_height_;
    int32_t new_width_;

public:
    Crop(int32_t new_height, int32_t new_width);

    Image Apply(const Image &image) const override;
};