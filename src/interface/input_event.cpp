#ifndef __INPUT_EVENT_CPP__
#define __INPUT_EVENT_CPP__

#include "../control/keyboard_event_list.cpp"

namespace minig {
    class InputEvent {
    public:
        virtual int button() = 0;
        
        virtual int action() = 0;
    };
}

#endif