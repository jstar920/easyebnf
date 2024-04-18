#pragma once

#include <unordered_map>
#include <memory>

namespace easyebnf
{
    using DefinitionPtr = std::shared_ptr<class Definition>;
    using DefinitionPtrMap = std::unordered_map<std::string, DefinitionPtr>;
    class Definitions
    {
    public:
        void add(const DefinitionPtr& definition);
        DefinitionPtr find(const std::string& definition);
    private:
        DefinitionPtrMap definitions_;
    };

}