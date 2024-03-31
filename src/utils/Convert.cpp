#include <stdexcept>
#include "utils/Convert.h"

int32_t Convert::ReadInteger(const std::string &input, const std::string &filter_name) {
    int32_t val = 0;
    try {
        val = static_cast<int32_t>(std::stoll(input));
    } catch (const std::exception &ex) {
        throw std::invalid_argument(filter_name + ": value \"" + input + "\" cannot be converted to integer");
    }
    return val;
}

float Convert::ReadFloat(const std::string &input, const std::string &filter_name) {
    float val = 0;
    try {
        val = static_cast<float>(std::stof(input));
    } catch (const std::exception &ex) {
        throw std::invalid_argument(filter_name + ": value \"" + input +
                                    "\" cannot be converted to floating point number");
    }
    return val;
}