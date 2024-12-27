#pragma once
#include "IElement.h"

namespace easyebnf
{
    class Exception : public IElement
    {
    public:
        Exception();
        virtual void addElement(const ElementPtr& element) override;
    private:
        ElementsVec elements_;
    };
}
