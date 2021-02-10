#include <stdio.h>
#include <errno.h>
#include "libsyserr.h"

extern int libsyserr_check_errno(int errsv)
{
    switch (errsv)
    {
        case 0:
            return 0;
        case EACCES: 
            printf("ERROR: Search permission is denied on a component of the path prefix, or write permission is denied on the parent directory of the directory to be created\n");
            return 1;
        case EEXIST:
            printf("ERROR: The named file exists\n");
            return 1;
        case ELOOP:
           printf("ERROR: A loop exists in symbolic links encountered during resolution of the path argument\n");
           return 1;
        case EMLINK:
           printf("ERROR: The link count of the parent directory would exceed {LINK_MAX}\n");
           return 1;
        case ENAMETOOLONG:
           printf("ERROR: The length of the path argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}\n");
           return 1;
        case ENOENT:
           printf("ERROR: A component of the path prefix specified by path does not name an existing directory or path is an empty string\n");
           return 1;
        case ENOSPC:
           printf("ERROR: The file system does not contain enough space to hold the contents of the new directory or to extend the parent directory of the new directory\n");
           return 1;
        case ENOTDIR:
           printf("ERROR: A component of the path prefix is not a directory\n");
           return 1;
        case EROFS:
           printf("ERROR: The parent directory resides on a read-only file system\n");
           return 1;
        default:
           printf("ERROR: undefined error errsv = %d\n", errsv);
           return 1;
    }
    return 0;
}
