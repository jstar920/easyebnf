#include "EbnfParser.h"
#include "Keywords.h"
#include "Definition.h"
#include "Definitions.h"
#include "TerminalString.h"
#include "Concatenation.h"
#include "Alternation.h"
#include <string>

namespace easyebnf
{
    EbnfParser::EbnfParser(const std::string& contents, const KeywordsPtr& keywords)
    : Parser(contents, keywords)
    {}

    ParserResult EbnfParser::parse()
    {
        for (; !end(); next())
        {
            MatchType matchType { MatchType::MatchNone };
            while (keywords_->isSpace(cur())) next();

            if (keywords_->isAlpha(cur()))
            {
                parseDefinitionString();
            }
            else if ((matchType = keywords_->matchDefinition(cur())) != MatchType::MatchNone)
            {
                parseDefinition();
            }
            else if ((matchType = keywords_->matchTerminateStrLeft(cur())) != MatchType::MatchNone)
            {
                parseTerminalString([this](const char* p){return keywords_->matchTerminateStrRight(p);});
            }
            else if ((matchType = keywords_->matchTerminateStr2Left(cur())) != MatchType::MatchNone)
            {
                parseTerminalString([this](const char* p){return keywords_->matchTerminateStr2Right(p);});
            }
            else if ((matchType = keywords_->matchConcatenation(cur())) != MatchType::MatchNone)
            {
                parseConcatenation();
            }
            else if ((matchType = keywords_->matchTermination(cur())) != MatchType::MatchNone)
            {
                parseTermination();
            }
            else if ((matchType = keywords_->matchAlternation(cur())) != MatchType::MatchNone)
            {
                parseAlternation();
            }
            else if ((matchType = keywords_->matchOptionalLeft(cur())) != MatchType::MatchNone)
            {
                parseAlternation();
            }

            next(matchType);
        }
        return ParserResult::Success;
    }

    void EbnfParser::parseDefinitionString()
    {
        std::string str;
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

        auto definition = definitionsDb_->find(str);

        if (!definition)
        {
            definition = std::make_shared<Definition>(str);
            elementsStack_.push(definition);
        }
        else
        {
            if (!elementsStack_.empty())
            {
                auto element = elementsStack_.top();
                element->addElement(definition);
            }
        }
    }

    void EbnfParser::parseDefinition()
    {
        if (elementsStack_.empty())
        {
            // should be crash it.
            //TBD;
        }
        currentDefinition_ = std::dynamic_pointer_cast<Definition>(elementsStack_.top());
        elementsStack_.pop();
        if (!currentDefinition_)
        {
            // should be crash it.
            //TBD;
        }

        if (auto definition = definitionsDb_->find(currentDefinition_->name()))
        {
            // should be crash it.
            //TBD;
        }
        definitionsDb_->add(currentDefinition_);
    }

    void EbnfParser::parseTerminalString(const MarchFunc& march)
    {
        std::string terminateString;
        auto matchType = march(cur());
        while(matchType == MatchType::MatchNone)
        {
            auto mt = keywords_->matchEscape(cur());
            if (mt != MatchType::MatchNone)
            {
                next(mt);
            }
            terminateString.push_back(curCh());
            next();
            matchType = march(cur());
        }
        next(matchType);
        elementsStack_.push(std::make_shared<TerminalString>(terminateString));
    }

    void EbnfParser::parseConcatenation()
    {
        auto concatenation = std::make_shared<Concatenation>();
        if (elementsStack_.empty())
        {
            // should be crash it.
            //TBD;
        }
        concatenation->addElement(elementsStack_.top());
        elementsStack_.pop();
        elementsStack_.push(concatenation);
    }

    void EbnfParser::parseTermination()
    {
        if (elementsStack_.empty() || !currentDefinition_)
        {
            // should be crash it.
            //TBD;
        }
        currentDefinition_->addElement(elementsStack_.top());
        elementsStack_.pop();
        if (!elementsStack_.empty())
        {
            // should be crash it.
            //TBD;
        }
        currentDefinition_.reset();
    }

    void EbnfParser::parseAlternation()
    {
        auto alternation = std::make_shared<Alternation>();
        if (elementsStack_.empty())
        {
            // should be crash it.
            //TBD;
        }
        alternation->addElement(elementsStack_.top());
        elementsStack_.pop();
        elementsStack_.push(alternation);
    }
}