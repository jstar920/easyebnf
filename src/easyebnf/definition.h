#pragma once
#include "IElement.h"
#include <string>

namespace easyebnf
{
    class Definition : public IElement
    {
    public:
        Definition(const std::string& name);
        virtual void addElement(const ElementPtr& element) override;
    private:
        std::string name_;
        std::vector<std::shared_ptr<IElement>> elements_;
    };
}