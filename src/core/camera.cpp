#ifndef __CAMERA_CPP
#define __CAMERA_CPP

#include <GLAD/glad.h>
#include <GLM/ext.hpp>

#include "./shader_program.cpp"
#include "./movable.cpp"

namespace minig {
    class Camera : public Movable {
        minig::ShaderProgram shader_program_;
        glm::vec3 position_, look_at_, up_;
        glm::mat4 projection_;

        bool mouse_view_initialization = false;
        double last_position_x = 400, last_position_y = 300;

    public:
        Camera(
            minig::ShaderProgram& shader_program,
            glm::mat4 projection=glm::perspective(glm::radians(45.0f), 8/(float)6, 0.1f, 100.0f),
            glm::vec3 position=glm::vec3(0.0, 0.0, 3.0),
            glm::vec3 look_at=glm::vec3(0.0, 0.0, 0.0),
            glm::vec3 up=glm::vec3(0.0, 1.0, 0.0)
        ): projection_(projection), 
        position_(position), look_at_(look_at), up_(up) {}

        void notice_keyboard_event(std::unique_ptr<KeyboardInputEvent> event) override {
            float move_multiplier = 0.5;

            auto pressed = event->button();

            if (pressed == GLFW_KEY_A) { 
                position_.x -= move_multiplier * 5;
            }
            else if (pressed == GLFW_KEY_D) { 
                position_.x += move_multiplier * 5;
            }
            else if (pressed == GLFW_KEY_W) {
                position_.z -= move_multiplier * 2.5;
            }
            else if (pressed == GLFW_KEY_S) {
                position_.z += move_multiplier * 2.5;
            }
        }

        void notice_mouse_move_event(std::unique_ptr<MouseMoveInputEvent> event) {
            float mouse_sensitivity = 0.01;
            auto cursor_x = event->position_x(), cursor_y = event->position_y();

            if (!mouse_view_initialization) {
                last_position_x = cursor_x;
                last_position_y = cursor_y;
                mouse_view_initialization = true;
            }

            float offset_x = (cursor_x - last_position_x) * mouse_sensitivity;
            float offset_y = (last_position_y - cursor_y) * mouse_sensitivity;
            last_position_x = cursor_x;
            last_position_y = cursor_y;

            look_at_.x += offset_x;
            look_at_.y += offset_y;
        }

        void set_uniform_variables() {
            glm::mat4 view = glm::lookAt(
                position_, look_at_, up_
            );

            shader_program_.send_projection_matrix(projection_);
            shader_program_.send_view_matrix(view);
        }
    };
}

#endif