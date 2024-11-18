#ifndef __INPUT_EVENT_CPP__
#define __INPUT_EVENT_CPP__

namespace minig {
    class InputEvent {};

    /*
    */
    class KeyboardInputEvent : public InputEvent {
    public:
        virtual int button() = 0;
        virtual int action() = 0;
        // virtual int modifier() = 0;
        // virtual int scancode() = 0;
    };

    class MouseMoveInputEvent : public InputEvent {
        double position_x_;
        double position_y_;

    public:
        MouseMoveInputEvent(
            double position_x,
            double position_y
        ): position_x_(position_x), position_y_(position_y) {}

        double position_x() { return position_x_; }

        double position_y() { return position_y_; }
    };
}

#endif