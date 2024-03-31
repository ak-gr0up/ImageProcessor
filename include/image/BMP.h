#include <fstream>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <bit>
#include <climits>
#include <byteswap.h>
#include <iostream>
#include "image/Image.h"

const size_t REDUNDANT_SIZE = 6;

struct BitmapFileHeader {
    int16_t identifier;
    int32_t size;
    int16_t reserved[2];
    int32_t offset;
};

struct BitmapInfoHeader {
    int32_t size;
    int32_t width;
    int32_t height;
    int16_t color_planes;
    int16_t bits_per_pixel;
    int32_t redundant[REDUNDANT_SIZE];
};

const size_t BITMAP_FILE_HEADER_SIZE = sizeof(BitmapFileHeader::identifier) + sizeof(BitmapFileHeader::size) +
                                       sizeof(BitmapFileHeader::reserved) + sizeof(BitmapFileHeader::offset);
const int32_t BYTES_PER_PIXEL = 3;
const int32_t BYTE = 8;
const bool NEED_TO_SWAP_ENDIANN = std::endian::native == std::endian::big;

class BMP {
private:
    BitmapFileHeader file_header_;
    BitmapInfoHeader info_header_;
    std::vector<uint8_t> data_;

public:
    explicit BMP(std::string input_path);

    Image ConvertToImage();

    void UpdateFromImage(const Image &image);

    void FormatHeadersEndiann();

    void ExportBMP(std::string path);

    void LoadBMP(std::string path);
};