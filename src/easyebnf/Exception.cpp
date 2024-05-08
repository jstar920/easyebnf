#include "Exception.h"
namespace easyebnf
{
    Exception::Exception()
    {
    }

    void Exception::addElement(const ElementPtr& element)
    {
        elements_.push_back(element);
    }
}