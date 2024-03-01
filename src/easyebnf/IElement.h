#pragma once
#include <memory>
#include <vector>
namespace easyebnf
{
    using ElementPtr = std::shared_ptr<class IElement>;
    using ElementsVec = std::vector<ElementPtr>;

    class IElement
    {
    public:
        virtual ~IElement() {}

        virtual void addElement(const ElementPtr& element) = 0;
    };

}