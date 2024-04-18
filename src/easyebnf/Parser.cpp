#include "Parser.h"
#include "Definitions.h"

namespace easyebnf
{
    Parser::Parser(const std::string& contents, const KeywordsPtr& keywords)
    : contents_(contents)
    , keywords_(keywords)
    , definitionsDb_ (std::make_shared<Definitions>())
    {}

    ParserResult Parser::parse()
    {
        return ParserResult::Success;
    }
}