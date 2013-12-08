#include <stdio.h>
#include <stdlib.h>
#include "jpegapi.h"
#include "hdr.h"
#include <time.h>
#include <sys/time.h>

int main(int argc, char** argv)
{

    unsigned char* img_sub  = 0;
    unsigned char* img_normal = 0;
    unsigned char* img_supra  = 0;
    unsigned char* img_hdr    = 0;
    int w = 0, h = 0;
    unsigned long i, vect_size;

    if(argc < 5)
    {
        printf( "Usage: ./hdr img1.jpg img2.jpg img3.jpg imgfinal.jpg\n");
        return 1;
    }

    read_jpeg_file(&img_sub, &h, &w, argv[1]);
    read_jpeg_file(&img_normal, &h, &w, argv[2]);
    read_jpeg_file(&img_supra, &h, &w, argv[3]);
    vect_size = w*h*3;

    struct timeval start, end;

    gettimeofday(&start, NULL);

    apply_tone_mapping(img_sub, vect_size);
    apply_tone_mapping(img_normal, vect_size);
    apply_tone_mapping(img_supra, vect_size);


    img_hdr = malloc(vect_size* sizeof(unsigned char));
    for(i =0; i< vect_size; ++i)
    {
        int temp =0;
        temp += (int)img_sub[i];
        temp += (int)img_normal[i];
        temp += (int)img_supra[i];
        img_hdr[i] = (char)(temp/3);
    }

    gettimeofday(&end, NULL);


    printf("Time: %ld,%ld sec\n", (end.tv_sec - start.tv_sec),
     (end.tv_usec - start.tv_usec));

    write_jpeg_file(img_hdr, h,w, argv[4], 100);
    return 0;
}
