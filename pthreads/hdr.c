#include "hdr.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHREADS 4

void* stage1(void* tid)
{
    threadData* data = (threadData*)tid;
    int i;
    int begin, end;
    double temp;
    //printf("Thread %d, inceput %d, dimensiune %d\n", data->tindex, data->begin_index, data->size);
    begin = data->begin_index;
    end = data->begin_index + data->size;

    for(i = begin; i < end; i = i+3)
    {
        temp = RED_WEIGHT*data->array[i] +
               GREEN_WEIGHT*data->array[i+1] +
               BLUE_WEIGHT*data->array[i+2];
        data->img_key_partial +=log(DELTA + temp);
    }
    pthread_exit(NULL);
}

void* stage2(void* tid)
{
    threadData* data = (threadData*)tid;
    int i;
    int begin, end;
    begin = data->begin_index;
    end = data->begin_index + data->size;

    for(i = begin; i < end; ++i)
    {
        double tmp_pixel = (double)data->array[i] * data->img_key_partial;
        tmp_pixel*= range_fix(tmp_pixel);
        if(tmp_pixel > 255)
            tmp_pixel = 255;

        data->array[i] = (char)tmp_pixel;
    }
    pthread_exit(NULL);
}
double get_luminance(unsigned char* raw_image, unsigned long vector_size)
{
    int j;
    double img_key_thr = 0;
    int slice_size;

    /***** Pthread Stuff */

    pthread_t threads[NTHREADS];
    pthread_attr_t attr;
    threadData t_data[NTHREADS];

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    slice_size = vector_size/NTHREADS;

    for(j = 0; j < NTHREADS; j++)
    {
        t_data[j].array = raw_image;
        t_data[j].begin_index = j*slice_size;
        t_data[j].size = slice_size;
        t_data[j].tindex = j;
        t_data[j].img_key_partial = 0;
        pthread_create(&threads[j], &attr, stage1, (void *) &t_data[j]);
    }

    for(j = 0; j<NTHREADS; j++)
    {
        pthread_join(threads[j], NULL);
    }

    for(j = 0; j < NTHREADS; j++)
    {
        img_key_thr+=t_data[j].img_key_partial;
    }
    img_key_thr/=(vector_size/3);

    return img_key_thr;
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
    //printf("Got buff %lf \n", buff);

    img_key = buff/(double)lum_size;

    return img_key;
}

void apply_tone_mapping(unsigned char* raw_image, unsigned long vector_size)
{
    double lum = 0;
    double light_ajust = 0;
    int j;

    int slice_size;

    /***** Pthread Stuff */

    pthread_t threads[NTHREADS];
    pthread_attr_t attr;
    threadData t_data[NTHREADS];

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    slice_size = vector_size/NTHREADS;

    lum = get_luminance(raw_image, vector_size);

    light_ajust = ALPHA/lum;

    for(j = 0; j < NTHREADS; j++)
    {
        t_data[j].array = raw_image;
        t_data[j].begin_index = j*slice_size;
        t_data[j].size = slice_size;
        t_data[j].tindex = j;
        t_data[j].img_key_partial = light_ajust;
        pthread_create(&threads[j], &attr, stage2, (void *) &t_data[j]);
    }

    for(j = 0; j<NTHREADS; j++)
    {
        pthread_join(threads[j], NULL);
    }
}

double range_fix(double value)
{
    return (value*(1+ value/(LWHITE*LWHITE)))/(1 + value);
}
