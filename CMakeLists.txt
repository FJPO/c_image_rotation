cmake_minimum_required(VERSION 3.17)
project(image_rotation)

set(CMAKE_CXX_STANDARD 14)

add_executable(image_rotation src/main.c src/mock_image.c src/mock_image.h src/bmp_handler.c src/bmp_handler.h src/app.c src/app.h)

