#include <vector>
#include <memory>

#include <GLAD/glad.h>
#include <GLM/ext.hpp>

#include "./application_window.cpp"
#include "./shader_program.cpp"
#include "../interface/ishape.cpp"
#include "./textured.cpp"
#include "./colored.cpp"

#include "../interface/IEnginable.cpp"
#include "../auxil/exception.cpp"

namespace minig {
    class Graphical : public IEnginable {
        minig::ShaderProgram shader_program_;
        GLuint attribute_array_, vertex_buffer_, index_buffer_;

        std::vector<std::unique_ptr<minig::IShape>> drawables;
        
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
            for (auto& drawable: drawables) {
                draw_preprocess();
                drawable->draw_call(shader_program_);
            }
        }

        void draw_preprocess() {
            glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                             glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f)); 
            glm::mat4 model = glm::mat4(1.0f);

            float aspect_ratio = static_cast<float>(800) / static_cast<float>(600);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
            
            shader_program_.use();
            shader_program_.send_projection_matrix(projection);
            shader_program_.send_view_matrix(view);
            shader_program_.send_model_matrix(model);
        }

        void register_drawable(std::unique_ptr<minig::Textured> drawable) {
            drawables.push_back(std::move(drawable));
        }
    };
}