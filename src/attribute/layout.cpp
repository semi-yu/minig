#include "./layout.hpp"

minig::attribute::Layout::Layout() {}

void minig::attribute::Layout::add_format(minig::attribute::Format format) { 
    attribute_formats.push_back(format); 
}

unsigned int minig::attribute::Layout::get_byte_offset() {
    unsigned int res = 0;
    
    for (auto& format: attribute_formats)
        res += format.size * sizeof(format.type);

    return res;
}

unsigned int minig::attribute::Layout::get_index() {
    return attribute_formats.size();
}

unsigned int minig::attribute::Layout::get_stride() {
    unsigned int res = 0;

    for (auto& format: attribute_formats)
        res += format.size;

    return res;
}

void minig::attribute::Layout::set_stride() {
    stride = get_stride();
}