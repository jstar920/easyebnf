#pragma once
namespace easyebnf
{
    struct BS
    {
        char left {0};
        char right {0};
        bool operator== (const BS& other) {return left == other.left && right == other.right;}
    };

    struct BS2
    {
        char left1 {0};
        char left2 {0};
        char right1 {0};
        char right2 {0};
        bool operator== (const BS2& other) {return left1 == other.left1 && left2 == other.left2 && right1 == other.right1 && right2 == other.right2;}
    };

    #ifdef EBNF_ALTERNATIVE
        constexpr char DefaultTermination = '.';
        using Optional = BS2;
        constexpr Optional DefaultOptional = {'(', '/', '/', ')'};
        using Repetition = BS2;
        constexpr Repetition DefaultRepetition = {'(', ':', ':', ')'};
    #else
        constexpr char DefaultTermination = ';';
        using Optional = BS;
        constexpr Optional DefaultOptional = {'[', ']'};
        using Repetition = BS;
        constexpr Repetition DefaultRepetition = {'{', '}'};
    #endif

    #define ALIGNED alignas(16)
}