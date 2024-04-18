#include "EbnfParser.h"
#include "Keywords.h"
#include "Definition.h"
#include "Definitions.h"
#include "TerminalString.h"
#include <string>

namespace easyebnf
{
    EbnfParser::EbnfParser(const std::string& contents, const KeywordsPtr& keywords)
    : Parser(contents, keywords)
    {}

    ParserResult EbnfParser::parse()
    {
        std::string currentString;
        for (; !end(); next())
        {
            MatchType matchType { MatchType::MatchNone };
            while (keywords_->isSpace(cur())) next();
            if (keywords_->isAlpha(cur()))
            {
                currentString.clear();
                parseIdString(currentString);
            }
            else if ((matchType = keywords_->matchDefinition(cur())) != MatchType::MatchNone)
            {
                currentDefinition_ = std::make_shared<Definition>(currentString);
                currentString.clear();
                definitionsDb_->add(currentDefinition_);

            }
            else if ((matchType = keywords_->matchTerminateStrLeft(cur())) != MatchType::MatchNone)
            {
                std::string terminateString;
                parseTerminalString(terminateString, [this](const char* p){return keywords_->matchTerminateStrRight(p);});
                elementsStack_.push(std::make_shared<TerminalString>(terminateString));
            }
            else if ((matchType = keywords_->matchTerminateStr2Left(cur())) != MatchType::MatchNone)
            {
                std::string terminateString;
                parseTerminalString(terminateString, [this](const char* p){return keywords_->matchTerminateStr2Right(p);});
                elementsStack_.push(std::make_shared<TerminalString>(terminateString));
            }

            next(matchType);
        }
        return ParserResult::Success;
    }

    void EbnfParser::parseIdString(std::string& str)
    {
        str.push_back(curCh());
        next();
        while (keywords_->isIdCh(cur()))
        {
            str.push_back(curCh());
            next();
        }
        while(std::isspace(str.back()))
        {
            str.pop_back();
            next();
        }
    }

    void EbnfParser::parseTerminalString(std::string& str, const MarchFunc& march)
    {
        auto matchType = march(cur());
        while(matchType == MatchType::MatchNone)
        {
            auto mt = keywords_->matchEscape(cur());
            if (mt != MatchType::MatchNone)
            {
                next(mt);
            }
            str.push_back(curCh());
            next();
            matchType = march(cur());
        }
        next(matchType);
    }
}