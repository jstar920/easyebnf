#pragma once
#include "IElement.h"
#include <string>

namespace easyebnf
{
    class SpecialSequence : public IElement
    {
    public:
        SpecialSequence(const std::string& specialSequence);
        virtual void addElement(const ElementPtr& element) final {};
    private:
        std::string specialSequence_;
    };
}