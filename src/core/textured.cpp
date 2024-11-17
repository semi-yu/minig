#include <GLAD/glad.h>

#include <stb_image.h>

#include "../auxil/exception.cpp"
#include "./shader_program.cpp"
#include "../interface/ishape.cpp"

namespace minig {
    class Textured : public IShape {
        GLuint texture_name_;
    
    public:
        Textured() {}
        
        Textured(
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices,
            std::string& texture_path
        ): IShape(static_cast<GLuint>(1)) {
            glGenVertexArrays(1, &attribute_array_);
            configure(vertices, indices, texture_path);
        }

        void pre_draw_call(minig::ShaderProgram& shader_program) {
            shader_program.send_unsigned_integer_scalar_data(
                std::string("texture_sample"), 0);

            shader_program.send_unsigned_integer_scalar_data(
                std::string("shape_type"), shape_type_);
        }

        void draw_call(minig::ShaderProgram& shader_program) {
            bind();
            bind_texture();

            glDrawElements(GL_TRIANGLES, n_indices_, GL_UNSIGNED_INT, 0);

            unbind_texture();
            unbind();
        }

        void bind_texture() {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_name_);
        }

        void unbind_texture() {
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindVertexArray(0);
        }

        void configure(
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices,
            std::string& texture_path
        ) {
            bind();
                configure_vertex_buffer(vertices);
                configure_index_buffer(indices);
                configure_attribute();
            unbind();

            configure_texture(texture_path);
        }

        void configure_attribute() override {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
        }

        void configure_texture(std::string& path) {
            glGenTextures(1, &texture_name_);
            glBindTexture(GL_TEXTURE_2D, texture_name_); 

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            stbi_set_flip_vertically_on_load(true);

            int width, height, channels;
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
            
            if (data)
            {
                glTexImage2D(
                    GL_TEXTURE_2D, 
                    0, GL_RGB, width, height, 
                    0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                throw minig::auxil::TextureLoadFailure(std::string(path)); 
            }
            
            stbi_image_free(data);
        }
    }; 
}