#pragma once

#include <cstdint>

#pragma pack (push, 1)
struct RGBColor_t {
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
    std::uint8_t a = 255;

    RGBColor_t() {}

    RGBColor_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) :
            r(r), g(g), b(b), a(a)
    {}

    RGBColor_t(int r, int g, int b, int a = 255) :
            r(static_cast<uint8_t>(r)),
            g(static_cast<uint8_t>(g)),
            b(static_cast<uint8_t>(b)),
            a(static_cast<uint8_t>(a))
    {}

    RGBColor_t(int v) : RGBColor_t(v, v, v) {}

    RGBColor_t(float r, float g, float b, float a = 1.0) :
            r(static_cast<uint8_t>(r * 255)),
            g(static_cast<uint8_t>(g * 255)),
            b(static_cast<uint8_t>(b * 255)),
            a(static_cast<uint8_t>(a * 255))
    {}

    RGBColor_t(float v) : RGBColor_t(v, v, v) {}

    RGBColor_t(double r, double g, double b, double a = 1.0) :
            r(static_cast<uint8_t>(r * 255)),
            g(static_cast<uint8_t>(g * 255)),
            b(static_cast<uint8_t>(b * 255)),
            a(static_cast<uint8_t>(a * 255))
    {}

    RGBColor_t(double v) : RGBColor_t(v, v, v) {}

    uint8_t grayscale() {
        return (r + g + b) / 3;
    }
};
#pragma pack (pop)

struct YCRCBColor_t {
    uint8_t y;
    uint8_t cb;
    uint8_t cr;
};
