#include <GLAD/glad.h>

#include "../auxil/exception.cpp"
#include "./shader_program.cpp"
#include "../interface/ishape.cpp"

namespace minig {
    class Colored : public IShape{
    
    public:
        Colored(
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices
        ): IShape(static_cast<GLuint>(0)) {
            glGenVertexArrays(1, &attribute_array_);
            configure(vertices, indices);
        }

        void pre_draw_call(minig::ShaderProgram& shader_program) {
            shader_program.send_unsigned_integer_scalar_data(
                std::string("shape_type"), shape_type_
            );
        }

        void draw_call(minig::ShaderProgram& shader_program) {
            bind();
                glDrawElements(GL_TRIANGLES, n_indices_, GL_UNSIGNED_INT, 0);
            unbind();
        }

        void configure(
            std::vector<GLfloat>& vertices,
            std::vector<GLuint>& indices
        ) {
            bind();
                configure_vertex_buffer(vertices);
                configure_index_buffer(indices);
                configure_attribute();
            unbind();
        }

        void configure_attribute() override {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        }
    };
}