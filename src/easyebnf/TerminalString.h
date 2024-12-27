#pragma once
#include "IElement.h"
#include <string>

namespace easyebnf
{
    class TerminalString : public IElement
    {
    public:
        TerminalString(const std::string& terminalString);
        virtual void addElement(const ElementPtr& element) final {}
        virtual void handleElemet() final {}
    private:
        std::string terminalString_;
    };
}
