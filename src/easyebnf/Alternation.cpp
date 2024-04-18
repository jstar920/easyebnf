#include "Alternation.h"
namespace easyebnf
{
    Alternation::Alternation()
    {}

    void Alternation::addElement(const ElementPtr& element)
    {
        elements_.push_back(element);
    }
};