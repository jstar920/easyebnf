#pragma once
#include "Parser.h"
#include "def.h"
#include <string>
#include <memory>
#include <stack>
#include <functional>

namespace easyebnf
{
    using ElementPtr = std::shared_ptr<class IElement>;
    using ElementStack = std::stack<ElementPtr>;
    enum class MatchType;
    enum class KeywordTag;
    using MatchFunc = std::function<MatchType(const char*)>;

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
        void parse(const MatchFunc& march);
        void parseElement();
        void parseDefinitionString();
        void parseDefinition();
        void parseTerminalString1();
        void parseTerminalString2();
        void parseConcatenation();
        void parseTermination();
        void parseAlternation();
        void parseComments();
        void parseOptional();
        void parseRepetition();
        void parseGrouping();
        void parseException();
        ElementPtr generateNotationString(KeywordTag tag, const std::string& str) const;
        void parseNotationString(KeywordTag tag, const MatchFunc& march, bool escape);
        void parseBinaryNotationRecursive(const ElementPtr& curElem, const MatchFunc& march);
    };
}
