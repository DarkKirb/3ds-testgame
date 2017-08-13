#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <iostream>
#include <png.hpp>
#include <3ds.h>
//Code copypasted from http://zarb.org/~gc/html/libpng.html
PNG::PNG(const char* fname) {
    unsigned char header[8];
    auto fp = fopen(fname, "rb");
    if(!fp) {
        std::cerr << "File " << fname << " could not be opened" << std::endl;
        abort();
    }
    fread(header, 1, 8, fp);
    if(png_sig_cmp(header, 0, 8)) {
        std::cerr << "File " << fname << " is not a valid PNG" << std::endl;
        abort();
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if(!png_ptr)
        abort();

    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr)
        abort();


    if(setjmp(png_jmpbuf(png_ptr)))
        abort();

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    png_read_update_info(png_ptr, info_ptr);

    row_pointers = new png_bytep[height];
    for(int y=0;y<height;y++)
        row_pointers[y] = new png_byte[png_get_rowbytes(png_ptr, info_ptr)];

    png_read_image(png_ptr, row_pointers);
    fclose(fp);
}

PNG::~PNG() {
    for(int i=0;i<height;i++)
        delete[] row_pointers[i];
    delete[] row_pointers;
}
unsigned char* PNG::copyImage(bool linear) {
    int pixel_width = bit_depth/8;
    int line_width = pixel_width * width;
    unsigned char* dest;
    if(linear) {
        dest = (unsigned char*)linearAlloc(height*width*pixel_width);
    } else {
        dest = new unsigned char[height*width*pixel_width];
    }
    for(int i=0;i<height;i++) {
        memcpy(dest+line_width*i, row_pointers[i], line_width);
    }
    return dest;
}

void PNG::copyImage(void *dest) {
    int pixel_width = bit_depth/8;
    int line_width = pixel_width * width;
    for(int i=0;i<height;i++)
        memcpy(dest+line_width*i, row_pointers[i], line_width);
}
