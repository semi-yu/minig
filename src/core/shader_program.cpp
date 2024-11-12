#include <vector>

#include <GLAD/glad.h>
#include <GLM/ext.hpp>

namespace minig {
    class ShaderProgram {
        GLuint shader_program_name_;

        // Auxiliary data
        int n_shaders_ = 2;

        std::vector<std::string> shader_sources_ = {
            "#version 430 core\n"
            "layout(location = 0) in vec3 position;\n"
            "layout(location = 1) in vec4 color;\n"
            "uniform mat4 projection;\n"
            "uniform mat4 view;\n"
            "uniform mat4 model;\n"
            "out vec4 mid_color;\n"
            "void main() {\n"
            "    gl_Position = projection * view * model * vec4(position, 1.0);\n"
            "    mid_color = color;\n"
            "}\n",

            "#version 430 core\n"
            "in vec4 mid_color;\n"
            "out vec4 fragment_color;\n"
            "void main() {\n"
            "    fragment_color = mid_color;\n"
            "}\n"
        };

        std::array<GLuint, 2> shader_types_ = { 
            GL_VERTEX_SHADER, 
            GL_FRAGMENT_SHADER 
        };

        std::array<std::string, 2> shader_names_ = { 
            std::string("vertex"), 
            std::string("fragment") 
        };

    public:
        ShaderProgram() {
            shader_program_name_ = __set_program();
        }

        void use() { glUseProgram(shader_program_name_); }

        void send_integer_scalar_data(const std::string& name, GLuint value) {
            glUniform1i(
                glGetUniformLocation(shader_program_name_, name.c_str()), 
                value
            );
        }

        void send_float_mat4_data(const std::string& name, glm::mat4& value) {
            glUniformMatrix4fv(
                glGetUniformLocation(shader_program_name_, name.c_str()), 
                1, GL_FALSE, glm::value_ptr(value)
            );
        }

    private:
        GLuint __set_program() {
            int success;
            char log[512];
            GLuint shader_program_name = glCreateProgram();
            std::array<GLuint, 2> shader_refers_;

            for (int i = 0; i < n_shaders_; i++) {
                shader_refers_[i] = __set_shader(
                    shader_sources_.at(i), 
                    shader_names_.at(i),
                    shader_types_.at(i)
                );
 
                glAttachShader(shader_program_name, shader_refers_.at(i));
            }
            
            glLinkProgram(shader_program_name);

            glGetProgramiv(shader_program_name, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader_program_name, 512, NULL, log);
                throw minig::auxil::ShaderProgramLinkFailure(std::string(log));
            }

            for (int i = 0; i < n_shaders_; i++) {
                glDeleteShader(shader_refers_.at(i));
            }

            return shader_program_name;
        }

        GLuint __set_shader(std::string& source, std::string& name, GLuint type) {
            int success;
            char log[512];
            GLuint shader_name = glCreateShader(type);

            const char* raw_source = source.c_str();
            glShaderSource(shader_name, 1, &raw_source, NULL);
            glCompileShader(shader_name);
            
            glGetShaderiv(shader_name, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader_name, 512, NULL, log);
                throw minig::auxil::ShaderCompilationFailure(name, std::string(log)); 
            }

            return shader_name;
        }
    }; 
}
