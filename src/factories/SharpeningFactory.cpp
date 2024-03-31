#include <iostream>
#include "factories/SharpeningFactory.h"
#include "filters/Sharpening.h"

std::unique_ptr<Filter> SharpeningFactory::Create(const std::vector<std::string>& args) {
    if (!args.empty()) {
        throw std::invalid_argument("Sharpening: filter doesn't take any parameters, but " +
                                    std::to_string(args.size()) + " was provided");
    }
    return std::make_unique<Sharpening>();
};

void SharpeningFactory::PrintHelp() {
    std::cout << "Image sharpening. Doesn't take any arguments. Example: -sharp";
}