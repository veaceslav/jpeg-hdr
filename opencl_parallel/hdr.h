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
