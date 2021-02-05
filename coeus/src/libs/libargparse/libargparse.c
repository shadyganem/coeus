
#include <string.h>
#include "libargparse.h"

int is_flag_on(int flagc, struct flag* flagv, const char * in_f_str)
{
    for (int i = 0; i < flagc; i++)
    {
        if (strcmp(flagv[i].f_str, in_f_str) == 0)
        {
            return flagv[i].f_on == true ? 0 : 1;
        } 
    }
    return 1;
}
