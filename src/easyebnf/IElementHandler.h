#pragma once

namespace easyebnf
{
    class IElementHandler
    {
    public:
        virtual void impl() = 0;
    };
}