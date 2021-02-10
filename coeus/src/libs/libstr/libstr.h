#ifndef _LIBSTR_H_
#define _LIBSTR_H_

enum libstr_errors
{
	libstr_status_ok,
	libstr_str_appeand_err
};

extern int libstr_str_append(int new_str_len, char * new_str, const char *original_str, const char *suffix_str);
#endif
