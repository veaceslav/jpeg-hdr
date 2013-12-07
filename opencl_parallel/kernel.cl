#pragma OPENCL EXTENSION cl_khr_fp64: enable

__kernel void doubleInput(           __global unsigned char* buffer,
                                     __global double* result)
{
	// unique 1D thread id (0->max_threads)
    const double RED_WEIGHT = 0.2125;
    const double GREEN_WEIGHT = 0.7514;
    const double BLUE_WEIGHT = 0.0721;
    const double delta = 0.0001;
	int tid = get_global_id(0);
    int tid2 = tid*3;
    double buffval;

	result[tid] = log((buffer[tid2]* RED_WEIGHT) + (buffer[tid2+1]*GREEN_WEIGHT)
                  + (buffer[tid2+2]*BLUE_WEIGHT) + delta);

    //result = result + buffval;
    //result[tid] = buffval;

    //int local_index = get_local_id(0);

    // Load data into local memory

    /*
    if (tid < length) {
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
}
