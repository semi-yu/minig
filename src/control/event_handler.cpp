#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include <memory>
#include <vector>

#include <GLFW/glfw3.h>

#include "./window_resize_callback.cpp"
#include "./mouse_action_callback.cpp"
#include "./keyboard_action_callback.cpp"

namespace minig {
    class EventHandler {
        std::unique_ptr<WindowResizeCallback> window_resize_callback;
        std::unique_ptr<MouseButtonCallback> mouse_button_callback;
        std::unique_ptr<MouseMoveCallback> mouse_move_callback;
        std::unique_ptr<KeyboardButtonCallback> keyboard_button_callback;

    public:
        EventHandler() {
            window_resize_callback = std::make_unique<WindowResizeCallback>();
            mouse_button_callback = std::make_unique<MouseButtonCallback>();
            mouse_move_callback = std::make_unique<MouseMoveCallback>();
            keyboard_button_callback = std::make_unique<KeyboardButtonCallback>();
        }

        void register_window_resize_callback(std::unique_ptr<WindowResizeCallback> callback) {
            window_resize_callback = std::move(callback);
        }

        void register_mouse_button_callback(std::unique_ptr<MouseButtonCallback> callback) {
            mouse_button_callback = std::move(callback);
        }

        void register_mouse_move_callback(std::unique_ptr<MouseMoveCallback> callback) {
            mouse_move_callback = std::move(callback);
        }

        void register_keyboard_button_callback(std::unique_ptr<KeyboardButtonCallback> callback) {
            keyboard_button_callback = std::move(callback);
        }

        void initialize(GLFWwindow* window) {
            glfwSetWindowUserPointer(window, this);

            glfwSetFramebufferSizeCallback(window, window_resize_wrapper);
            glfwSetCursorPosCallback(window, mouse_move_wrapper);
            glfwSetMouseButtonCallback(window, mouse_button_wrapper);
            glfwSetKeyCallback(window, keyboard_button_wrapper);
        }
    
    private:
        static void window_resize_wrapper(GLFWwindow* window, int width, int height) {
            auto instance = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

            if (instance) {
                instance->window_resize_callback->callback(window, width, height);
            }
        }

        static void mouse_move_wrapper(GLFWwindow* window, double xpos, double ypos) {
            auto instance = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

            if (instance) {
                instance->mouse_move_callback->callback(window, xpos, ypos);
            }
        }

        static void mouse_button_wrapper(GLFWwindow* window, int button, int action, int mods) {
            auto instance = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

            if (instance) {
                instance->mouse_button_callback->callback(window, button, action, mods);
            }
        }

        static void keyboard_button_wrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto instance = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

            if (instance) {
                instance->keyboard_button_callback->callback(window, key, scancode, action, mods);
            }
        }
    };
}

#endif