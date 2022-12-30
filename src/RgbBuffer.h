
#ifndef RGB_BUFFER_H
#define RGB_BUFFER_H

#include <memory>
#include <string>
#include "Color.h"

class RgbBuffer {
public:
    RgbBuffer(size_t const initial_width = 512, size_t const initial_height = 512);
    RgbBuffer(std::string const& file);
    RgbBuffer(RgbBuffer const&) = delete;
    RgbBuffer& operator=(RgbBuffer const&) = delete;

    size_t get_size() const;
    size_t get_size_bytes() const;
    size_t get_width() const;
    size_t get_height() const;
    void resize(size_t const width, size_t const height);
    RGBColor_t* data() const;

private:
    using RgbBuffer_t = std::unique_ptr<RGBColor_t[]>;

    bool load_from_file(std::string const& path);

    size_t m_width;
    size_t m_height;
    RgbBuffer_t m_buffer;
};

#endif
