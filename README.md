# image
Include binary data to images


Simple CMake configuration for the two C programs we created: one for encoding ASCII text into a PNG image and another for decoding the PNG image back into ASCII text.

### Directory Structure
Assuming you have the following directory structure:

```
/your_project_directory
├── CMakeLists.txt
├── encode_png.c
└── decode_png.c
```

### CMakeLists.txt
Create a file named `CMakeLists.txt` in your project directory with the following content:

```cmake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PNGTextEncoderDecoder)

# Find the PNG library
find_package(PNG REQUIRED)

# Add the executable for the encode program
add_executable(encode_png encode_png.c)
target_link_libraries(encode_png PRIVATE PNG::PNG)

# Add the executable for the decode program
add_executable(decode_png decode_png.c)
target_link_libraries(decode_png PRIVATE PNG::PNG)
```

### How to Use CMake

1. **Install CMake**: If you haven't installed CMake yet, you can do so using your package manager. For example, on Ubuntu, you can use:
   ```bash
   sudo apt-get install cmake
   ```

2. **Create a Build Directory**: It's a good practice to create a separate build directory to keep the build files organized. Navigate to your project directory and create a build directory:
   ```bash
   mkdir build
   cd build
   ```

3. **Run CMake**: From the build directory, run CMake to configure the project:
   ```bash
   cmake ..
   ```

4. **Build the Project**: After configuring the project, you can build it using:
   ```bash
   make
   ```

5. **Run the Programs**: After building, you will have two executables: `binary_strip` and `decode_png`. You can run them as follows:
   - To encode text into a PNG:
     ```bash
     ./binary_strip output.png "Your text here"
     ```
   - To decode the PNG back into text:
     ```bash
     ./decode_png output.png
     ```

### Summary
- The `CMakeLists.txt` file specifies the project name, finds the PNG library, and defines the executables for both programs.
- You create a build directory, run CMake to configure the project, and then use `make` to build the executables.
- Finally, you can run the programs to encode and decode text to and from PNG images.

