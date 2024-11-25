#ifndef __ATTRIBUTE_LAYOUT_HPP__
#define __ATTRIBUTE_LAYOUT_HPP__

#include <vector>

#include <GLAD/glad.h>

#include "./format.hpp"

namespace minig::attribute { class Format; }

namespace minig::attribute {
    struct Layout {
        std::vector<minig::attribute::Format> attribute_formats;
        GLsizei stride;

        Layout();

        void add_format(minig::attribute::Format format);

        unsigned int get_byte_offset();

        unsigned int get_index();

        unsigned int get_stride();

        void set_stride();
    };
}

#endif