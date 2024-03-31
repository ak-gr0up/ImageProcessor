#include <memory>
#include <iostream>
#include "factories/OilFactory.h"
#include "filters/Oil.h"
#include "utils/Convert.h"

std::unique_ptr<Filter> OilFactory::Create(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        throw std::invalid_argument("Oil Effect: filter takes exactly two parameters -- radius and intensity, but " +
                                    std::to_string(args.size()) + " was provided");
    }
    int32_t radius = Convert::ReadInteger(args[0], "Oil Effect");
    int32_t intensity = Convert::ReadInteger(args[1], "Oil Effect");

    if (radius <= 0) {
        throw std::invalid_argument("Oil Effect: Radius must be positive integer.");
    }
    if (intensity <= 0) {
        throw std::invalid_argument("Oil Effect: Intensity must be positive integer.");
    }

    return std::make_unique<Oil>(radius, intensity);
};

void OilFactory::PrintHelp() {
    std::cout << "Applies oil effect to the image. Takes two positive integer arguments radius and intensity. "
                 "The more the radius the bigger \"oil blocks\" you get."
                 "The more details and objects picture has, the more intensity should be set. "
                 "Example: -oil 5 10";
}