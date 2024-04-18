#pragma once

#include "IElement.h"

namespace easyebnf
{
    class Repetition : public IElement
    {
    public:
        Repetition();
        virtual void addElement(const ElementPtr& element) override;
    private:
        ElementPtr element_;
    };
}