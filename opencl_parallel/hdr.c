#include "hdr.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <sys/time.h>
double get_luminance(unsigned char* raw_image, unsigned long vector_size,
                     cl_device_id device, cl_context context,
                     cl_command_queue queue)
{
    unsigned long i;
    double img_key;
    double* lum = malloc((vector_size/3)*sizeof(double));
    cl_kernel kernel;

    cl_mem bufferIN;    // data IN
    cl_mem bufferOUT;   // data OUT

    struct timeval start, end;

    // allocate memory INPUT - device RAM/VRAM, OpenCL handled
    gettimeofday(&start, NULL);
    bufferIN = clCreateBuffer(context, CL_MEM_READ_ONLY, vector_size*sizeof(char), NULL, NULL);

    // allocate memory OUTPUT - device RAM/VRAM, OpenCL hendled
    bufferOUT= clCreateBuffer(context, CL_MEM_WRITE_ONLY, vector_size*sizeof(double), NULL, NULL);

    // write data to specified device address, OpenCL handled
    clEnqueueWriteBuffer(queue, bufferIN, 1, 0, vector_size*sizeof(char), raw_image,0,0,0);
    gettimeofday(&end, NULL);
    kernel = get_kernel("../kernel.cl", "doubleInput", device, context);
    // pass args, execute OPENCL kernels

    size_t global_work_size = vector_size/3;
    int vsize = vector_size/3;

    check2(clSetKernelArg(kernel, 0, sizeof(bufferIN),  (void*)&bufferIN));
    check2(clSetKernelArg(kernel, 1, sizeof(bufferOUT),  (void*)&bufferOUT));

    size_t global_work = vector_size/3;

    // start first kernel
    check2(clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work, NULL, 0, NULL, NULL));

    // finish queue
    check2(clFinish(queue));

    // read back to host memory from CL buffer
    clEnqueueReadBuffer(queue, bufferOUT, CL_TRUE, 0, global_work*sizeof(double),
                        lum, 0, 0, 0);

    clReleaseMemObject(bufferIN);
    clReleaseMemObject(bufferOUT);


    printf("%lf %lf\n", lum[0], lum[6]);

    printf("Time OpenCL: %ld,%ld sec\n", (end.tv_sec - start.tv_sec),
           (end.tv_usec - start.tv_usec));
    img_key = get_image_key(lum, vector_size/3);

    printf("Got Image key %lf\n", img_key);
    free(lum);
    return img_key;
}

double get_image_key(double* lum, unsigned long lum_size)
{
    double img_key =0;
    double buff = 0;
    unsigned long i;

    for(i = 0 ; i < lum_size; i++)
    {
        buff = buff + lum[i];
        //printf("%lf ", lum[i]);
    }
    printf("Got buff %lf \n", buff);

    img_key = buff/(double)lum_size;

    return img_key;
}

void apply_tone_mapping(unsigned char* raw_image, unsigned long vector_size,
                        cl_device_id device, cl_context context,
                        cl_command_queue queue)
{
    double lum = 0;
    double light_ajust = 0;
    unsigned long i;

    lum = get_luminance(raw_image, vector_size, device, context, queue);

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
