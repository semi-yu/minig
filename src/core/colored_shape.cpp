#ifndef __COLORED_SHAPE_CPP__
#define __COLORED_SHAPE_CPP__

#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>
#include <GLAD/glad.h>

#include "./shader_program.cpp"

namespace minig {
    class ColoredShape {
        GLuint attribute_array_, vertex_buffer_, index_buffer_;
    
    public:
        ColoredShape(
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices
        ) {
            __configure_drawable_context(vertices, indices); 
            fmt::print(bg(fmt::color::green), "[info] {}\n", "Successful shape init.");
        }

        void draw_call(minig::ShaderProgram& shader_program) {
            bind();
            shader_program.send_integer_scalar_data(std::string("shape_type"), 0);
            glDrawElements(GL_TRIANGLES, n_indices_, GL_UNSIGNED_INT, 0);
            unbind();
        }

        void bind() { glBindVertexArray(attribute_array_); }

        void unbind() { glBindVertexArray(0); }
    
    protected:
        GLuint n_indices_;
        
        void __configure_drawable_context(
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices
        ) {
            glGenVertexArrays(1, &attribute_array_);
            
            bind();

            __configure_vertex_buffer(vertices);
            __configure_index_buffer(indices);
            __configure_encoding();

            unbind();
        }

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
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
        }
    }; 
}

#endif