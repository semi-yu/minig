#ifndef _APPLICATION_WINDOw_RESIZE_CALLBACK_CPP__
#define _APPLICATION_WINDOw_RESIZE_CALLBACK_CPP__

#include <vector>
#include <memory>

#include <GLFW/glfw3.h>

namespace minig {
    class WindowResizeCallback {
    public:
        void callback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    };
}

#endif