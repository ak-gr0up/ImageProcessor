#pragma once

#include <algorithm>
#include "image/Image.h"
#include "filters/Filter.h"

class Oil : public Filter {
private:
    int32_t radius_;
    int32_t intensity_;

public:
    Oil(int32_t radius, int32_t intensity);

    Image Apply(const Image &image) const override;
};