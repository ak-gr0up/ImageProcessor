#include <memory>
#include <iostream>
#include "factories/CropFactory.h"
#include "filters/Crop.h"
#include "utils/Convert.h"

std::unique_ptr<Filter> CropFactory::Create(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        throw std::invalid_argument("Crop: filter takes exactly two parameters -- height and width, but " +
                                    std::to_string(args.size()) + " was provided");
    }
    int32_t new_height = Convert::ReadInteger(args[0], "Crop");
    int32_t new_width = Convert::ReadInteger(args[1], "Crop");

    if (new_height < 0 || new_width < 0) {
        throw std::invalid_argument("Crop: height, width for crop function can't be negative");
    }
    return std::make_unique<Crop>(new_height, new_width);
};

void CropFactory::PrintHelp() {
    std::cout << "Crops image to given size. Takes two integer arguments height and width. "
                 "Example: -crop 300 200";
}