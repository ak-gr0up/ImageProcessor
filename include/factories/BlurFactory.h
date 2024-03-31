#include "factories/FilterFactory.h"

class BlurFactory : public FilterFactory {
public:
    BlurFactory() = default;
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    void PrintHelp() override;
};