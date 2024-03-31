#pragma once

#include "image/Image.h"
#include "filters/Filter.h"
#include <algorithm>

class Edge : public Filter {
private:
    float threshold_;

public:
    explicit Edge(float threshold);

    Image Apply(const Image &image) const override;
};