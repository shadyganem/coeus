
#include <string.h>
#include "libargparse.h"

int is_flag_on(int flagc, struct flag* flagv, const char * in_f_str)
{
    if (in_f_str == NULL) return 1;
    if (flagv == NULL) return 1;
    for (int i = 0; i < flagc; i++)
    {
        if (strcmp(flagv[i].f_str, in_f_str) == 0)
        {
            return flagv[i].f_on == true ? 0 : 1;
        } 
    }
    return 1;
}
