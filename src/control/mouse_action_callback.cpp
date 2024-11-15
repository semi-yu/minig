#ifndef __MOUSE_ACTION_CALLBACK_CPP__
#define __MOUSE_ACTION_CALLBACK_CPP__

#include <vector>
#include <memory>

#include <fmt/core.h>
#include <fmt/color.h>
#include <GLFW/glfw3.h>

namespace minig {
    class MouseMoveCallback {
    public:
        void callback(GLFWwindow* window, double xpos, double ypos) {
            fmt::print("mouse cursor position ({}, {})\n", xpos, ypos);
        }
    };

    class MouseButtonEvent {
    public:
        virtual bool trigger_condition(int button, int action, int mods) = 0;
        virtual void action() = 0;
    };

    class TestMouseEvent : public MouseButtonEvent {
        bool trigger_condition(int button, int action, int mods) override {
            return button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS;
        }

        void action() {
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
                    event->action();
            }
        }

        void register_event(std::unique_ptr<MouseButtonEvent> event) {
            events_.push_back(std::move(event));
        }
    };
}

#endif 