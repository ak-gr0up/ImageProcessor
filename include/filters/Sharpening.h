#pragma once

#include "image/Image.h"
#include "filters/Filter.h"
#include <algorithm>

class Sharpening : public Filter {
public:
    Sharpening() = default;

    Image Apply(const Image &image) const override;
};