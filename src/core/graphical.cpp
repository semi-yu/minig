#include <GLAD/glad.h>

#include "../interface/IEnginable.cpp"
#include "../auxil/exception.cpp"

namespace minig {
    class Graphical : public IEnginable {
        GLuint shader_program_name_;
    
    public:
        Graphical() {
            shader_program_name_ = set_program();
        }

        void run() {
            return;
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