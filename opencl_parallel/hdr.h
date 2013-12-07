#include "openclwrap.h"
#define RED_WEIGHT 0.2125
#define GREEN_WEIGHT 0.7514
#define BLUE_WEIGHT 0.0721

#define DELTA 0.0001
#define ALPHA 3.5
#define LWHITE 235

double get_luminance(unsigned char* raw_image, unsigned long vector_size,
                     cl_device_id device, cl_context context,
                     cl_command_queue queue);

double get_image_key(double* lum, unsigned long lum_size);

void apply_tone_mapping(unsigned char* raw_image, unsigned long vector_size,
                        cl_device_id device, cl_context context,
                        cl_command_queue queue);

double range_fix(double value);

//result = result + buffval;
//result[tid] = buffval;

//int local_index = get_local_id(0);

// Load data into local memory

/*
 i f* (tid < length) {
     scratch[local_index] = buffval;
     } else {
         // Infinity is the identity element for the min operation
         scratch[local_index] = INFINITY;
         }
         barrier(CLK_LOCAL_MEM_FENCE);
         for(int offset = 1; offset < get_local_size(0); offset <<= 1) {
             int mask = (offset << 1) - 1;
             if ((local_index & mask) == 0) {
                 float other = scratch[local_index + offset];
                 float mine = scratch[local_index];
                 scratch[local_index] = (mine < other) ? mine : other;
                 }
                 barrier(CLK_LOCAL_MEM_FENCE);
                 }
                 if (local_index == 0) {
                     result[get_group_id(0)] = scratch[0];
                     }
                     */
