#pragma once
#include <memory>
#include <vector>
namespace easyebnf
{
    using ElementPtr = std::shared_ptr<class IElement>;
    using ElementsVec = std::vector<ElementPtr>;
    using ElementHandlerPtr = std::shared_ptr<class IElementHandler>;

    class IElement
    {
    public:
        virtual ~IElement() {}

        virtual void addElement(const ElementPtr& element) = 0;
        virtual void handleElemet() = 0;

        void setHandler(const ElementHandlerPtr& handler) { handler_ = handler; };
    private:
        ElementHandlerPtr handler_;
    };

}