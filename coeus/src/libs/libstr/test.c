
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libstr.h"

#define test_main main

int test_main(int argc, char **argv)
{
	char * str_a = "/home/sganem/temp";
	char * str_suf = "/Makefile";

	printf("str_a length is:  %ld\n", strlen(str_a));
	printf("str_suf length is %ld\n", strlen(str_suf));
	printf("new str length is: %ld\n", strlen(str_a) + strlen(str_suf) + 1);

	char * new_str = (char*) malloc(sizeof(char) * (strlen(str_a) + strlen(str_suf) + 1));
	if (new_str == NULL)
	{
		printf("malloc failed \n");
	}
	
	libstr_str_append(27 , new_str, str_a, str_suf);
	printf("original str: %s\n", str_a);
	printf("suffix str: %s\n", str_suf);
	printf("combined str: %s\n", new_str);

	free(new_str);
}
