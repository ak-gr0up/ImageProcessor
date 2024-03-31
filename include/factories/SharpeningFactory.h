#include "factories/FilterFactory.h"

class SharpeningFactory : public FilterFactory {
public:
    SharpeningFactory() = default;
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    void PrintHelp() override;
};