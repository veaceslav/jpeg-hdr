#pragma OPENCL EXTENSION cl_khr_fp64: enable
__kernel void doubleInput(__global unsigned char* buffer, __global double* result)
{
    const double RED_WEIGHT = 0.2125;
    const double GREEN_WEIGHT = 0.7514;
    const double BLUE_WEIGHT = 0.0721;
    const double delta = 0.0001;
	int tid = get_global_id(0);
    int tid2 = tid*3;

	result[tid] = log((buffer[tid2]* RED_WEIGHT) + (buffer[tid2+1]*GREEN_WEIGHT)
                  + (buffer[tid2+2]*BLUE_WEIGHT) + delta);

}

__kernel void adjust(__global unsigned char* in, __global double* img_key, __global unsigned char* out)
{
    int tid = get_global_id(0);
    double LWHITE = 235.0;
    double tmp_pixel = (double)in[tid] * img_key[0];
    tmp_pixel *= (tmp_pixel*(1+ tmp_pixel/(LWHITE*LWHITE)))/(1 + tmp_pixel);
    tmp_pixel = tmp_pixel > 255.0 ? 255 : tmp_pixel;
    out[tid] = (unsigned char)tmp_pixel;
}
