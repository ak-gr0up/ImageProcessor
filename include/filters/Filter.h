#pragma once

#include "image/Image.h"

class Filter {
public:
    virtual Image Apply(const Image& image) const = 0;
    virtual ~Filter() = default;
};