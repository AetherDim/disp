
#ifndef AVS3_IMAGESTAT_H
#define AVS3_IMAGESTAT_H

#include <vector>
#include <cmath>
#include "RgbBuffer.h"

struct ImageStats {

    enum class ColorChannel {
        R, G, B, A
    };

    template<typename T>
    static void calcHist(RgbBuffer const & buffer, std::vector<T>& hist, ColorChannel channel = ColorChannel::R) {
        hist.resize(256);

        for(size_t i = 0; i < buffer.get_size(); i++) {
            switch (channel) {
                case ColorChannel::R:
                    hist[buffer.data()[i].r] ++;
                    break;
                case ColorChannel::G:
                    hist[buffer.data()[i].g] ++;
                    break;
                case ColorChannel::B:
                    hist[buffer.data()[i].b] ++;
                    break;
                case ColorChannel::A:
                    hist[buffer.data()[i].a] ++;
                    break;
            }
        }
    }

    template<typename T>
    static double calcEntropyFromHist(std::vector<T> const & hist, ColorChannel channel = ColorChannel::R) {
        size_t max = 0;
        for(size_t i = 0; i < 256; i++) {
            if(max < hist[i]) max = hist[i];
        }

        double entropy = 0;

        for(size_t i = 0; i < 256; i++) {
            if(max != 0 && hist[i] != 0) {
                double p = static_cast<double>(hist[i])/static_cast<double>(max);
                entropy += p * std::log2(p);
            }
        }

        return -entropy;
    }

    static double calcEntropy(RgbBuffer const & buffer, ColorChannel channel = ColorChannel::R) {
        std::vector<size_t> hist;
        calcHist(buffer, hist, channel);

        return calcEntropyFromHist(hist, channel);
    }



};

#endif //AVS3_IMAGESTAT_H
