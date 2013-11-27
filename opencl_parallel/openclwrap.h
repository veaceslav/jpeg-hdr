#ifndef OPENCLWRAP_H
#define OPENCLWRAP_H

#include <CL/cl.h>
#include <stdio.h>


// App settings
#define MAX_STR_SIZE        512
#define MAX_PLATFORMS       8
#define MAX_DEVICE_COUNT    16
#define NR_ELEMENTS     16

// error codes
const char* print_cl_errstring(cl_int err);

// compile log, given by OpenCL env
void errorLog(cl_program program,cl_device_id device);

// check code compilation against device
int check(int cuerr, cl_program program, cl_device_id device);

// check given return code
int check2(int cuerr);

cl_device_id get_device();

cl_kernel get_kernel(char* filename, char* kernel_name,
                     cl_device_id device, cl_context context);


#endif
