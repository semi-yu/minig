#include <string>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <fmt/core.h>

#include "../auxil/exception.cpp"

namespace minig {
    class ApplicationWindow {
        std::string window_title_;
        int window_width_, window_height_;

        GLFWwindow* window_;
    
    public:
        ApplicationWindow(
            const std::string& title, 
            int width, int height
        ): window_title_(title), window_width_(width), window_height_(height) {
            __init_opengl_context();
        }

        ~ApplicationWindow() {
            glfwTerminate();
        }

        void application_loop() {
            while(__keep_loop()) {
                fmt::print("{}\n", "Hello.");\
                
                glfwSwapBuffers(window_);
                glfwPollEvents();
            }
        }

    protected:
        bool __keep_loop() {
            return !glfwWindowShouldClose(window_);
        }
    private:
        void __init_opengl_context() {
            glfwInit();
            // Only OpenGL 4.3 or older version allows to use uniform variables
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            
            window_ = glfwCreateWindow(
                window_width_, window_height_,
                window_title_.c_str(), 
                NULL, NULL
            );

            if (window_ == NULL) {
                glfwTerminate();
                throw minig::auxil::GlfwInitFailure();
            }

            glfwMakeContextCurrent(window_);
            // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                glfwTerminate();
                throw minig::auxil::GladInitFailure();
            }
        }

    }; 
}