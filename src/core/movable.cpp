#ifndef __MOVEABLE_CPP__
#define __MOVEABLE_CPP__

#include <memory>

#include <GLAD/glad.h>
#include <GLM/ext.hpp>

#include "./textured.cpp"

#include "./shader_program.cpp"

#include "../interface/input_event.cpp"
#include "../control/keyboard_action_callback.cpp"
#include "../control/keyboard_event_list.cpp"

namespace minig {
    class Movable : public minig::Textured, public minig::ISubscribable {
        glm::mat4 translation_, rotation_, scalation_;
        GLfloat rotational_angle_ = 0.0;

        minig::ShaderProgram shader_program_;
    public:
        Movable(
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices,
            std::string& texture_path,
            minig::ShaderProgram& shader_program
        ): Textured(vertices, indices, texture_path), shader_program_(shader_program) {
            translation_ = glm::mat4(1.0);
            rotation_ = glm::mat4(1.0);
            scalation_ = glm::mat4(1.0);
        }

        void notice(std::unique_ptr<InputEvent> event) {
            shader_program_.use();
            
            auto pressed = event->button();

            if (pressed == GLFW_KEY_A) { rotational_angle_ += 0.5; }
            else if (pressed == GLFW_KEY_D) { rotational_angle_ -= 0.5; }

            rotation_ = glm::rotate(glm::mat4(1.0), rotational_angle_, glm::vec3(0.0, 1.0, 0.0));
        }

        void set_uniform_variables() {
            shader_program_.send_translation_matrix(translation_);
            shader_program_.send_rotation_matrix(rotation_);
            shader_program_.send_scalation_matrix(scalation_);
        }
    };
}

#endif