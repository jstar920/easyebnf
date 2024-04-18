#pragma once
#include "IElement.h"

namespace easyebnf
{
    class Alternation : public IElement
    {
    public:
        Alternation();
        virtual void addElement(const ElementPtr& element) override;
    private:
        ElementsVec elements_;
    };
}