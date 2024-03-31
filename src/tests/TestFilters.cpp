#include <vector>
#include <string>
#include <exception>
#include <memory>
#include "filters/Blur.h"
#include "filters/Crop.h"
#include "filters/Edge.h"
#include "filters/Grayscale.h"
#include "filters/Negative.h"
#include "filters/Oil.h"
#include "tests/TestFailedException.h"
#include "image/Image.h"

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::vector;

struct TestGroup {
    vector<shared_ptr<Filter>> filters_pointers_;
    string filter_name_;
};

int main() {
    const Image image = Image(10, 10);
    const vector<TestGroup> test_groups = {
        {{make_shared<Blur>(31.0), make_shared<Blur>(0)}, "Blur"},
        {{make_shared<Crop>(3, 5), make_shared<Crop>(0, 0), make_shared<Crop>(100, 100)}, "Crop"},
        {{make_shared<Edge>(0), make_shared<Edge>(1), make_shared<Edge>(0.5)}, "Edge"},
        {{make_shared<Grayscale>()}, "Grayscale"},
        {{make_shared<Negative>()}, "Negative"},
        {{make_shared<Oil>(5, 10), make_shared<Oil>(1, 1)}, "Oil"}};
    for (auto &test : test_groups) {
        for (auto const &filter_ptr : test.filters_pointers_) {
            try {
                filter_ptr->Apply(image);
            } catch (const std::exception &ex) {
                throw TestFailedException("Exception occured when applying filter " + test.filter_name_ +
                                          " to the image: " + string(ex.what()));
            }
        }
    }
}