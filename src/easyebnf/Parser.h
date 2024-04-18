#pragma once
#include <string>
#include <memory>
#include <stack>
#include <unordered_map>

namespace easyebnf
{
    using ElementPtr = std::shared_ptr<class IElement>;
    using ElementStack = std::stack<ElementPtr>;
    using KeywordsPtr = std::shared_ptr<class Keywords>;
    using DefinitionPtr = std::shared_ptr<class Definition>;
    using DefinitionsPtr = std::shared_ptr<class Definitions>;

    enum class ParserResult
    {
        Success
    };

    class Parser
    {
    public:
        virtual ParserResult parse();
    protected:
        Parser(const std::string& contents, const KeywordsPtr& keywords);
    protected:
        inline const char* cur() const { return contents_.data() + index_; } ;
        inline const char curCh() const { return *cur(); };
        inline void next() { ++index_; };

        template<typename Size>
        inline void next(Size size) { int count = static_cast<int>(size); while(count > 0) { ++index_, --count; } }
        inline bool end() { return index_ == contents_.size(); };
    protected:
        std::string contents_;
        KeywordsPtr keywords_;
        size_t index_ { 0 };
        DefinitionPtr currentDefinition_;
        DefinitionsPtr definitionsDb_;
        ElementStack elementsStack_;
    };
}
