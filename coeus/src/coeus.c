
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

void help_generate_q(void);
unsigned int generate(int argc, char** argv);
static struct
{
    char *inarg;
    void (*print_help_q)(void);
    unsigned int (*callback)(int, char**);
} args_handler[] = { {"-generate" , help_generate_q, generate}};

unsigned int generate(int argc, char** argv)
{
    printf("here the generation magic will happen\n");
    return STATUS_OK;
}

/* function names that end with q mean they will quite the program on termination*/
void help_generate_q(void)
{
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    printf("environment test\n");
    //skipping the first arg
    argc--;
    argv++;
    if (argc == 0) exit(0);
    if (strcmp(argv[0], "-generate") == 0)
    {
        args_handler->callback(argc, argv);
    }
    

    return 0;
}
