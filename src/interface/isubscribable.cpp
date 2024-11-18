#ifndef __ISUBSCRIBABLE_CPP__
#define __ISUBSCRIBABLE_CPP__

#include <memory>

#include "./input_event.cpp"

namespace minig {
    class ISubscribable {};

    class IKeyboardEventSubscribable : public ISubscribable {
    public:
        virtual void notice_keyboard_event(std::unique_ptr<KeyboardInputEvent> event) = 0;
    };

    class IMouseMoveEventSubscribable : public ISubscribable {
    public:
        virtual void notice_mouse_move_event(std::unique_ptr<MouseMoveInputEvent> event) = 0;
    };
}

#endif