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
        std::unique_ptr<WindowResizeCallback> window_resize_callback_;
        std::unique_ptr<MouseButtonCallback> mouse_button_callback_;
        std::unique_ptr<MouseMoveCallback> mouse_move_callback_;
        std::unique_ptr<KeyboardButtonCallback> keyboard_button_callback_;

    public:
        void register_window_resize_callback(std::unique_ptr<WindowResizeCallback> callback) {
            window_resize_callback_ = std::move(callback);
        }

        void register_mouse_button_callback(std::unique_ptr<MouseButtonCallback> callback) {
            mouse_button_callback_ = std::move(callback);
        }

        void register_mouse_move_callback(std::unique_ptr<MouseMoveCallback> callback) {
            mouse_move_callback_ = std::move(callback);
        }

        void register_keyboard_button_callback(std::unique_ptr<KeyboardButtonCallback> callback) {
            keyboard_button_callback_ = std::move(callback);
        }

        void initialize(GLFWwindow* window) {
            glfwSetWindowUserPointer(window, this);

            if (window_resize_callback_ != nullptr) glfwSetFramebufferSizeCallback(window, window_resize_wrapper);

            if (mouse_move_callback_ != nullptr) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPosCallback(window, mouse_move_wrapper);
            }

            if (mouse_button_callback_ != nullptr) glfwSetMouseButtonCallback(window, mouse_button_wrapper);

            if (keyboard_button_callback_ != nullptr) glfwSetKeyCallback(window, keyboard_button_wrapper);
        }
    
    private:
        static void window_resize_wrapper(GLFWwindow* window, int width, int height) {
            auto instance = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

            if (instance && instance->window_resize_callback_ != nullptr) {
                instance->window_resize_callback_->callback(window, width, height);
            }
        }

        static void mouse_move_wrapper(GLFWwindow* window, double xpos, double ypos) {
            auto instance = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

            if (instance && instance->mouse_move_callback_ != nullptr) {
                instance->mouse_move_callback_->callback(window, xpos, ypos);
            }
        }

        static void mouse_button_wrapper(GLFWwindow* window, int button, int action, int mods) {
            auto instance = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

            if (instance && instance->mouse_button_callback_ != nullptr) {
                instance->mouse_button_callback_->callback(window, button, action, mods);
            }
        }

        static void keyboard_button_wrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto instance = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

            if (instance && instance->keyboard_button_callback_ != nullptr) {
                instance->keyboard_button_callback_->callback(window, key, scancode, action, mods);
            }
        }
    };
}

#endif