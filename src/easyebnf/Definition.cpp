#include "Definition.h"
namespace easyebnf
{
    Definition::Definition(const std::string& name)
    : name_(name)
    {}

    void Definition::addElement(const ElementPtr& element)
    {
        if (!element_)
        {
            element_ = element;
        }
    }

    std::string Definition::name() const
    {
        return name_;
    }
}
