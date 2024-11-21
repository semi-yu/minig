#include <vector>
#include <memory>

#include <GLAD/glad.h>
#include <GLM/ext.hpp>

#include "./application_window.cpp"
#include "./shader_program.cpp"
#include "./movable.cpp"
#include "./camera.cpp"

#include "../interface/ishape.cpp"
#include "../interface/IEnginable.cpp"
#include "../auxil/exception.cpp"

namespace minig {
    class Graphical : public IEnginable {
        minig::ShaderProgram shader_program_;

        std::shared_ptr<minig::Camera> camera_;

        std::vector<std::shared_ptr<minig::Movable>> drawables;
        
    public:
        Graphical(
            minig::ShaderProgram& shader_program
        ): shader_program_(shader_program) {}

        void pre_run() override {
            glEnable(GL_DEPTH_TEST);

            shader_program_.use();

            for (auto& drawable: drawables) {
                drawable->pre_draw_call(shader_program_);
            }
        }

        void run() override {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (auto& drawable: drawables) {
                draw_preprocess();
                drawable->set_uniform_variables();
                drawable->draw_call(shader_program_);
            }
        }

        void draw_preprocess() {
            shader_program_.use();

            camera_->set_uniform_variables();
        }

        void register_drawable(std::shared_ptr<minig::Movable> drawable) {
            drawables.push_back(std::move(drawable));
        }

        void register_camera(std::shared_ptr<minig::Camera> camera) {
            camera_ = camera;
        }
    };
}