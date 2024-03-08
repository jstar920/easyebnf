#pragma once
#include "def.h"

namespace easyebnf
{
    enum class MatchType
    {
        MatchNone,
        MatchUnary,
        MatchBinary,
    };

    enum class KeyWordTag
    {
        Definition,
        Concatenation,
        Termination,
        Alternation,
        Grouping,
        TerminateStr1,
        TerminateStr2,
        Special,
        Optional,
        Repetition,
        Comments,
        Exception
    };

    class ALIGNED KeyWord
    {
    public:
        void setKeyWord(KeyWordTag tag, const Notation& notation)
        {
            switch(tag)
            {
                case KeyWordTag::Definition:
                    definition_ = notation;
                    break;
                case KeyWordTag::Concatenation:
                    concatenation_ = notation;
                    break;
                case KeyWordTag::Termination:
                    termination_ = notation;
                    break;
                case KeyWordTag::Alternation:
                    alternation_ = notation;
                    break;
                case KeyWordTag::Exception:
                    exception_ = notation;
                    break;
                default:
                    break;
            }
        }

        void setKeyWord(KeyWordTag tag, const NotationPair& notationPair)
        {
            switch(tag)
            {
                case KeyWordTag::Grouping:
                    grouping_ = notationPair;
                    break;
                case KeyWordTag::TerminateStr1:
                    terminal_string1_ = notationPair;
                    break;
                case KeyWordTag::TerminateStr2:
                    terminal_string2_ = notationPair;
                    break;
                case KeyWordTag::Special:
                    special_sequence_ = notationPair;
                    break;
                case KeyWordTag::Optional:
                    optional_ = notationPair;
                    break;
                case KeyWordTag::Repetition:
                    repetition_ = notationPair;
                    break;
                case KeyWordTag::Comments:
                    comments_ = notationPair;
                    break;
            }
        }

        MatchType matchDefinition(void* p) const { return march(definition_, p); }
        MatchType matchConcatenation(void* p) const { return march(concatenation_, p); }
        MatchType matchTermination(void* p) const { return march(termination_, p); }
        MatchType matchAlternation(void* p) const { return march(alternation_, p); }
        MatchType matchGroupingLeft(void* p) const { return march(grouping_.left, p); };
        MatchType matchGroupingRight(void* p) const { return march(grouping_.left, p); };
        MatchType matchTerminateStrLeft(void* p) const
        {
            const auto ret = march(terminal_string1_.left, p);
            ret == MatchType::MatchNone ? march(terminal_string2_.left, p) : ret;
        }
        MatchType matchTerminateStrRight(void* p) const
        {
            const auto ret = march(terminal_string1_.right, p);
            ret == MatchType::MatchNone ? march(terminal_string2_.right, p) : ret;
        }
        MatchType matchSpecialLeft(void* p) const { return march(special_sequence_.left, p); }
        MatchType matchSpecialRight(void* p) const {return march(special_sequence_.right, p); }
        MatchType matchOptionalLeft(void* p) const { return march(optional_.left, p); }
        MatchType matchOptionalRight(void* p) const {return march(optional_.right, p); }
        MatchType matchRepetitionLeft(void* p) const { return march(repetition_.left, p); }
        MatchType matchRepetitionRight(void* p) const {return march(repetition_.right, p); }
        MatchType matchCommentsLeft(void* p) const { return march(comments_.left, p); }
        MatchType matchCommentsRight(void* p) const {return march(comments_.right, p); }

        MatchType matchException(void* p) const { return march(exception_, p); }
    private:
        MatchType march(const Notation& notation, void* p) const
        {
            char* pCh = reinterpret_cast<char*>(p);
            if (*pCh != '\0' && notation.matchUnary(*pCh))
            {
                return MatchType::MatchUnary;
            }
            else if (*pCh != '\0' && *(pCh + 1) != '\0' && notation.matchBinary(*pCh, *(pCh + 1)))
            {
                return MatchType::MatchBinary;
            }
            return MatchType::MatchNone;
        }

    private:
        Notation definition_ {'='};
        Notation concatenation_ {','};
        Notation termination_ {DefaultTermination};
        Notation alternation_ {'|'};
        NotationPair grouping_ {'(', ')'};
        NotationPair terminal_string1_ {'\"', '\"'};
        NotationPair terminal_string2_ {'\'', '\''};
        NotationPair special_sequence_ {'?', '?'};
        NotationPair optional_ {'[', ']'};
        NotationPair repetition_ {'{', '}'};
        NotationPair comments_ {{'(', '*'}, {'*', ')'}};
        Notation exception_ {'-'};
    };
}