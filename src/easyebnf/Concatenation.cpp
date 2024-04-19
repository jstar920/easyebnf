#include "Concatenation.h"
namespace easyebnf
{
    Concatenation::Concatenation()
    {
    }

    void Concatenation::addElement(const ElementPtr& element)
    {
        if (auto otherConcatenation = std::dynamic_pointer_cast<Concatenation>(element))
        {
            elements_.reserve(elements_.size() + otherConcatenation->elements_.size());
            elements_.insert(elements_.end(), otherConcatenation->elements_.begin(), otherConcatenation->elements_.end());
        }
        else
        {
            elements_.push_back(element);
        }
    }
}