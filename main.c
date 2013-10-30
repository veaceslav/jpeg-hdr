#include <stdio.h>
#include "jpegapi.h"

int main(int argc, char** argv)
{
    if(argc < 5)
    {
        printf( "Usage: ./hdr img1.jpg img2.jpg img3.jpg imgfinal.jpg\n");
        return 1;
    }

    return 0;
}
