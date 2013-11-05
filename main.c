#include <stdio.h>
#include "jpegapi.h"

int main(int argc, char** argv)
{

    JSAMPLE* my_img  = 0;
    int w = 0, h = 0;

    if(argc < 5)
    {
        printf( "Usage: ./hdr img1.jpg img2.jpg img3.jpg imgfinal.jpg\n");
        return 1;
    }

    read_jpeg_file(my_img, w, h, argv[1]);
    return 0;
}
