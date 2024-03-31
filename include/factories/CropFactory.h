#include "factories/FilterFactory.h"

class CropFactory : public FilterFactory {
public:
    CropFactory() = default;
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    void PrintHelp() override;
};