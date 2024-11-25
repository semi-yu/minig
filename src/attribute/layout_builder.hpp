#ifndef __ATTRIBUTE_LAYOUT_BUILDER_HPP__
#define __ATTRIBUTE_LAYOUT_BUILDER_HPP__

#include <memory>

#include "./layout.hpp"
#include "./format.hpp"

namespace minig::attribute { class Layout; }
namespace minig::attribute { class Format; }

namespace minig::attribute {
    class LayoutBuilder {
        typedef LayoutBuilder self;

        std::shared_ptr<minig::attribute::Layout> attribute_layout_;

    public:
        LayoutBuilder();

        std::shared_ptr<minig::attribute::Layout> get_attribute_layout();

        self& position();

        self& color(bool include_alpha = false);

        self& texture_wrap();

        self& normal();
    };
}

#endif