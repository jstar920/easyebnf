#pragma once
#include "IElement.h"

namespace easyebnf
{
    class Grouping : public IElement
    {
    public:
        Grouping();
        virtual void addElement(const ElementPtr& element) override;
    private:
        ElementsVec elements_;
    };
}
