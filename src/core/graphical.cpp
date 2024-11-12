#include <GLAD/glad.h>
#include <GLM/ext.hpp>

#include "./application_window.cpp"
#include "../interface/IEnginable.cpp"
#include "../auxil/exception.cpp"

namespace minig {
    class Graphical : public IEnginable {
        GLuint shader_program_name_;
        GLuint attribute_array_, vertex_buffer_, index_buffer_;
    
    public:
        Graphical() {
            shader_program_name_ = set_program();
        }

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
            glUniformMatrix4fv(
                glGetUniformLocation(shader_program_name_, "projection"), 
                1, GL_FALSE, glm::value_ptr(projection)
            );

            glUniformMatrix4fv(
                glGetUniformLocation(shader_program_name_, "view"),
                1, GL_FALSE, glm::value_ptr(view)
            ); 

            glUniformMatrix4fv(
                glGetUniformLocation(shader_program_name_, "model"),
                1, GL_FALSE, glm::value_ptr(model)
            ); 

            glUseProgram(shader_program_name_);
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

        GLuint set_program() {
            int success;
            char log[512];
            GLuint shader_program = glCreateProgram();

            std::string vertex_source = "#version 430 core\n"
            "in vec3 position;\n"
            "in vec4 color;\n"
            "out vec4 mid_color;\n"
            "void main() {\n"
            "    gl_Position = vec4(position, 1.0);\n"
            "    mid_color = color;\n"
            "}\n";

            std::string fragment_source = "#version 430 core\n"
            "in vec4 mid_color;\n"
            "out vec4 fragment_color;\n"
            "void main() {\n"
            "    fragment_color = mid_color;\n"
            "}\n"; 
            
            GLuint vertex = set_shader(vertex_source, GL_VERTEX_SHADER);
            GLuint fragment = set_shader(fragment_source, GL_FRAGMENT_SHADER);

            glAttachShader(shader_program, vertex);
            glAttachShader(shader_program, fragment);
            glLinkProgram(shader_program);

            glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader_program, 512, NULL, log);
                throw minig::auxil::ShaderProgramLinkFailure(std::string(log));
            }

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            return shader_program;
        }

        GLuint set_shader(std::string& source, GLuint type) {
            std::string shader_name;
            if (type == GL_VERTEX_SHADER) shader_name = std::string("vertex");
            else if (type == GL_FRAGMENT_SHADER) shader_name = std::string("fragment");

            int success;
            char log[512];
            GLuint name = glCreateShader(type);

            const char* raw_source = source.c_str();
            glShaderSource(name, 1, &raw_source, NULL);
            glCompileShader(name);
            
            glGetShaderiv(name, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(name, 512, NULL, log);
                throw minig::auxil::ShaderCompilationFailure(shader_name, std::string(log)); 
            }

            return name;
        }
    };
}