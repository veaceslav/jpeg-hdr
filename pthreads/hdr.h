
#define RED_WEIGHT 0.2125
#define GREEN_WEIGHT 0.7514
#define BLUE_WEIGHT 0.0721

#define DELTA 0.0001
#define ALPHA 3.5
#define LWHITE 235

typedef struct thrdata {
    unsigned char* array;
    int begin_index;
    int size;
    int tindex;
    double img_key_partial;
} threadData;

void* stage1(void* tid);

void* stage2(void* tid);

double get_luminance(unsigned char* raw_image, unsigned long vector_size);

double get_image_key(float* lum, unsigned long lum_size);

void apply_tone_mapping(unsigned char* raw_image, unsigned long vector_size);

double range_fix(double value);
