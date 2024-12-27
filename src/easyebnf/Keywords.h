#pragma once
#include "def.h"
#include <cctype>

namespace easyebnf
{
    enum class MatchType
    {
        MatchNone = 0,
        MatchUnary = 1,
        MatchBinary = 2,
        MatchTernary = 3
    };

    enum class KeywordTag
    {
        Definition,
        Concatenation,
        Termination,
        Alternation,
        Grouping,
        TerminalStr1,
        TerminalStr2,
        Special,
        Optional,
        Repetition,
        Comments,
        Exception,
        Escape
    };

    class ALIGNED Keywords
    {
    public:
        void setKeyWord(KeywordTag tag, const Notation& notation)
        {
            switch(tag)
            {
                case KeywordTag::Definition:
                    definition_ = notation;
                    break;
                case KeywordTag::Concatenation:
                    concatenation_ = notation;
                    break;
                case KeywordTag::Termination:
                    termination_ = notation;
                    break;
                case KeywordTag::Alternation:
                    alternation_ = notation;
                    break;
                case KeywordTag::Exception:
                    exception_ = notation;
                    break;
                case KeywordTag::Escape:
                default:
                    break;
            }
        }

        void setKeyWord(KeywordTag tag, const NotationPair& notationPair)
        {
            switch(tag)
            {
                case KeywordTag::Grouping:
                    grouping_ = notationPair;
                    break;
                case KeywordTag::TerminalStr1:
                    terminal_string1_ = notationPair;
                    break;
                case KeywordTag::TerminalStr2:
                    terminal_string2_ = notationPair;
                    break;
                case KeywordTag::Special:
                    special_sequence_ = notationPair;
                    break;
                case KeywordTag::Optional:
                    optional_ = notationPair;
                    break;
                case KeywordTag::Repetition:
                    repetition_ = notationPair;
                    break;
                case KeywordTag::Comments:
                    comments_ = notationPair;
                    break;
                default:
                    break;
            }
        }

        MatchType matchDefinition(const char* p) const { return march(definition_, p); }
        MatchType matchConcatenation(const char* p) const { return march(concatenation_, p); }
        MatchType matchTermination(const char* p) const { return march(termination_, p); }
        MatchType matchAlternation(const char* p) const { return march(alternation_, p); }
        MatchType matchGroupingLeft(const char* p) const { return march(grouping_.left, p); };
        MatchType matchGroupingRight(const char* p) const { return march(grouping_.left, p); };
        MatchType matchTerminalStr1Left(const char* p) const {return march(terminal_string1_.left, p);}
        MatchType matchTerminalStr1Right(const char* p) const {return march(terminal_string1_.right, p);}
        MatchType matchTerminalStr2Left(const char* p) const {return march(terminal_string2_.left, p);}
        MatchType matchTerminalStr2Right(const char* p) const {return march(terminal_string2_.right, p);}
        MatchType matchSpecialLeft(const char* p) const { return march(special_sequence_.left, p); }
        MatchType matchSpecialRight(const char* p) const {return march(special_sequence_.right, p); }
        MatchType matchOptionalLeft(const char* p) const { return march(optional_.left, p); }
        MatchType matchOptionalRight(const char* p) const {return march(optional_.right, p); }
        MatchType matchRepetitionLeft(const char* p) const { return march(repetition_.left, p); }
        MatchType matchRepetitionRight(const char* p) const {return march(repetition_.right, p); }
        MatchType matchCommentsLeft(const char* p) const { return march(comments_.left, p); }
        MatchType matchCommentsRight(const char* p) const {return march(comments_.right, p); }
        MatchType matchException(const char* p) const { return march(exception_, p); }
        MatchType matchEscape(const char* p) const { return march(escape_, p); }

        bool isSpace(const char* p) const { return std::isspace(*p); }
        bool isAlpha(const char* p) const { return std::isalpha(*p); }
        bool isDigit(const char* p) const { return std::isdigit(*p); }
        bool isPunct(const char* p) const { return std::ispunct(*p); }
        bool isIdCh(const char* p) const { return isDigit(p) || isAlpha(p) || *p == '_';}

    private:
        MatchType march(const Notation& notation, const char* p) const
        {
            if (*p != '\0' && notation.matchUnary(*p))
            {
                return MatchType::MatchUnary;
            }
            else if (*p != '\0' && *(p + 1) != '\0' && notation.matchBinary(*p, *(p + 1)))
            {
                return MatchType::MatchBinary;
            }
            else if (*p != '\0' && *(p + 1) != '\0' && *(p + 2) != '\0' && notation.matchTernary(*p, *(p + 1), *(p + 2)))
            {
            }
            return MatchType::MatchNone;
        }

    private:
        Notation definition_ {'='};
        Notation concatenation_ {','};
        Notation termination_ {';'};
        Notation alternation_ {'|'};
        NotationPair grouping_ {'(', ')'};
        NotationPair terminal_string1_ {'\"', '\"'};
        NotationPair terminal_string2_ {'\'', '\''};
        NotationPair special_sequence_ {'?', '?'};
        NotationPair optional_ {'[', ']'};
        NotationPair repetition_ {'{', '}'};
        NotationPair comments_ {{'(', '*'}, {'*', ')'}};
        Notation exception_ {'-'};
        Notation escape_ {'\\'};
    };
}
