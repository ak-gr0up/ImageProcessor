#include "filters/Filter.h"

class Grayscale : public Filter {
public:
    Grayscale() = default;

    Image Apply(const Image &image) const override;
};