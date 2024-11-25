#ifndef __ATTRIBUTE_FORMAT_HPP__
#define __ATTRIBUTE_FORMAT_HPP__

#include <string>

#include <GLAD/glad.h>

namespace minig::attribute {
    struct Format {
        std::string name;
        GLuint index;
        GLsizei size;
        GLenum type;
        GLboolean normalized;
        GLsizei offset;

        Format(
            std::string name,
            GLuint index,
            GLsizei size,
            GLenum type,
            GLboolean normalized,
            GLsizei offset
        );
    };
}

#endif