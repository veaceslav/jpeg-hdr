#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>

void write_jpeg_file(unsigned char* raw_image, int img_h, int img_w,
                    char* filename, int quality);

int read_jpeg_file(unsigned char** image_buffer, int* img_h, int* img_w,
                    char* filename);

void put_scanline_someplace(JSAMPROW pixelrow, int row_width);
