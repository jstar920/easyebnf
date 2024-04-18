#include "Optional.h"
namespace easyebnf
{
    Optional::Optional()
    {}

    void Optional::addElement(const ElementPtr& element)
    {
        if (!element_)
        {
            element_ = element;
        }
    }
};