#ifndef __KEYBOARD_ACTION_CALLBACK_CPP__
#define __KEYBOARD_ACTION_CALLBACK_CPP__

#include <memory>
#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>
#include <GLFW/glfw3.h>

#include "../interface/isubscribable.cpp"
#include "../interface/input_event.cpp"

namespace minig {
    class KeyboardButtonInputEvent : public KeyboardInputEvent {
        int button_;
        int action_;

    public:
        KeyboardButtonInputEvent(
            int button,
            int action
        ): button_(button), action_(action) {}

        int button() override { return button_; }

        int action() override { return action_; }
    };

    class KeyboardButtonEventListener {
        std::vector<std::shared_ptr<IKeyboardEventSubscribable>> subscribers_;

    public:
        virtual bool trigger_condition(int key, int scancode, int action, int mods) = 0;

        void register_subscriber(std::shared_ptr<IKeyboardEventSubscribable> subscriber) {
            subscribers_.push_back(subscriber);
        }

        void perform(std::unique_ptr<minig::KeyboardButtonInputEvent> event) {
            for (auto& subscriber: subscribers_) {
                subscriber->notice_keyboard_event(std::move(event));
            }
        }
    };

    class AButtonPressKeyboardEventListener : public KeyboardButtonEventListener {
        bool trigger_condition(int key, int scancode, int action, int mods) override {
            return key == GLFW_KEY_A && action == GLFW_PRESS;
        }
    };

    class DButtonPressKeyboardEventListener : public KeyboardButtonEventListener {
        bool trigger_condition(int key, int scancode, int action, int mods) override {
            return key == GLFW_KEY_D && action == GLFW_PRESS;
        }
    };

    class KeyboardButtonCallback {
        std::vector<std::unique_ptr<KeyboardButtonEventListener>> event_listeners_;

    public:
        void callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            for (auto& listener: event_listeners_) {
                auto event = std::make_unique<minig::KeyboardButtonInputEvent>(key, action);

                if (listener->trigger_condition(key, scancode, action, mods))
                    listener->perform(std::move(event));
            }
        }

        void register_event_listener(std::unique_ptr<KeyboardButtonEventListener> listener) {
            event_listeners_.push_back(std::move(listener));
        }
    };
}

#endif