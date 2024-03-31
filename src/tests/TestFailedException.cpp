#include <string>
#include <exception>
#include "tests/TestFailedException.h"

TestFailedException::TestFailedException(const std::string &message) : message_(message) {
}

const char *TestFailedException::what() const noexcept {
    return message_.c_str();
}
