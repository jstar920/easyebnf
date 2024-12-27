#pragma once
#include "IElement.h"

namespace easyebnf
{
    class Concatenation : public IElement
    {
    public:
        Concatenation();
        virtual void addElement(const ElementPtr& element) override;
    private:
        ElementsVec elements_;
    };
}
