#include <stdio.h>
#include "jpegapi.h"

int main(int argc, char** argv)
{

    unsigned char* my_img  = 0;
    int w = 0, h = 0;
    //int i,j;

    if(argc < 5)
    {
        printf( "Usage: ./hdr img1.jpg img2.jpg img3.jpg imgfinal.jpg\n");
        return 1;
    }

    read_jpeg_file(&my_img, &h, &w, argv[1]);
    /*
    for(i=0; i< h; i++)
    {
        for(j = 0; j < w*3; j++)
        {
            printf("%d ",my_img[i*h*3 +j]);
        }
        printf("\n");
    }
    */

    write_jpeg_file(my_img, h,w, "test_out.jpg", 100);
    return 0;
}
