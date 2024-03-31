#include <vector>
#include "image/Image.h"

using std::vector;

class ApplyMatrix {
public:
    static Image Apply(const Image& image, const vector<vector<float>>& matrix);
};