cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PNGTextEncoderDecoder)

# Find the PNG library
find_package(PNG REQUIRED)

# Add the executable for the decode program
add_executable(encode_png encode_png.c)
target_link_libraries(encode_png PRIVATE PNG::PNG)

# Add the executable for the binary strip program
add_executable(decode_png decode_png.c)
target_link_libraries(decode_png PRIVATE PNG::PNG)


