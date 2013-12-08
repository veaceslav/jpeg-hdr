#include "openclwrap.h"

///
/// Error codes
///
const char* print_cl_errstring(cl_int err) {
    switch (err) {
        case CL_SUCCESS:                          return  "Success!";
        case CL_DEVICE_NOT_FOUND:                 return  "Device not found.";
        case CL_DEVICE_NOT_AVAILABLE:             return  "Device not available";
        case CL_COMPILER_NOT_AVAILABLE:           return  "Compiler not available";
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:    return  "Memory object allocation failure";
        case CL_OUT_OF_RESOURCES:                 return  "Out of resources";
        case CL_OUT_OF_HOST_MEMORY:               return  "Out of host memory";
        case CL_PROFILING_INFO_NOT_AVAILABLE:     return  "Profiling information not available";
        case CL_MEM_COPY_OVERLAP:                 return  "Memory copy overlap";
        case CL_IMAGE_FORMAT_MISMATCH:            return  "Image format mismatch";
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:       return  "Image format not supported";
        case CL_BUILD_PROGRAM_FAILURE:            return  "Program build failure";
        case CL_MAP_FAILURE:                      return  "Map failure";
        case CL_INVALID_VALUE:                    return  "Invalid value";
        case CL_INVALID_DEVICE_TYPE:              return  "Invalid device type";
        case CL_INVALID_PLATFORM:                 return  "Invalid platform";
        case CL_INVALID_DEVICE:                   return  "Invalid device";
        case CL_INVALID_CONTEXT:                  return  "Invalid context";
        case CL_INVALID_QUEUE_PROPERTIES:         return  "Invalid queue properties";
        case CL_INVALID_COMMAND_QUEUE:            return  "Invalid command queue";
        case CL_INVALID_HOST_PTR:                 return  "Invalid host pointer";
        case CL_INVALID_MEM_OBJECT:               return  "Invalid memory object";
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:  return  "Invalid image format descriptor";
        case CL_INVALID_IMAGE_SIZE:               return  "Invalid image size";
        case CL_INVALID_SAMPLER:                  return  "Invalid sampler";
        case CL_INVALID_BINARY:                   return  "Invalid binary";
        case CL_INVALID_BUILD_OPTIONS:            return  "Invalid build options";
        case CL_INVALID_PROGRAM:                  return  "Invalid program";
        case CL_INVALID_PROGRAM_EXECUTABLE:       return  "Invalid program executable";
        case CL_INVALID_KERNEL_NAME:              return  "Invalid kernel name";
        case CL_INVALID_KERNEL_DEFINITION:        return  "Invalid kernel definition";
        case CL_INVALID_KERNEL:                   return  "Invalid kernel";
        case CL_INVALID_ARG_INDEX:                return  "Invalid argument index";
        case CL_INVALID_ARG_VALUE:                return  "Invalid argument value";
        case CL_INVALID_ARG_SIZE:                 return  "Invalid argument size";
        case CL_INVALID_KERNEL_ARGS:              return  "Invalid kernel arguments";
        case CL_INVALID_WORK_DIMENSION:           return  "Invalid work dimension";
        case CL_INVALID_WORK_GROUP_SIZE:          return  "Invalid work group size";
        case CL_INVALID_WORK_ITEM_SIZE:           return  "Invalid work item size";
        case CL_INVALID_GLOBAL_OFFSET:            return  "Invalid global offset";
        case CL_INVALID_EVENT_WAIT_LIST:          return  "Invalid event wait list";
        case CL_INVALID_EVENT:                    return  "Invalid event";
        case CL_INVALID_OPERATION:                return  "Invalid operation";
        case CL_INVALID_GL_OBJECT:                return  "Invalid OpenGL object";
        case CL_INVALID_BUFFER_SIZE:              return  "Invalid buffer size";
        case CL_INVALID_MIP_LEVEL:                return  "Invalid mip-map level";
        default:                                  return  "Unknown";
    }
}


///
/// ERROR LOG
///
void errorLog(cl_program program, cl_device_id device)
{
    char* build_log;
    size_t log_size;

    // First call to know the proper size
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    build_log = malloc((log_size+1)*sizeof(char));

    // Second call to get the log
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL);
    build_log[log_size] = '\0';
    printf("%s",build_log);
}

