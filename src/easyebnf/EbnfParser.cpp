#include "EbnfParser.h"
#include "Keywords.h"
#include "Definition.h"
#include "Definitions.h"
#include "TerminalString.h"
#include "Concatenation.h"
#include "Alternation.h"
#include "Optional.h"
#include "Repetition.h"
#include "Grouping.h"
#include "Comments.h"
#include "Exception.h"
#include <string>

namespace easyebnf
{
    EbnfParser::EbnfParser(const std::string& contents, const KeywordsPtr& keywords)
    : Parser(contents, keywords)
    {}

    ParserResult EbnfParser::parse()
    {
        parse(nullptr);
        return ParserResult::Success;
    }

    void EbnfParser::parse(const MatchFunc& match)
    {
        for (; !end(); next())
        {
            MatchType matchType { MatchType::MatchNone };
            if (match)
            {
                matchType = match(cur());
                if (matchType != MatchType::MatchNone)
                {
                    next(matchType);
                    return;
                }
            }

            parseElement();
        }
    }

    void EbnfParser::parseElement()
    {
            while (keywords_->isSpace(cur())) next();

            MatchType matchType { MatchType::MatchNone };

            if (keywords_->isAlpha(cur()))
            {
                parseDefinitionString();
            }
            else if ((matchType = keywords_->matchDefinition(cur())) != MatchType::MatchNone)
            {
                parseDefinition();
            }
            else if ((matchType = keywords_->matchTerminalStr1Left(cur())) != MatchType::MatchNone)
            {
                parseTerminalString1();
            }
            else if ((matchType = keywords_->matchTerminalStr2Left(cur())) != MatchType::MatchNone)
            {
                parseTerminalString2();
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
            else if ((matchType = keywords_->matchRepetitionLeft(cur())) != MatchType::MatchNone)
            {
                parseAlternation();
            }
            else if ((matchType = keywords_->matchGroupingLeft(cur())) != MatchType::MatchNone)
            {
                parseAlternation();
            }
            else if ((matchType = keywords_->matchCommentsLeft(cur())) != MatchType::MatchNone)
            {
                parseComments();
            }
            else if ((matchType = keywords_->matchException(cur())) != MatchType::MatchNone)
            {
                parseException();
            }

            next(matchType);
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

    void EbnfParser::parseTerminalString1()
    {
        parseNotationString(KeywordTag::TerminalStr1, [this](const char* p){return keywords_->matchTerminalStr1Right(p);}, true);
    }

    void EbnfParser::parseTerminalString2()
    {
        parseNotationString(KeywordTag::TerminalStr2, [this](const char* p){return keywords_->matchTerminalStr2Right(p);}, true);
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

    void EbnfParser::parseComments()
    {
        parseNotationString(KeywordTag::Comments, [this](const char* p){return keywords_->matchCommentsRight(p);}, false);
    }

    void EbnfParser::parseOptional()
    {
        parseBinaryNotationRecursive(std::make_shared<Optional>(), [this](const char* p){return keywords_->matchOptionalRight(p);});
    }

    void EbnfParser::parseRepetition()
    {
        parseBinaryNotationRecursive(std::make_shared<Repetition>(), [this](const char* p){return keywords_->matchRepetitionRight(p);});
    }

    void EbnfParser::parseGrouping()
    {
        parseBinaryNotationRecursive(std::make_shared<Grouping>(), [this](const char* p){return keywords_->matchGroupingRight(p);});
    }

    void EbnfParser::parseException()
    {
        auto excpetion = std::make_shared<Exception>();
        parseElement();
        if (elementsStack_.empty())
        {
            // should be crash it.
            //TBD;
        }
        excpetion->addElement(elementsStack_.top());
        elementsStack_.pop();
        elementsStack_.push(excpetion);
    }

    ElementPtr EbnfParser::generateNotationString(KeywordTag tag, const std::string& str) const
    {
        switch(tag)
        {
            case KeywordTag::Definition:
                return std::make_shared<Definition>(str);
            case KeywordTag::Comments:
                return std::make_shared<Comments>(str);
            case KeywordTag::TerminalStr1:
            case KeywordTag::TerminalStr2:
                return std::make_shared<TerminalString>(str);
            default:
                return nullptr;
        }
    }

    void EbnfParser::parseNotationString(KeywordTag tag, const MatchFunc& march, bool escape)
    {
        std::string str;
        auto matchType = march(cur());
        while(matchType == MatchType::MatchNone)
        {
            if (escape)
            {
                auto mt = keywords_->matchEscape(cur());
                if (mt != MatchType::MatchNone)
                {
                    next(mt);
                }
            }
            str.push_back(curCh());
            next();
            matchType = march(cur());
        }
        next(matchType);
        elementsStack_.push(generateNotationString(tag, str));
    }

    void EbnfParser::parseBinaryNotationRecursive(const ElementPtr& curElem, const MatchFunc& march)
    {
        elementsStack_.push(curElem);
        parse(march);
        auto tempElem = elementsStack_.top();
        elementsStack_.pop();
        if (elementsStack_.empty())
        {
            // should be crash it.
            //TBD;
        }
        elementsStack_.top()->addElement(tempElem);
    }
}