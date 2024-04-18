#include "Grouping.h"
namespace easyebnf
{
    Grouping::Grouping()
    {
    }

    void Grouping::addElement(const ElementPtr& element)
    {
        elements_.push_back(element);
    }
}