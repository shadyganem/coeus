
#include <stdio.h>
#include "libmake.h"

#define test_main main


int test_main(int argc, char** argv)
{
    printf("test program for libmake\n");

    libmake_generate_template(MF_C_obj, "");

    return 0;
}

