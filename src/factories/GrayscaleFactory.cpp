#include <iostream>
#include "factories/GrayscaleFactory.h"
#include "filters/Grayscale.h"

std::unique_ptr<Filter> GrayscaleFactory::Create(const std::vector<std::string>& args) {
    if (!args.empty()) {
        throw std::invalid_argument("Grayscale: filter doesn't take any parameters, but " +
                                    std::to_string(args.size()) + " was provided");
    }
    return std::make_unique<Grayscale>();
};

void GrayscaleFactory::PrintHelp() {
    std::cout << "Converts image to grayscale. Doesn't take any arguments. Example: -gs";
}