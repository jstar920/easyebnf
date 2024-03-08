#include "Definition.h"
namespace easyebnf
{
    Definition::Definition(const std::string& name)
    : name_(name)
    {}

    void Definition::addElement(const ElementPtr& element)
    {
        elements_.push_back(element);
    }
}