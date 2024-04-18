#pragma once
#include <cstdint>
#include <cstring>

namespace easyebnf
{
    enum class NotationType
    {
        Ternary,
        Binary,
        Unary
    };

    struct Notation
    {
        Notation(char first, char second = '\0', char thrid = '\0')
        : tag_(second == '\0' ? static_cast<uint8_t>(NotationType::Unary)
                              : thrid == '\0' ? static_cast<uint8_t>(NotationType::Binary)
                                              : static_cast<uint8_t>(NotationType::Ternary))
        , first_(static_cast<uint8_t>(first))
        , second_(static_cast<uint8_t>(second))
        , third_(static_cast<uint8_t>(thrid))
        {}

        Notation(const Notation& other)
        : tag_(other.tag_)
        , first_(other.first_)
        , second_(other.second_)
        {}

        inline bool isBinary() const
        {
            return tag_ == static_cast<uint8_t>(NotationType::Binary);
        }

        inline bool isUnary() const
        {
            return tag_ == static_cast<uint8_t>(NotationType::Unary);
        }

        inline bool isTernary() const
        {
            return tag_ == static_cast<uint8_t>(NotationType::Ternary);
        }

        template<typename CH>
        inline bool matchUnary(CH ch) const
        {
            isUnary() && static_cast<uint8_t>(ch) == first_;
        }

        template<typename CH>
        inline bool matchBinary(CH ch1, CH ch2) const
        {
            return isBinary() && matchFirst(ch1) && matchSecond(ch2);
        }

        template<typename CH>
        inline bool matchTernary(CH ch1, CH ch2, CH ch3) const
        {
            return isBinary() && matchFirst(ch1) && matchSecond(ch2) && matchThird(ch3);
        }

        bool operator == (const Notation& other) const
        {
            return (std::memcmp(this, &other, 4) == 0);
        }

        Notation& operator = (const Notation& other)
        {
            std::memcpy(this, &other, 4);
            return *this;
        }

    private:
        template<typename CH>
        inline bool matchFirst(CH ch) const
        {
            static_cast<uint8_t>(ch) == first_;
        }

        template<typename CH>
        inline bool matchSecond(CH ch) const
        {
            static_cast<uint8_t>(ch) == second_;
        }

        template<typename CH>
        inline bool matchThird(CH ch) const
        {
            static_cast<uint8_t>(ch) == third_;
        }


    private:
        uint8_t tag_ {0};
        uint8_t first_ {0};
        uint8_t second_ {0};
        uint8_t third_ {0};
    };

    struct NotationPair
    {
        Notation left;
        Notation right;
        NotationPair& operator = (const NotationPair& other)
        {
            left = other.left;
            right = other.right;
            return *this;
        }
    };

    #define ALIGNED alignas(16)
}