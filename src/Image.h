#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <imgui.h>
#include <memory>
#include "Color.h"
#include "RgbBuffer.h"
#include "ImageStats.h"

class Image {
public:
    Image(std::string const&& path);
    Image(std::string const& path);
    Image(size_t const width, size_t const height, RGBColor_t const color = {});
    Image(std::vector<uint8_t> const& grayscale, size_t const width, size_t const height);
    Image(uint8_t const buffer[], size_t const width, size_t const height);
    Image(RgbBuffer const& buffer);
    ~Image();

    Image(const Image&);
    Image& operator=(Image const& img);

    bool save(std::string const& path);

    void draw();
    void plot(std::string const& name);

    Image toGrayscale();
    void toGrayscaleVec(std::vector<uint8_t>& out);

    ImTextureID getTexture();

    void set(size_t const x, size_t const y, RGBColor_t const c);
    RGBColor_t get(size_t const x, size_t const y);

    void resize(size_t const width, size_t const height);

    void update(); // needs to be called to update the displayed texture on the GPU!

    void update_buffer(RgbBuffer const& buffer);

    size_t width() const;
    size_t height() const;
    size_t get_size_pixel() const;
    size_t get_size_bytes() const;
    RGBColor_t* get_buffer() const;

    void updateStats();

private:
    bool LoadTextureFromFile(std::string const& path);
    void copyImage(Image const& img, bool const assign);

    GLuint texture{0};
    RgbBuffer imageData{};

    bool showHist = false;
    bool showStats = false;

    std::vector<uint64_t> histR, histG, histB;
    double entropyR = 0;
    double entropyG = 0;
    double entropyB = 0;


};
