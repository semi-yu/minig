#include <GLAD/glad.h>
#include <GLM/ext.hpp>

#include "./application_window.cpp"
#include "./shader_program.cpp"
#include "../interface/IEnginable.cpp"
#include "../auxil/exception.cpp"

namespace minig {
    class Graphical : public IEnginable {
        minig::ShaderProgram shader_program_;
        GLuint attribute_array_, vertex_buffer_, index_buffer_;
    
    public:
        Graphical(
            minig::ShaderProgram& shader_program
        ): shader_program_(shader_program) {}

        void run() override {
            glViewport(0, 0, 800, 600);
            draw();
        }

        void draw() {
            glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                             glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f)); 
            glm::mat4 model = glm::mat4(1.0f);

            float aspect_ratio = static_cast<float>(800) / static_cast<float>(600);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
            
            shader_program_.use();

            shader_program_.send_float_mat4_data(std::string("projection"), projection);
            shader_program_.send_float_mat4_data(std::string("view"), view);
            shader_program_.send_float_mat4_data(std::string("model"), model);


            glBindVertexArray(attribute_array_);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        void configure_drawable() {
            float edge = 0.4;
            float ang = 3.14/6;
            auto vertices = std::vector<GLfloat>({
                -edge, -edge, 0.0, 1.0, 0.5, 0.2, 0.0, 
                -edge,  edge, 0.0, 1.0, 0.5, 0.2, 0.0, 
                 edge, -edge, 0.0, 1.0, 0.5, 0.2, 0.0,
                 edge,  edge, 0.0, 1.0, 0.5, 0.2, 0.0
            });

            auto indices = std::vector<GLuint>({
                0, 1, 2,
                1, 2, 3
            }); 

            glGenVertexArrays(1, &attribute_array_);
            glGenBuffers(1, &vertex_buffer_);
            glGenBuffers(1, &index_buffer_);

            glBindVertexArray(attribute_array_);

            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
        }
    };
}