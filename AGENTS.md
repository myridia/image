# AGENTS.md — image

## What this is
Two C programs that encode ASCII text into a PNG image and decode a PNG image back into ASCII text, built with CMake.

## Stack
- C
- libpng
- CMake

## Build
```bash
mkdir build && cd build
cmake ..
make
```

## Run
```bash
./binary_strip output.png "Your text here"   # encode
./decode_png output.png                       # decode
```

## Structure
- `strip/CMakeLists.txt` — build configuration
- `strip/encode_png.c` — encodes text into PNG
- `strip/decode_png.c` — decodes PNG back to text
- `strip/a.png` — sample output image

## Conventions
- No comments in code unless asked.
- Verify: build with `cmake .. && make`.
