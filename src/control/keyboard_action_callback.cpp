#ifndef __KEYBOARD_ACTION_CALLBACK_CPP__
#define __KEYBOARD_ACTION_CALLBACK_CPP__

#include <memory>
#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>
#include <GLFW/glfw3.h>

#include "../interface/isubscribable.cpp"
#include "../interface/input_event.cpp"

#include "../interface/input_event.cpp"
#include "./keyboard_event_list.cpp"

namespace minig {
    class KeyboardButtonEvent {
        public:
        virtual bool trigger_condition(int key, int scancode, int action, int mods) = 0;
        virtual void action() = 0;
    };

    class TestKeyboardEvent : public KeyboardButtonEvent {
        bool trigger_condition(int key, int scancode, int action, int mods) override {
            return key == GLFW_KEY_A && action == GLFW_PRESS;
        }

        void action() {
            fmt::print(bg(fmt::color::dodger_blue), "[KEYBOARD] A button pressed\n");
        }
    };

    class KeyboardButtonCallback {
        std::vector<std::unique_ptr<KeyboardButtonEvent>> events_;

    public:
        KeyboardButtonCallback() {
            register_event(std::make_unique<TestKeyboardEvent>());
        }

        void callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            for (auto& event: events_) {
                if (event->trigger_condition(key, scancode, action, mods))
                    event->action();
            }
        }
        
        void register_event(std::unique_ptr<KeyboardButtonEvent> event) {
            events_.push_back(std::move(event));
        }
    };
}

#endif