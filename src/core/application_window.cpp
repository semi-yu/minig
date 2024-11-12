#include <string>
#include <vector>
#include <memory>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <fmt/core.h>

#include "../auxil/exception.cpp"
#include "../interface/IEnginable.cpp"

namespace minig {
    class ApplicationWindow {
        std::string window_title_;
        int window_width_, window_height_;

        GLFWwindow* window_;
        std::vector<std::unique_ptr<IEnginable>> enginables;
    
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
                __pre_process();

                for (auto& engine: enginables) {
                    engine->run();
                }
                
                __post_process();
            }
        }

        void register_enginable(std::unique_ptr<IEnginable>& enginable) {
            enginables.push_back(std::move(enginable)); 
        }

    protected:
        bool __keep_loop() {
            return !glfwWindowShouldClose(window_);
        }

        void __pre_process() {
            // to be done...
        }

        void __post_process() {
            glfwSwapBuffers(window_);
            glfwPollEvents();
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