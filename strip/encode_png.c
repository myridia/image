#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

void create_binary_png_strip(const char *output_file, const char *text) {
    // Calculate the number of characters
    size_t text_length = strlen(text);
    int width = text_length; // Each character corresponds to one column
    int height = 8; // Fixed height of 8 pixels

    // Allocate memory for the image
    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte *)malloc(width * 4); // 4 bytes per pixel (RGBA)
    }

    // Fill the image with binary data
    for (size_t char_index = 0; char_index < text_length; char_index++) {
        unsigned char byte = text[char_index]; // Get the ASCII value of the character
        for (int bit_index = 0; bit_index < 8; bit_index++) {
            // Determine the color based on the binary value
            int pixel_y = 7 - bit_index; // Invert the bit index to match the height
            if (byte & (1 << bit_index)) { // Check if the bit is set
                // Set pixel to black (1)
                row_pointers[pixel_y][char_index * 4 + 0] = 0;   // R (black)
                row_pointers[pixel_y][char_index * 4 + 1] = 0;   // G (black)
                row_pointers[pixel_y][char_index * 4 + 2] = 0;   // B (black)
            } else {
                // Set pixel to white (0)
                row_pointers[pixel_y][char_index * 4 + 0] = 255; // R (white)
                row_pointers[pixel_y][char_index * 4 + 1] = 255; // G (white)
                row_pointers[pixel_y][char_index * 4 + 2] = 255; // B (white)
            }
            // Set alpha to fully opaque
            row_pointers[pixel_y][char_index * 4 + 3] = 255; // A (fully opaque)
        }
    }

    // Write the image to a PNG file
    FILE *fp = fopen(output_file, "wb");
    if (!fp) {
        fprintf(stderr, "Error opening file %s\n", output_file);
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    if (setjmp(png_jmpbuf(png))) {
        fprintf(stderr, "Error during PNG creation\n");
        fclose(fp);
        return;
    }

    png_init_io(png, fp);
    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    // Cleanup
    fclose(fp);
    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    png_destroy_write_struct(&png, &info);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <output.png> <text>\n", argv[0]);
        return 1;
    }

    create_binary_png_strip(argv[1], argv[2]);
    return 0;
}
