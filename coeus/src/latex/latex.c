#include "latex.h"
#include <stdio.h>
#define STATUS_OK 0
#define STATUS_ERROR 1
typedef unsigned int uint; 

/*static fucntion declarations*/
static uint latex_generate_book_template(const char* path, const char* output_filename);

/*static global variables*/
static char* _BookDocumentclass = "\documentclass{book}\n";

static uint latex_generate_book_template(const char* path, const char* output_filename)
{
	;	
}

extern uint latex_generate_template(const char* path, const char* output_filename, TexDocType document)
{
	printf("calling this function from an external program");
	return STATUS_OK;
}