///
/// Error check 1
///
int check(int cuerr, cl_program program, cl_device_id device){

    if(cuerr != CL_SUCCESS)
    {
        printf("\n%s\n", print_cl_errstring(cuerr));
        errorLog(program, device);
        return 1;
    }

    return 0;
}

///
/// Error check 1
///
int check2(int cuerr){

    if(cuerr != CL_SUCCESS)
    {
        printf("\n%s\n", print_cl_errstring(cuerr));
        return 1;
    }

    return 0;
}

cl_device_id get_device()
{

    char tempString[MAX_STR_SIZE];      // store platform info
    cl_platform_id platform[MAX_PLATFORMS]; // Platform { CPU, GPU, FPGA }
    cl_device_id devices[MAX_DEVICE_COUNT]; // device list
    cl_uint totalDevices=0;         // num devices
    cl_uint platformDevices=0;  // platform devices
    cl_uint currentDevice=0;    // for selection of device to run on

    size_t global_work_size;    // work size
    cl_uint num_platforms;      // num platforms

    int i,j;

    // retrieve platforms
    clGetPlatformIDs(MAX_PLATFORMS,platform,&num_platforms);
    if(num_platforms==0){
        printf("No platform found\n");
        exit(-1);
    }
    else
        printf("Found %d platforms\n\n",num_platforms);

    // find available platforms
    for( i=0;i<num_platforms;i++)
    {
        clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, sizeof(char)*MAX_STR_SIZE, tempString, NULL);
        printf("[%c] %s\n",(char)(i+(int)'A'),tempString);

        clGetPlatformInfo(platform[i], CL_PLATFORM_VENDOR, sizeof(char)*MAX_STR_SIZE, tempString, NULL);
        printf("- Platform Vendor %s\n",tempString);

        clGetPlatformInfo(platform[i], CL_PLATFORM_VERSION, sizeof(char)*MAX_STR_SIZE, tempString, NULL);
        printf("- Platform Version %s\n",tempString);

        clGetDeviceIDs(platform[i],CL_DEVICE_TYPE_ALL,MAX_DEVICE_COUNT,devices+totalDevices,&platformDevices);
        totalDevices+=platformDevices;
        printf("- Devices available : %d\n\n",platformDevices);
    }

    // print out available devices
    for(j=0;j<totalDevices;j++)
    {
        clGetDeviceInfo(devices[j],CL_DEVICE_NAME,sizeof(char)*MAX_STR_SIZE,tempString,NULL);
        printf("[%d]%s \n",j,tempString);
    }

    // Select device to run on
    printf("\nSelect device to run on :");

    // force flush of platform info
    fflush(stdout);

    // selection of device
    //scanf("%d",&currentDevice);
    currentDevice = 0;
    if((currentDevice<0) || (currentDevice>totalDevices)){
        printf("\nSelected device does not exist. Exiting...\n");
        exit(-1);
    }

    // get device info
    clGetDeviceInfo(devices[currentDevice], CL_DEVICE_NAME,
                    sizeof(char)*MAX_STR_SIZE, tempString, NULL);

    // = device=devices[currentDevice];
    printf("\nRunning on %s \n",tempString);

    return devices[currentDevice];
}

cl_kernel get_kernel(char* filename, char* kernel_name,
                     cl_device_id device, cl_context context)
{
    long f_size;
    char* code;
    size_t code_s, result;
    cl_kernel kernel;
    cl_program program;     // program
    cl_int err;         // for error checking

    FILE* fp = fopen(filename, "r");
    if(!fp)
    {
        printf("Cannt open file, exiting\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp); /* This returns 29696, but file is 85 bytes */
    fseek(fp, 0, SEEK_SET);
    code_s = sizeof(char) * f_size;
    code = calloc(f_size+1, sizeof(char));
    result = fread(code, 1, f_size, fp); /* This returns 1045, it should be the same as f_size */

    const char* source = code;

    //printf("am scris programul pentru kernel\n");
    program = clCreateProgramWithSource(context, 1, &source, NULL, &err);
    check(err,program,device);
    //printf("Pass");
    check2(clBuildProgram(program, 1, &device, NULL, NULL, NULL));

    // kernels
    kernel = clCreateKernel(program, kernel_name, &err);
    check(err, program, device);

    return kernel;
}
