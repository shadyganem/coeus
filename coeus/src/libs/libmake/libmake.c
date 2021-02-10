
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "libmake.h"

static int libmake_check_errno(int errsv);
static int libmake_internal_generate_C_obj(const char * path);

static struct 
{
	int (*gen_callback)(const char *path);
	enum GenericMakefile MF_type; 
} gen_handler[] = { {libmake_internal_generate_C_obj, MF_C_obj} }; 

static int gen_handler_num_of_el = sizeof(gen_handler)/sizeof(gen_handler[0]);

static int libmake_check_errno(int errsv)
{
	return 0;
}

static int libmake_internal_generate_C_obj(const char * path)
{
	//TODO - first check if the file already exists because it is not good to voerride Makefiles
    FILE* make_file;
    int status;
    make_file = fopen("Makefile", "w"); 
    if (make_file != NULL)
    {
	    printf("I AM I THE IF STATEMENT\n");
	fprintf(make_file, "CC = gcc\n");
	fprintf(make_file, "FLAGS = -Wall\n");
	fprintf(make_file, "SRC = $(wildcard *.c)\n");
	fprintf(make_file, "SRC := $(filter-out test.c, $(SRC))\n");
	fprintf(make_file, "OBJ = $(SRC:.c=.o)\n\n");
	fprintf(make_file, "all: $(OBJ)\n\n");
	fprintf(make_file, "%%.o: %%.c %%.h\n");
	fprintf(make_file, "\t$(CC) $(FLAGS) -c $<\n\n"); 
	fprintf(make_file, "clean:\n");
	fprintf(make_file, "\trm -f *.o\n\n");
	fprintf(make_file, "test: test.o $(OBJ)\n");
	fprintf(make_file, "\t$(CC) $(FLAGS) -o test test.o $(OBJ)\n\n");
	fprintf(make_file, "test.o: test.c\n");
	fprintf(make_file, "\t$(CC) -c test.c\n\n");
	fprintf(make_file, "clean_test:\n");
	fprintf(make_file, "\trm -f test\n");
	fprintf(make_file, "\trm -f *.o");
    }
    else
    {
	    printf("failed to open file\n");
	    status = 1;
    }
    return status;
}

extern int libmake_generate_template(enum GenericMakefile file_type, const char * path)
{
	printf("libmake has been called\n");
	int status;
	for (int i = 0; i < gen_handler_num_of_el; i++)
	{
		if (gen_handler[i].MF_type == file_type)
		{
			status = gen_handler[i].gen_callback(path);
		}
	}
	return status;
}
