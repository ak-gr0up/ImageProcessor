#include "image/BMP.h"

void Byteswap(int16_t &var) {
    var = static_cast<int16_t>(__bswap_16(var));
}

void Byteswap(int32_t &var) {
    var = static_cast<int32_t>(__bswap_32(var));
}

BMP::BMP(std::string input_path) {
    LoadBMP(input_path);
}

Image BMP::ConvertToImage() {
    Image image = Image(info_header_.height, info_header_.width);
    int32_t data_ptr = 0;
    for (int32_t row = info_header_.height - 1; row >= 0; row--) {
        for (int32_t column = 0; column < info_header_.width; column++) {
            image(row, column) = Pixel(data_[data_ptr + 2], data_[data_ptr + 1], data_[data_ptr]);
            data_ptr += BYTES_PER_PIXEL;
        }
    }
    return image;
}

void BMP::UpdateFromImage(const Image &image) {
    info_header_.height = image.GetHeight();
    info_header_.width = image.GetWidth();
    data_.resize(static_cast<size_t>(image.GetHeight()) * image.GetWidth() * BYTES_PER_PIXEL);

    int32_t data_ptr = 0;
    for (int32_t row = image.GetHeight() - 1; row >= 0; row--) {
        for (int32_t column = 0; column < image.GetWidth(); column++) {
            std::tie(data_[data_ptr + 2], data_[data_ptr + 1], data_[data_ptr]) = image(row, column).RGBValue();
            data_ptr += BYTES_PER_PIXEL;
        }
    }
}

void BMP::FormatHeadersEndiann() {
    if (NEED_TO_SWAP_ENDIANN) {
        Byteswap(file_header_.identifier);
        Byteswap(file_header_.size);
        Byteswap(file_header_.offset);
        for (int16_t &var : file_header_.reserved) {
            Byteswap(var);
        }

        Byteswap(info_header_.size);
        Byteswap(info_header_.width);
        Byteswap(info_header_.height);
        Byteswap(info_header_.color_planes);
        Byteswap(info_header_.bits_per_pixel);

        for (int32_t &var : info_header_.redundant) {
            Byteswap(var);
        }
    }
}

void BMP::ExportBMP(std::string path) {
    std::ofstream file{path, std::ios_base::binary};
    if (!file) {
        throw std::runtime_error("Cannot open the output file for writing.");
    }

    try {
        int32_t padding_count = info_header_.width % 4;

        info_header_.size = sizeof(BitmapInfoHeader);
        file_header_.offset = BITMAP_FILE_HEADER_SIZE + sizeof(BitmapInfoHeader);
        file_header_.size =
            file_header_.offset + static_cast<int32_t>(data_.size()) + info_header_.height * padding_count;

        FormatHeadersEndiann();

        file.write(reinterpret_cast<char *>(&file_header_.identifier), sizeof(file_header_.identifier));
        file.write(reinterpret_cast<char *>(&file_header_.size), sizeof(file_header_.size));
        file.write(reinterpret_cast<char *>(&file_header_.reserved), sizeof(file_header_.reserved));
        file.write(reinterpret_cast<char *>(&file_header_.offset), sizeof(file_header_.offset));
        file.write(reinterpret_cast<const char *>(&info_header_), sizeof(info_header_));

        FormatHeadersEndiann();

        int32_t row_length = info_header_.width * BYTES_PER_PIXEL;
        for (int32_t row = 0; row < info_header_.height; row++) {
            int32_t start_index = row * row_length;
            for (int32_t i = start_index; i < start_index + row_length; i++) {
                file.write(reinterpret_cast<const char *>(&data_[i]), sizeof(data_[i]));
            }
            for (int32_t i = 0; i < padding_count; i++) {
                const char padding = 0;
                file.write(&padding, sizeof(char));
            }
        }
    } catch (const std::exception &ex) {
        throw std::runtime_error("Error occured when saving the resulting image:\n" + std::string(ex.what()));
    }
}

void BMP::LoadBMP(std::string path) {
    std::ifstream file{path, std::ios::binary};
    if (!file) {
        throw std::runtime_error("Cannot open the input file for reading.");
    }

    try {

        file.read(reinterpret_cast<char *>(&file_header_.identifier), sizeof(file_header_.identifier));
        file.read(reinterpret_cast<char *>(&file_header_.size), sizeof(file_header_.size));
        file.read(reinterpret_cast<char *>(&file_header_.reserved), sizeof(file_header_.reserved));
        file.read(reinterpret_cast<char *>(&file_header_.offset), sizeof(file_header_.offset));
        file.read(reinterpret_cast<char *>(&info_header_), sizeof(info_header_));

        FormatHeadersEndiann();
    } catch (const std::exception &ex) {
        throw std::runtime_error("Error occured when reading input image file header:\n" + std::string(ex.what()));
    }

    if (info_header_.bits_per_pixel != BYTES_PER_PIXEL * BYTE) {
        throw std::invalid_argument("Programm works only with 24-bit bmp files");
    }

    try {
        file.seekg(file_header_.offset, file.beg);

        int32_t row_length = info_header_.width * BYTES_PER_PIXEL;
        data_.resize(info_header_.height * row_length);

        int32_t data_ptr = 0;
        for (int32_t row = 0; row < info_header_.height; row++) {
            for (int32_t column = 0; column < row_length; column++) {
                file.read(reinterpret_cast<char *>(&data_[data_ptr]), sizeof(data_[data_ptr]));
                ++data_ptr;
            }

            char padding[3];
            for (int32_t i = 0; i < info_header_.width % 4; i++) {
                file.read(&padding[i], sizeof(padding[i]));
            }
        }
    } catch (const std::exception &ex) {
        throw std::runtime_error("Error occured when reading input image:\n" + std::string(ex.what()));
    }
}