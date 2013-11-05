#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include <setjmp.h>

struct my_error_mgr {
    struct jpeg_error_mgr pub;

    jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr* my_error_ptr;


void write_jpeg_file(JSAMPLE* image_buffer, int img_h, int img_w,
                    char* filename, int quality);

int read_jpeg_file(JSAMPLE* image_buffer, int img_h, int img_w,
                    char* filename);

void put_scanline_someplace(JSAMPROW pixelrow, int row_width);
