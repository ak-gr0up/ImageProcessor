#include <exception>
#include <string>

class TestFailedException : public std::exception {
public:
    explicit TestFailedException(const std::string &message);

    const char *what() const noexcept override;

private:
    std::string message_;
};
