#include <memory>
#include <iostream>
#include "factories/BlurFactory.h"
#include "filters/Blur.h"
#include "utils/Convert.h"

std::unique_ptr<Filter> BlurFactory::Create(const std::vector<std::string>& args) {
    if (args.size() != 1) {
        throw std::invalid_argument("Blur: filter takes exactly one parameter - sigma, but " +
                                    std::to_string(args.size()) + " was provided");
    }
    float sigma = Convert::ReadFloat(args[0], "Blur");
    if (sigma < 0) {
        throw std::invalid_argument("Blur: sigma parameter can't be negative.");
    }

    return std::make_unique<Blur>(sigma);
};

void BlurFactory::PrintHelp() {
    std::cout << "Gaussian blur. Takes one parameter - sigma. "
                 "Example: -blur 0.5";
}