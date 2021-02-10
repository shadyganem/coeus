
#include <stdio.h>
#include <string.h>
#include "libstr.h"

extern int libstr_str_append(int new_str_len, char * new_str, const char *original_str, const char *suffix_str)
{
	int original_str_len = strlen(original_str);
	int suffix_str_len = strlen(suffix_str);

	//first we will check that the target str has enough space to take the suffix_str
	if (original_str_len + suffix_str_len + 1 < new_str_len)
	{
		return libstr_str_appeand_err;
	}

	for (int i = 0; i < original_str_len; i++)
	{
		new_str[i] = original_str[i];

	}

	for (int i = 0; i < suffix_str_len; i++)
	{

		new_str[original_str_len + i] = suffix_str[i];
	}

	new_str[original_str_len + suffix_str_len] = '\0';
	return libstr_status_ok;
}
