#include "./format.hpp"

minig::attribute::Format::Format(
    std::string name,
    GLuint index,
    GLsizei size,
    GLenum type,
    GLboolean normalized,
    GLsizei offset
): name(name), index(index), size(size), type(type), normalized(normalized), offset(offset) {}