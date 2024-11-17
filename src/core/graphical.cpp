#include <vector>
#include <memory>

#include <GLAD/glad.h>
#include <GLM/ext.hpp>

#include "./application_window.cpp"
#include "./shader_program.cpp"
#include "./movable.cpp"

#include "../interface/ishape.cpp"
#include "../interface/IEnginable.cpp"
#include "../auxil/exception.cpp"

namespace minig {
    class Graphical : public IEnginable {
        minig::ShaderProgram shader_program_;

        std::vector<std::shared_ptr<minig::Movable>> drawables;
        
    public:
        Graphical(
            minig::ShaderProgram& shader_program
        ): shader_program_(shader_program) {}

        void pre_run() override {
            shader_program_.use();

            for (auto& drawable: drawables) {
                drawable->pre_draw_call(shader_program_);
            }
        }

        void run() override {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto& drawable: drawables) {
                draw_preprocess();
                drawable->set_uniform_variables();
                drawable->draw_call(shader_program_);
            }
        }

        void draw_preprocess() {
            shader_program_.use();

            glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                             glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));

            float aspect_ratio = static_cast<float>(800) / static_cast<float>(600);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
            
            shader_program_.send_projection_matrix(projection);
            shader_program_.send_view_matrix(view);
        }

        void register_drawable(std::shared_ptr<minig::Movable> drawable) {
            drawables.push_back(std::move(drawable));
        }
    };
}