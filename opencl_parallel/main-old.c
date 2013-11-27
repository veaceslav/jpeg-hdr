#include "openclwrap.h"


///
/// MAIN
///
int main(int argc,char** argv)
{
	char tempString[MAX_STR_SIZE];		// store platform info

	cl_device_id device;		// Device { GPU_ID }
	cl_context context;		// Context
	cl_command_queue queue;		// Queue
	cl_int err;			// for error checking

	cl_program program;		// program
	cl_kernel kernel;

	cl_mem bufferIN;	// data IN
	cl_mem bufferOUT;	// data OUT

	float* inputData;		// input data
	float* outputData;		// output data

	size_t global_work_size;	// work size

	int i,j;

    device = get_device();

	// create context & add 1 queue for 1 device
	context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
	queue 	= clCreateCommandQueue(context, device, 0, NULL);

	// allocate memory - heap, non-OpenCL
	inputData = malloc(NR_ELEMENTS*sizeof(float));
	outputData = malloc(NR_ELEMENTS*sizeof(float));

	if((!inputData) || (!outputData))
		exit(-1);

	// assign start values
	for(i = 0; i<NR_ELEMENTS; i++)
		inputData[i] = i + 0.15;

	// allocate memory INPUT - device RAM/VRAM, OpenCL handled
	bufferIN = clCreateBuffer(context, CL_MEM_READ_ONLY, NR_ELEMENTS *sizeof(float), NULL, NULL);

	// allocate memory OUTPUT - device RAM/VRAM, OpenCL hendled
	bufferOUT= clCreateBuffer(context, CL_MEM_WRITE_ONLY, NR_ELEMENTS *sizeof(float), NULL, NULL);

	// write data to specified device address, OpenCL handled
	clEnqueueWriteBuffer(queue, bufferIN, 1, 0, NR_ELEMENTS *sizeof(float), inputData,0,0,0);

    kernel = get_kernel("../kernel.cl", "doubleInput", device, context);
	// pass args, execute OPENCL kernels
	global_work_size = NR_ELEMENTS;

	check2(clSetKernelArg(kernel, 0, sizeof(bufferIN),	(void*)&bufferIN));
	check2(clSetKernelArg(kernel, 1, sizeof(bufferOUT),	(void*)&bufferOUT));

	size_t global_work = NR_ELEMENTS;

	// start first kernel
	check2(clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work, NULL, 0, NULL, NULL));

	// finish queue
	check2(clFinish(queue));

	// read back to host memory from CL buffer
	clEnqueueReadBuffer(queue, bufferOUT, CL_TRUE, 0, NR_ELEMENTS*sizeof(float),
				outputData, 0, 0, 0);

 	// output data
	for(i=0; i<NR_ELEMENTS; i++)
		printf("%f\n",outputData[i]);

	// all ok
	return 0;
}
