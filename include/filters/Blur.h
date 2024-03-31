#pragma once

#include "image/Image.h"
#include "filters/Filter.h"
#include <algorithm>

class Blur : public Filter {
private:
    float sigma_;

public:
    explicit Blur(float sigma);

    Image Apply(const Image &image) const override;
};