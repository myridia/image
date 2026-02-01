#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

void decode_png_to_text(const char *input_file) {
    FILE *fp = fopen(input_file, "rb");
    if (!fp) {
        fprintf(stderr, "Error opening file %s\n", input_file);
        return;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    if (setjmp(png_jmpbuf(png))) {
        fprintf(stderr, "Error during PNG reading\n");
        fclose(fp);
        return;
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);
    png_byte color_type = png_get_color_type(png, info);

    // Ensure the image is in RGBA format
    if (color_type != PNG_COLOR_TYPE_RGBA) {
        png_set_expand(png);
        png_set_palette_to_rgb(png);
        png_set_tRNS_to_alpha(png);
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
        color_type = PNG_COLOR_TYPE_RGBA;
    }

    png_read_update_info(png, info);

    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
    }
    png_read_image(png, row_pointers);

    fclose(fp);

    // Decode the binary data from the PNG
    char *decoded_text = (char *)malloc(width + 1); // +1 for null terminator
    for (int x = 0; x < width; x++) {
        unsigned char byte = 0;
        for (int y = 0; y < height; y++) {
            // Check if the pixel is black (1) or white (0)
            if (row_pointers[y][x * 4] == 0) { // Check the red channel for black
                byte |= (1 << (7 - y)); // Set the corresponding bit
            }
        }
        decoded_text[x] = byte; // Store the ASCII character
    }
    decoded_text[width] = '\0'; // Null-terminate the string

    // Print the decoded text
    printf("Decoded text: %s\n", decoded_text);

    // Cleanup
    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    free(decoded_text);
    png_destroy_read_struct(&png, &info, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input.png>\n", argv[0]);
        return 1;
    }

    decode_png_to_text(argv[1]);
    return 0;
}
