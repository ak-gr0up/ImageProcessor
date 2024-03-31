#include <memory>
#include <iostream>
#include "factories/EdgeFactory.h"
#include "filters/Edge.h"
#include "utils/Convert.h"

std::unique_ptr<Filter> EdgeFactory::Create(const std::vector<std::string>& args) {
    if (args.size() != 1) {
        throw std::invalid_argument("Edge: filter takes exactly one parameter -- threshold, but " +
                                    std::to_string(args.size()) + " was provided");
    }
    float threshold = Convert::ReadFloat(args[0], "Edge");
    if (threshold < 0 || threshold > 1) {
        throw std::invalid_argument("Edge: threshold parameter must lie between 0 and 1.");
    }

    return std::make_unique<Edge>(threshold);
};

void EdgeFactory::PrintHelp() {
    std::cout << "Edge detection. Takes one parameter - threshold. "
                 "Example: -edge 0.179";
}