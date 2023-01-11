#include <iostream>

#include "Image.h"

#include "imgui.h"
#include "implot.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

void updateTexture(GLuint texture, RGBColor_t* data, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, texture);

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void CreateTexture(GLuint* out_texture) {
    glGenTextures(1, out_texture);
    glBindTexture(GL_TEXTURE_2D, *out_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

}

// Simple helper function to load an image into a OpenGL texture with common settings
/*bool Image::LoadTextureFromFile(std::string const& path)
{
    // Load from file
	int image_widht = 0;
	int image_height = 0;
    auto data = reinterpret_cast<RGBColor_t*>(stbi_load(path.c_str(), &image_widht, &image_height, nullptr, 4));
    if (data == nullptr)
        return false;

	this->imageWidth = image_widht;
	this->imageHeight = image_height;
	this->imageSizePixel = imageWidth * imageHeight;
	this->imageSizeBytes = this->imageSizePixel * sizeof(RGBColor_t);

	imageData = std::make_unique<RGBColor_t[]>(this->imageSizeBytes);
	std::memcpy(imageData.get(), data, this->imageSizeBytes);
	stbi_image_free(data);

	CreateTexture(&this->texture);

	updateTexture(this->texture, imageData.get(), this->imageWidth, this->imageHeight);

    return true;
}*/

void freeTexture(GLuint* texture, RGBColor_t* data) {
    glBindTexture(GL_TEXTURE_2D, 0); // bind default texture
    glDeleteTextures(1, texture);
}

Image::Image(size_t const width, size_t const height, RGBColor_t const color) : imageData{ width, height } {
    CreateTexture(&this->texture);

    for (auto i{ 0 }; i < this->imageData.get_size(); ++i) {
        this->imageData.data()[i] = color;
    }

    this->update();
}

Image::Image(std::vector<uint8_t> const& grayscale, size_t const width, size_t const height): imageData{ width, height }
{
    CreateTexture(&this->texture);

    for (auto i{ 0 }; i < imageData.get_size(); ++i) {
        this->imageData.data()[i] = {grayscale[i]};
    }

    this->update();
}

Image::Image(uint8_t const buffer[], size_t const width, size_t const height) : imageData{ width, height } {
    CreateTexture(&this->texture);

    for (auto i{ 0 }; i < imageData.get_size(); ++i) {
        this->imageData.data()[i] = { buffer[i] };
    }

    this->update();
}

Image::Image(RgbBuffer const& buffer): Image(0, 0) {
    this->update_buffer(buffer);
}

void Image::resize(size_t const width, size_t const height) {
    imageData.resize(width, height);
}

Image::Image(std::string const&& path) : imageData{ path } {
    CreateTexture(&this->texture);
    this->update();
}

Image::Image(std::string const& path) : imageData{ path } {
    CreateTexture(&this->texture);
    this->update();
}

Image::Image(Image const& img) {
    copyImage(img, false);
}

Image& Image::operator=(Image const& img) {
    copyImage(img, true);
    return *this;
}

void Image::copyImage(Image const& img, bool const assign) {
    if (assign) {
        glBindTexture(GL_TEXTURE_2D, 0); // bind default texture
        glDeleteTextures(1, &this->texture);
    }
    CreateTexture(&this->texture);
    this->imageData.resize(img.width(), img.height());
    std::memcpy(this->imageData.data(), img.imageData.data(), this->imageData.get_size_bytes());

    this->update(); // update texture content
}

Image::~Image() {
    glBindTexture(GL_TEXTURE_2D, 0); // bind default texture
    glDeleteTextures(1, &this->texture);
}

void Image::draw() {
    ImGui::Image((void*)(intptr_t)this->texture, ImVec2(this->width(), this->height()));
}

void Image::update() {
    updateTexture(this->texture, this->imageData.data(), this->width(), this->height());
    updateStats();
}

void Image::plot(std::string const& name) {

    if(ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_MenuBar)) {
        if(ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Stats"))
            {
                ImGui::MenuItem("Plot histogram", nullptr, &this->showHist);
                ImGui::MenuItem("Show stats", nullptr, &this->showStats);
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        if(ImPlot::BeginPlot(name.c_str(), ImVec2(-1, 500), ImPlotFlags_Equal)) {
            ImPlot::PlotImage(name.c_str(), this->getTexture(), ImPlotPoint(0, 0), ImPlotPoint(this->width(), this->height()));
            ImPlot::EndPlot();
        }

        if(this->showStats) {
            ImGui::Text("Stats:");
            ImGui::Value("Entropy R", this->entropyR, nullptr);
            ImGui::Value("Entropy G", this->entropyG, nullptr);
            ImGui::Value("Entropy B", this->entropyB, nullptr);
        }

        if(this->showHist) {
            if(ImPlot::BeginPlot(("Histogram: " + name).c_str(), ImVec2(-1, 0))) {

                ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4{1, 0, 0, 1});
                ImPlot::PlotLine("R", this->histR.data(), this->histR.size());
                ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4{0, 1, 0, 1});
                ImPlot::PlotLine("G", this->histG.data(), this->histG.size());
                ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4{0, 0, 1, 1});
                ImPlot::PlotLine("B", this->histB.data(), this->histB.size());
                ImPlot::PopStyleColor(3);

                ImPlot::EndPlot();
            }
        }

    }



    ImGui::End();
}

