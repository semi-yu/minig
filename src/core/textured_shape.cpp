#ifndef __TEXTURED_SHAPE_CPP__
#define __TEXTURED_SHAPE_CPP__

#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>
#include <GLAD/glad.h>

#include <stb_image.h>

#include "./shader_program.cpp"
#include "./colored_shape.cpp"
#include "../auxil/exception.cpp"

namespace minig {
    class TexturedShape {
        GLuint attribute_array_, vertex_buffer_, index_buffer_;
        GLuint texture_name_;
    
    public:
        TexturedShape(
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices
        ) {
            glGenVertexArrays(1, &attribute_array_);

            bind();
                __configure_vertex_buffer(vertices);
                __configure_index_buffer(indices);
                __configure_encoding();
            unbind();
            
            __configure_texture();
        }

        void pre_draw_call(minig::ShaderProgram& shader_program) {
            GLuint shape_type = 1;

            shader_program.send_unsigned_integer_scalar_data(std::string("texture_sample"), 0);
            shader_program.send_unsigned_integer_scalar_data(std::string("shape_type"), shape_type);
        }

        void draw_call(minig::ShaderProgram& shader_program) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_name_);
            
            bind();
                glDrawElements(GL_TRIANGLES, n_indices_, GL_UNSIGNED_INT, 0);
            unbind();
        }

        void bind() { glBindVertexArray(attribute_array_); }

        void unbind() { glBindVertexArray(0); }

    protected:
        GLuint n_indices_;

        void __configure_vertex_buffer(std::vector<GLfloat>& vertices) {
            glGenBuffers(1, &vertex_buffer_);

            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        }

        void __configure_index_buffer(std::vector<GLuint>& indices) {
            glGenBuffers(1, &index_buffer_);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

            n_indices_ = indices.size();
        }

        void __configure_encoding() {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
        }

        void __configure_texture() {
            const char* path = "../resource/texture/wooden_container.jpg";

            glGenTextures(1, &texture_name_);
            glBindTexture(GL_TEXTURE_2D, texture_name_); 

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            stbi_set_flip_vertically_on_load(true);

            int width, height, channels;
            unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
            
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

#endif