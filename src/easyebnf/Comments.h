#pragma once
#pragma once
#include "IElement.h"
#include <string>

namespace easyebnf
{
    class Comments : public IElement
    {
    public:
        Comments(const std::string& comments);
        virtual void addElement(const ElementPtr& element) final {}
    private:
        std::string comments_;
    };
}
