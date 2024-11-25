#include <fmt/core.h>
#include <GLAD/glad.h>

#include "./layout_builder.hpp"

minig::attribute::LayoutBuilder::LayoutBuilder() : attribute_layout_(std::make_shared<minig::attribute::Layout>()) {}

std::shared_ptr<minig::attribute::Layout> minig::attribute::LayoutBuilder::get_attribute_layout() {
    attribute_layout_->set_stride();
    return std::move(attribute_layout_);
}

minig::attribute::LayoutBuilder::self& minig::attribute::LayoutBuilder::position() {
    attribute_layout_->add_format(
        minig::attribute::Format(
            std::string("position"),
            attribute_layout_->get_index(),
            3,
            GL_FLOAT,
            GL_FALSE,
            attribute_layout_->get_byte_offset()
        )
    );

    return *this;
}

minig::attribute::LayoutBuilder::self& minig::attribute::LayoutBuilder::color(bool include_alpha) {
    attribute_layout_->add_format(
        minig::attribute::Format(
            std::string("color"),
            attribute_layout_->get_index(),
            include_alpha ? 3 : 4,
            GL_FLOAT,
            GL_FALSE,
            attribute_layout_->get_byte_offset()
        )
    );

    return *this;
}

minig::attribute::LayoutBuilder::self& minig::attribute::LayoutBuilder::texture_wrap() {
    attribute_layout_->add_format(
        minig::attribute::Format(
            std::string("texture_wrap"),
            attribute_layout_->get_index(),
            2,
            GL_FLOAT,
            GL_FALSE,
            attribute_layout_->get_byte_offset()
        )
    );

    return *this;
}

minig::attribute::LayoutBuilder::self& minig::attribute::LayoutBuilder::normal() {
    attribute_layout_->add_format(
        minig::attribute::Format(
            std::string("normal"),
            attribute_layout_->get_index(),
            3,
            GL_FLOAT,
            GL_FALSE,
            attribute_layout_->get_byte_offset()
        )
    );

    return *this;
}