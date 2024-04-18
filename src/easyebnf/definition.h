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
        std::string name() const;
    private:
        std::string name_;
        std::shared_ptr<IElement> element_;
    };
}