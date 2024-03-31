#include <string>
#include <stdint.h>
#include <vector>
#include <cmath>
#include <cassert>
#include "tests/TestFailedException.h"
#include "image/Pixel.h"

using std::string;

const float EPS = 1e-9;

bool operator!=(const Pixel& a, const Pixel& b) {
    for (size_t i = 0; i < Pixel::CHANNELS; i++) {
        if (std::abs(a.GetChannel(i) - b.GetChannel(i)) >= EPS) {
            return true;
        }
    }
    return false;
}

string PixelToString(Pixel p) {
    string result = "(";
    for (size_t i = 0; i < Pixel::CHANNELS; i++) {
        result += std::to_string(p.GetChannel(i));
        if (i + 1 != Pixel::CHANNELS) {
            result += ";";
        }
    }
    result += ")";
    return result;
}

string BoolToString(bool b) {
    return b ? "true" : "false";
}

bool TestMethod(Pixel result, Pixel expected_value, const std::string& operator_name) {
    if (result != expected_value) {
        throw TestFailedException(operator_name + " for Pixel doesn't work correctly. Result: " +
                                  PixelToString(result) + " Expected Value: " + PixelToString(expected_value));
    }
    return true;
}

bool TestMethod(bool result, bool expected_value, const std::string& operator_name) {
    if (result != expected_value) {
        throw TestFailedException(operator_name + " for Pixel doesn't work correctly. Result: " + BoolToString(result) +
                                  " Expected Value: " + BoolToString(expected_value));
    }
    return true;
}

int main() {
    const Pixel not_normal_pixel = Pixel{-1.0f, 2.0f, 0.3f};
    Pixel p = not_normal_pixel;
    p.Normalize();

    const bool result[] = {
        // to aviod linter errors about magic numbers
        TestMethod(Pixel(static_cast<uint8_t>(255), static_cast<uint8_t>(255), static_cast<uint8_t>(255)),
                   Pixel{1.0f, 1.0f, 1.0f}, "uint_8 constructor"),
        TestMethod(Pixel{0.1f, 0.2f, 0.3f} + Pixel{0.1f, 0.1f, 0.1f}, Pixel{0.2f, 0.3f, 0.4f}, "summation operator"),
        TestMethod(Pixel{0.1f, 0.2f, 0.3f} * 2, Pixel{0.2f, 0.4f, 0.6f}, "multiply operator"),
        TestMethod(Pixel{0.1f, 0.2f, 0.3f} / 2, Pixel{0.05f, 0.1f, 0.15f}, "division operator"),

        TestMethod(p, Pixel(0.0f, 1.0f, 0.3f), "Pixel::Normalize"),

        TestMethod(Pixel{0.1f, 0.2f, 0.3f} > 0.29f, true, "operator >"),
        TestMethod(Pixel{0.1f, 0.2f, 0.3f} > 0.3f, false, "operator >")};
    assert(result[0]);
}