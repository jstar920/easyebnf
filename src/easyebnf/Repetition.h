#pragma once

#include "IElement.h"
#include <string>

namespace easyebnf
{
    class Repetition : public IElement
    {
    public:
        Repetition();
        virtual void addElement(const ElementPtr& element) override;
    private:
        std::vector<std::shared_ptr<IElement>> elements_;
    };
}