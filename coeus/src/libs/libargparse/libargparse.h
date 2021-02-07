#ifndef _LIBARGPARSE_H_
#define _LIBARGPARSE_H_
#include <stdbool.h>
struct flag
{
    char* f_str;
    bool f_on;
    bool f_opt;
    bool f_arg_req;
    const char* f_arg;
};  

struct command 
{
    const char* c_name;
    int c_num_of_flags;
    struct flag* c_flags;
    int (* c_callback)(int flagc, struct flag* flagv);
};

struct context 
{
    const char* context_name;
    int num_of_commands;
    struct command* commands;
};

int is_flag_on(int flagc, struct flag * flagv, const char * flag_str);

//TODO define a new library for parsing argument
//TODO treat argument as a token stream
//TODO define statemachine to determain grammer
//TODO have fun

struct argparser
{
    char* argparser_name;
};

struct argparser* argparser_init(int argc, char **argv);

#endif
