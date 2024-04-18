#pragma once
#include "IElement.h"

namespace easyebnf
{
    class Optional : public IElement
    {
    public:
        Optional();
        virtual void addElement(const ElementPtr& element) override;
    private:
        ElementPtr element_;
    };
}