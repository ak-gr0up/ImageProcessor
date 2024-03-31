project(image_processor)
set(CMAKE_CXX_STANDARD 20)

add_executable(
    image_processor
    image_processor.cpp
    src/image/BMP.cpp
    src/image/Image.cpp
    src/image/Pixel.cpp
    src/filters/Crop.cpp
    src/filters/Grayscale.cpp
    src/filters/Negative.cpp
    src/filters/Sharpening.cpp
    src/filters/Edge.cpp
    src/filters/ApplyMatrix.cpp
    src/filters/Blur.cpp
    src/filters/Oil.cpp
    src/factories/CropFactory.cpp
    src/factories/GrayscaleFactory.cpp
    src/factories/NegativeFactory.cpp
    src/factories/SharpeningFactory.cpp
    src/factories/EdgeFactory.cpp
    src/factories/BlurFactory.cpp
    src/factories/OilFactory.cpp
    src/utils/Convert.cpp
)

enable_testing()

add_executable(
    test_factories
    src/tests/TestFactories.cpp
    src/tests/TestFailedException.cpp
    src/image/Image.cpp
    src/image/Pixel.cpp
    src/filters/Crop.cpp
    src/filters/Grayscale.cpp
    src/filters/Negative.cpp
    src/filters/Sharpening.cpp
    src/filters/Edge.cpp
    src/filters/ApplyMatrix.cpp
    src/filters/Blur.cpp
    src/filters/Oil.cpp
    src/factories/CropFactory.cpp
    src/factories/GrayscaleFactory.cpp
    src/factories/NegativeFactory.cpp
    src/factories/SharpeningFactory.cpp
    src/factories/EdgeFactory.cpp
    src/factories/BlurFactory.cpp
    src/factories/OilFactory.cpp
    src/utils/Convert.cpp
)

add_executable(
    test_filters
    src/tests/TestFilters.cpp
    src/tests/TestFailedException.cpp
    src/image/Image.cpp
    src/image/Pixel.cpp
    src/filters/Crop.cpp
    src/filters/Grayscale.cpp
    src/filters/Negative.cpp
    src/filters/Sharpening.cpp
    src/filters/Edge.cpp
    src/filters/ApplyMatrix.cpp
    src/filters/Blur.cpp
    src/filters/Oil.cpp
)

add_executable(
    test_pixel
    src/tests/TestPixel.cpp
    src/tests/TestFailedException.cpp
    src/image/Pixel.cpp
)

add_test(
    NAME Factories
    COMMAND test_factories
)

add_test(
    NAME Filters
    COMMAND test_filters
)

add_test(
    NAME Pixel
    COMMAND test_pixel
)

target_include_directories(image_processor PUBLIC ./include)
target_include_directories(test_factories PUBLIC ./include)
target_include_directories(test_filters PUBLIC ./include)
target_include_directories(test_pixel PUBLIC ./include)
