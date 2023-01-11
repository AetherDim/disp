
#include "RgbBuffer.h"

//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <cassert>

bool RgbBuffer::load_from_file(std::string const& path)
{
    // Load from file
    int image_widht = 0;
    int image_height = 0;
    auto data = reinterpret_cast<RGBColor_t*>(stbi_load(path.c_str(), &image_widht, &image_height, nullptr, 4));
    if (data == nullptr)
        return false;

    m_width = image_widht;
    m_height = image_height;
    m_buffer = std::make_unique<RGBColor_t[]>(m_width * m_height * sizeof(RGBColor_t));
    std::memcpy(m_buffer.get(), data, m_width * m_height * sizeof(RGBColor_t));
    stbi_image_free(data);

    return true;
}

RgbBuffer::RgbBuffer(size_t const initial_width, size_t const initial_height) : m_width{ initial_width }, m_height{ initial_height }, m_buffer{ std::make_unique<RGBColor_t[]>(initial_height*initial_width*sizeof(RGBColor_t)) } {

}

RgbBuffer::RgbBuffer(std::string const& filename) {
    assert(load_from_file(filename) && "damn you perry the platipus!");
}

size_t RgbBuffer::get_size() const {
    return m_width * m_height;
}

size_t RgbBuffer::get_size_bytes() const {
    return m_width * m_height * sizeof(RGBColor_t);
}

void RgbBuffer::resize(size_t const width, size_t const height) {
    m_buffer.reset();
    m_width = width;
    m_height = height;
    m_buffer = std::make_unique<RGBColor_t[]>(m_width* m_height * sizeof(RGBColor_t));
}

RGBColor_t* RgbBuffer::data() const {
    return m_buffer.get();
}

size_t RgbBuffer::get_width() const {
    return m_width;
}
size_t RgbBuffer::get_height() const {
    return m_height;
}
