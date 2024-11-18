#ifndef __ISUBSCRIBABLE_CPP__
#define __ISUBSCRIBABLE_CPP__

#include <memory>

#include "./input_event.cpp"

namespace minig {
    class ISubscribable {};
    
    class IKeyboardEventSubscribable : public ISubscribable {
    public:
        virtual void notice(std::unique_ptr<InputEvent> event) = 0;
    };
}

#endif