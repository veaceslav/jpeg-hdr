#include "hdr.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double get_luminance(unsigned char* raw_image, unsigned long vector_size)
{
    unsigned long i;
    double img_key;
    float* lum = malloc((vector_size/3)*sizeof(float));

    for(i = 0; i < vector_size; i=i+3)
    {
        lum[i/3] = RED_WEIGHT*raw_image[i] +GREEN_WEIGHT*raw_image[i+1] + BLUE_WEIGHT*raw_image[i+2];
    }

    img_key = get_image_key(lum, vector_size/3);
    printf("Got Image key %lf\n", img_key);
    free(lum);
    return img_key;
}

double get_image_key(float* lum, unsigned long lum_size)
{
    double img_key =0;
    double buff = 0;
    unsigned long i;

    for(i = 0 ; i < lum_size; i++)
    {
        buff = buff + log(DELTA + (double)(lum[i]));
    }
    printf("Got buff %lf \n", buff);

    img_key = buff/(double)lum_size;

    return img_key;
}

void apply_tone_mapping(unsigned char* raw_image, unsigned long vector_size)
{
    double lum = 0;
    double light_ajust = 0;
    unsigned long i;

    lum = get_luminance(raw_image, vector_size);

    light_ajust = ALPHA/lum;

    for(i = 0; i < vector_size; ++i)
    {
        double tmp_pixel = (double)raw_image[i] * light_ajust;
        tmp_pixel*= range_fix(tmp_pixel);
        if(tmp_pixel > 255)
            tmp_pixel = 255;

        raw_image[i] = (char)tmp_pixel;
    }
}

double range_fix(double value)
{
    return (value*(1+ value/(LWHITE*LWHITE)))/(1 + value);
}
