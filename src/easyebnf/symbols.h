#pragma once
#include "definition.h"

namespace easyebnf
{
    class ALIGNED Symbols
    {
    public:
        void setAlternation(char c) {alternation_ = c;}
        bool isDefinition(char* p) {return *p == definition_;}
        bool isConcatenation(char* p) {return *p == concatenation_;}
        bool isTermination(char* p) {return *p == termination_;}
        bool isAlternation(char* p) {return *p == alternation_;}
        bool isOptional(char* p) {return (*reinterpret_cast<Optional*>(p)) == optional_;}
        bool isRepetition(char* p) {return (*reinterpret_cast<Repetition*>(p)) == repetition_;}
        bool isGrouping(char* p) {return (*reinterpret_cast<BS*>(p)) == grouping_;}
        bool isTerminalString(char* p) {return (*reinterpret_cast<BS*>(p)) == terminal_string_ || (*reinterpret_cast<BS*>(p)) == terminal_string2_;}
        bool isComments(char* p) {return (*reinterpret_cast<BS2*>(p)) == comments_;}
        bool isSpecialSequence_(char* p) {return (*reinterpret_cast<BS*>(p)) == special_sequence_;}
        bool isException(char* p) {return *p == exception_;}
    private:
        char definition_ {'='};
        char concatenation_ {','};
        char termination_ {DefaultTermination};
        char alternation_ {'|'};
        BS grouping_ {'(', ')'};
        BS terminal_string_ {'\"', '\"'};
        BS terminal_string2_ {'\'', '\''};
        BS special_sequence_ {'?', '?'};
        Optional optional_ {DefaultOptional};
        Repetition repetition_ {DefaultRepetition};
        BS2 comments_ {'(', '*', '*', ')'};
        char exception_ {'-'};
    };
}