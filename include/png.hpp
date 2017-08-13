#pragma once
#include <png.h>
struct PNG {
    int width, height;
    png_byte color_type, bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep *row_pointers;

    PNG(const char *fname);
    ~PNG();

    unsigned char * copyImage(bool linear);
    void copyImage(void *);
};
