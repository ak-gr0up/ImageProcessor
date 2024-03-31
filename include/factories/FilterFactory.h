#pragma once

#include <memory>
#include <vector>
#include <string>
#include "filters/Filter.h"

class FilterFactory {
public:
    virtual ~FilterFactory() = default;
    virtual std::unique_ptr<Filter> Create(const std::vector<std::string>& args) = 0;
    virtual void PrintHelp() = 0;
};