#ifndef __MOUSE_ACTION_CALLBACK_CPP__
#define __MOUSE_ACTION_CALLBACK_CPP__

#include <vector>
#include <memory>

#include <fmt/core.h>
#include <fmt/color.h>
#include <GLFW/glfw3.h>

#include "../interface/isubscribable.cpp"
#include "../interface/input_event.cpp"

namespace minig {
    class MouseMoveEventListener {
        std::vector<std::shared_ptr<IMouseMoveEventSubscribable>> subscribers_;

    public:
        void register_subscriber(std::shared_ptr<IMouseMoveEventSubscribable> subscriber) {
            subscribers_.push_back(subscriber);
        }

        void perform(std::unique_ptr<minig::MouseMoveInputEvent> event) {
            for (auto& subscriber: subscribers_) {
                subscriber->notice_mouse_move_event(std::move(event));
            }
        }
    };
    
    class MouseMoveCallback {
    public:
        void callback(GLFWwindow* window, double xpos, double ypos) {
            fmt::print("mouse cursor position ({}, {})\n", xpos, ypos);
        }
    };

    class MouseButtonEvent {
    public:
        virtual bool trigger_condition(int button, int action, int mods) = 0;
        virtual void perform() = 0;
    };

    class TestMouseEvent : public MouseButtonEvent {
        bool trigger_condition(int button, int action, int mods) override {
            return button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS;
        }

        void perform() {
            fmt::print(bg(fmt::color::dodger_blue), "[MOUSE] right button pressed\n");
        }
    };

    class MouseButtonCallback {
        std::vector<std::unique_ptr<MouseButtonEvent>> events_;

    public:
        MouseButtonCallback() {
            register_event(std::make_unique<TestMouseEvent>());
        }

        void callback(GLFWwindow* window, int button, int action, int mods) {
            for (auto& event: events_) {
                if (event->trigger_condition(button, action, mods))
                    event->perform();
            }
        }

        void register_event(std::unique_ptr<MouseButtonEvent> event) {
            events_.push_back(std::move(event));
        }
    };
}

#endif 