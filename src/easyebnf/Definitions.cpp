#include "Definitions.h"
#include "Definition.h"

namespace easyebnf
{
    void Definitions::add(const DefinitionPtr& definition)
    {
        definitions_[definition->name()] = definition;
    }

    DefinitionPtr Definitions::find(const std::string& definition)
    {
        const auto it = definitions_.find(definition);
        if (it == definitions_.cend())
        {
            return nullptr;
        }

        return it->second;
    }
}