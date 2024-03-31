#include "factories/FilterFactory.h"

class EdgeFactory : public FilterFactory {
public:
    EdgeFactory() = default;
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    void PrintHelp() override;
};