#ifndef __MOVEABLE_CPP__
#define __MOVEABLE_CPP__

#include <memory>

#include <GLAD/glad.h>
#include <GLM/ext.hpp>

#include "./textured.cpp"

#include "./shader_program.cpp"

#include "../interface/input_event.cpp"
#include "../control/keyboard_action_callback.cpp"

namespace minig {
    class Movable : public minig::Textured, public minig::IKeyboardEventSubscribable, public minig::IMouseMoveEventSubscribable {
        glm::mat4 translation_, rotation_, scalation_;
        GLfloat rotational_angle_ = 0.0;

        minig::ShaderProgram shader_program_;

    public:
        Movable() {}
        
        Movable(
            minig::ShaderProgram& shader_program,
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices,
            std::string& texture_path
        ): Textured(vertices, indices, texture_path), shader_program_(shader_program) {
            translation_ = glm::mat4(1.0);
            rotation_ = glm::mat4(1.0);
            scalation_ = glm::mat4(1.0);
        }

        void notice_keyboard_event(std::unique_ptr<KeyboardInputEvent> event) override {
            auto pressed = event->button();

            if (pressed == GLFW_KEY_A) { rotational_angle_ += 0.5; }
            else if (pressed == GLFW_KEY_D) { rotational_angle_ -= 0.5; }

            rotation_ = glm::rotate(glm::mat4(1.0), rotational_angle_, glm::vec3(0.0, 1.0, 0.0));
        }

        void notice_mouse_move_event(std::unique_ptr<MouseMoveInputEvent> event) override {
            auto cursor_x = event->position_x(), cursor_y = event->position_y();

            fmt::print("cursor position ({}, {})\n", cursor_x, cursor_y);
        }

        void set_uniform_variables() {
            shader_program_.use();

            shader_program_.send_translation_matrix(translation_);
            shader_program_.send_rotation_matrix(rotation_);
            shader_program_.send_scalation_matrix(scalation_);
        }

        void translate(glm::vec3&& position) {
            translation_ = glm::translate(glm::mat4(1.0), position);
        }

        void rotate(glm::vec3&& axis, GLfloat radian) {
            rotation_ = glm::rotate(glm::mat4(1.0), radian, axis);
        }

        void scale(glm::vec3& extend) {
            scalation_ = glm::scale(glm::mat4(1.0), extend);
        }

        void accumulate_translate(glm::vec3& position) {
            translation_ = glm::translate(translation_, position);
        }

        void accumulate_rotate(glm::vec3& axis, GLfloat radian) {
            rotation_ = glm::rotate(rotation_, radian, axis);
        }

        void accumulate_scale(glm::vec3& extend) {
            scalation_ = glm::scale(scalation_, extend);
        }
    };
}

#endif