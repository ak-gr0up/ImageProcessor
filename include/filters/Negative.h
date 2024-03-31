#include "filters/Filter.h"

class Negative : public Filter {
public:
    Negative() = default;

    Image Apply(const Image &image) const override;
};