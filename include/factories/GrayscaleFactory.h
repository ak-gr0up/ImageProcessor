#include "factories/FilterFactory.h"

class GrayscaleFactory : public FilterFactory {
public:
    GrayscaleFactory() = default;
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    void PrintHelp() override;
};