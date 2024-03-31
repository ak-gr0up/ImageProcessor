#include <iostream>
#include "factories/NegativeFactory.h"
#include "filters/Negative.h"

std::unique_ptr<Filter> NegativeFactory::Create(const std::vector<std::string>& args) {
    if (!args.empty()) {
        throw std::invalid_argument("Negative: filter doesn't take any parameters, but " + std::to_string(args.size()) +
                                    " was provided");
    }
    return std::make_unique<Negative>();
};

void NegativeFactory::PrintHelp() {
    std::cout << "Converts an image to negative. Doesn't take any arguments. Example: -neg";
}