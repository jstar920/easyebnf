#include "Repetition.h"

namespace easyebnf
{
    Repetition::Repetition()
    {}

    void Repetition::addElement(const ElementPtr& element)
    {
        if (!element_)
        {
            element_ = element;
        }
    }
}