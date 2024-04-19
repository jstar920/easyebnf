#pragma once
#include "Parser.h"
#include <string>
#include <memory>
#include <stack>
#include <functional>

namespace easyebnf
{
    using ElementPtr = std::shared_ptr<class IElement>;
    using ElementStack = std::stack<ElementPtr>;
    enum class MatchType;
    using MarchFunc = std::function<MatchType(const char*)>;

    enum class ParserResult
    {
        Success
    };

    class EbnfParser : public Parser
    {
    public:
        EbnfParser(const std::string& contents, const KeywordsPtr& keywords);
    private:
        virtual ParserResult parse();
    private:
        void parseDefinitionString();
        void parseDefinition();
        void parseTerminalString(const MarchFunc& march);
        void parseConcatenation();
        void parseTermination();
        void parseAlternation();
    };
}
