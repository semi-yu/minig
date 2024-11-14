#ifndef _APPLICATION_WINDOw_RESIZE_CALLBACK_CPP__
#define _APPLICATION_WINDOw_RESIZE_CALLBACK_CPP__

#include <fmt/core.h>

#include <vector>
#include <memory>

#include <GLFW/glfw3.h>

namespace minig {
    class ApplicationWindowResizeCallback {
    public:
        void set(GLFWwindow* application_window) {
            glfwSetWindowUserPointer(application_window, this);
        }

        void register_callback(GLFWwindow* application_window) {
            glfwSetFramebufferSizeCallback(application_window, callback_wrapper);
        }

    protected:
        void callback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }

        static void callback_wrapper(GLFWwindow* window, int width, int height) {
            ApplicationWindowResizeCallback* instance = static_cast<ApplicationWindowResizeCallback*>(glfwGetWindowUserPointer(window));
            if (instance) {
                instance->callback(window, width, height);
            }
        }
    };
}

#endif