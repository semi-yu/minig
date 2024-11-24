#ifndef __ISHAPE_CPP__
#define __ISHAPE_CPP__

#include <GLAD/glad.h>

namespace minig {
    class IShape {
    protected:
        GLuint attribute_array_, vertex_buffer_, index_buffer_;
        GLuint n_indices_;

        GLuint shape_type_;

    public:
        IShape() {}
        
        IShape(GLuint shape_type): shape_type_(shape_type) {}

        GLuint attribute_array() { return attribute_array_; }
        
        virtual void pre_draw_call(minig::ShaderProgram& shader_program) = 0;
        virtual void draw_call(minig::ShaderProgram& shader_program) = 0;

        void bind() const { glBindVertexArray(attribute_array_); }
        void unbind() const { glBindVertexArray(0); }

        void configure_vertex_buffer(std::vector<GLfloat>& vertices) {
            glGenBuffers(1, &vertex_buffer_);

            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        }

        void configure_index_buffer(std::vector<GLuint>& indices) {
            glGenBuffers(1, &index_buffer_);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

            n_indices_ = indices.size();
        }

        virtual void configure_attribute() = 0;

        GLuint shape_type() { return shape_type_; }

        void set_shape_type(GLuint type) { shape_type_ = type; }
    }; 
}

#endif