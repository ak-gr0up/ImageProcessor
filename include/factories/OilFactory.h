#include "factories/FilterFactory.h"

class OilFactory : public FilterFactory {
public:
    OilFactory() = default;
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    void PrintHelp() override;
};