ImTextureID Image::getTexture() {
    return (void*)(intptr_t)this->texture;
}

size_t Image::width() const {
    return this->imageData.get_width();
}

size_t Image::height() const {
    return this->imageData.get_width();
}

size_t Image::get_size_bytes() const {
    return this->imageData.get_size_bytes();
}

size_t Image::get_size_pixel() const {
    return this->imageData.get_size();
}

void Image::set(size_t const x, size_t const y, RGBColor_t const c) {
    if (x > imageData.get_width() || y > imageData.get_height()) {
        std::cerr << "out of bounds access in Image::set detected!" << std::endl;
        return;
    }
    this->imageData.data()[y * this->imageData.get_width() + x] = c;
}

RGBColor_t Image::get(size_t const x, size_t const y) {
    if (x > this->imageData.get_width() || y > imageData.get_height()) {
        std::cerr << "out of bounds access in Image::get detected!" << std::endl;
        return std::move(RGBColor_t{});
    }
    return this->imageData.data()[y * this->imageData.get_width() + x];
}

RGBColor_t* Image::get_buffer() const {
    return imageData.data();
}

bool Image::save(std::string const& path) {
    size_t idx = path.find_last_of(".");

    std::string filetype = "png";

    if(idx < path.size()) {
        filetype = path.substr(idx+1, path.size());
    }

    int res = 0;

    int width = this->width();
    int height = this->height();

    if(filetype == "png") {
        res = stbi_write_png(path.c_str(), width, height, 4, this->imageData.data(), this->imageData.get_width() * 4);
    } else if(filetype == "jpg") {

        int comp = 80;

        if(width < 100 && height < 100) {
            comp = 100;
        }

        res = stbi_write_jpg(path.c_str(), width, height, 4, this->imageData.data(), comp);
    } else if(filetype == "bmp") {
        res = stbi_write_bmp(path.c_str(), width, height, 4, this->imageData.data());
    } else if(filetype == "tga") {
        res = stbi_write_tga(path.c_str(), width, height, 4, this->imageData.data());
    } else {
        //assert(false && "unknown image type!");
    }

    return res == 0;
}

Image Image::toGrayscale() {
    Image res = *this; // copy

    for(size_t i = 0; i < res.get_size_pixel(); i++) {
        res.get_buffer()[i] = {res.get_buffer()[i].grayscale()};
    }

    res.update();

    return res;
}

void Image::toGrayscaleVec(std::vector<uint8_t>& out) {
    out.resize(this->get_size_pixel());
    auto buff = this->get_buffer();
    for(size_t i = 0; i < this->get_size_pixel(); i++) {
        out[i] = {buff[i].grayscale()};
    }
}

void Image::update_buffer(RgbBuffer const& buffer) {
    if (imageData.get_width() != buffer.get_width() || imageData.get_height() != buffer.get_height()) {
        imageData.resize(buffer.get_width(), buffer.get_height());
    }

    std::memcpy(imageData.data(), buffer.data(), imageData.get_size_bytes());
    this->update();
}


void Image::updateStats() {
    ImageStats::calcHist(this->imageData, this->histR, ImageStats::ColorChannel::R);
    ImageStats::calcHist(this->imageData, this->histG, ImageStats::ColorChannel::G);
    ImageStats::calcHist(this->imageData, this->histB, ImageStats::ColorChannel::B);

    this->entropyR = ImageStats::calcEntropyFromHist(this->histR);
    this->entropyG = ImageStats::calcEntropyFromHist(this->histG);
    this->entropyB = ImageStats::calcEntropyFromHist(this->histB);
}
