#include "factories/FilterFactory.h"

class NegativeFactory : public FilterFactory {
public:
    NegativeFactory() = default;
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    void PrintHelp() override;
};