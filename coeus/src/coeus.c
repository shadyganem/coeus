#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include <unistd.h>
#include "latex/latex.h"

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

int latex_help_callback(int flagc, struct flag* flagv)
{
    //help_flags is a NULL pointer
    printf("coeus helps you manage and automate LaTeX documentation");
    printf("Usage:\n");
    printf("coeus latex help/-h - print help on latex\n");
    return 0;
}

int latex_new_callback(int flagc, struct flag* flagv)
{
    //LaTeXDocType doc;
    //int flag_check = true;
    //char * output_dir;
    //checking that all requried flags exit
    //for (int i = 0; i < flagc; i++)
    //{
    //    if (flagv[i].f_opt == false && flagv[i].f_on == false)
    //    {
    //        printf("please provide docment type after %s is required for command new\n", flagv[i].f_str);
    //        flag_check = false;
    //    }
    //}
    return 0;
}

void print_help_and_die(void)
{
    printf("coeus is a documentation assistance tool\n");
    printf("Usage:\n");
    printf("coeus -h for help\n");
    exit(EXIT_SUCCESS);
}

bool flags_ok(int flagc, struct flag* flagv, int argc, char** argv)
{
    //assuming argument start from argv[0]
}

int main(int argc, char** argv)
{
    //each context has it's commands {context_name, num_of_commands, commands[]}
    //each command has a callback function and flags {command_name, num_of_flags, flags[], (*c_callback)}
    //each flag has {f_str, f_on, f_opt, f_arg_req, f_arg} 
    struct flag latex_new_flags[] = {{"-d", false, false, true, NULL}, 
                                    {"-o", false, true, true, NULL}};

    struct command latex_commands[] = {{"new", sizeof(latex_new_flags)/sizeof(latex_new_flags[0]), latex_new_flags, latex_new_callback},
                                       {"help", 0, NULL , latex_help_callback}};

    struct context contexts[] = {{"latex",sizeof(latex_commands)/sizeof(latex_commands[0]), latex_commands}};
    int num_of_contexts = sizeof(contexts)/sizeof(contexts[0]);

    //declaring branching flags
    int context_found_flag = false;
    int command_found_flag = false;

    int context_index = 0;
    int command_index = 0;

    //skipping the first arg
    argc--;
    argv++;
    if (argc == 0) exit(EXIT_SUCCESS); //calling without context is a shame
    if (strcmp(argv[0], "help") == 0) print_help_and_die();
    if (strcmp(argv[0], "-h") == 0) print_help_and_die();

    for (int i = 0; i < num_of_contexts; i++)
    {
        if (strcmp(argv[0], contexts[i].context_name) == 0) 
        {
            context_found_flag = true;
            context_index = i;
        }
    } 

    //skipping the second arg
    argc--;
    argv++;

    if (context_found_flag)
    {
        printf("context %s\n", contexts[context_index].context_name);
        if (argc != 0 && contexts[context_index].commands != NULL) //never dereference a pointer without checking first
        {
            for (int i = 0; i < contexts[context_index].num_of_commands; i++)
            {
                if (strcmp((contexts[context_index]).commands[i].c_name, argv[0]) == 0) //command found
                {
                    command_found_flag = true;
                    command_index = i;
                }
            }
        }
        //skipping the third arg
        argc--;
        argv++;
        struct command * current_command = &contexts[context_index].commands[command_index];
        int command_status = 1;
        if (command_found_flag) //handle command
        {
            if (argc != 0 &&  current_command != NULL)
            {
                printf("command %s\n", contexts[context_index].commands[command_index].c_name);
                if(flags_ok(current_command->c_num_of_flags, current_command->c_flags, argc, argv))
                {
                    command_status = current_command->c_callback(current_command->c_num_of_flags, current_command->c_flags);
                }
            }
            else
            {
                printf("Wrong input\n");
                printf("Type coeus %s help for more info\n", contexts[context_index].context_name);
            }

            if (command_status != 0)
            {
                printf("Command %s %s Had Failed\n", contexts[context_index].context_name, current_command->c_name);
            }
        }
        else
        {
            printf("Wrong input\n");
            printf("Type coeus %s help for more info\n", contexts[context_index].context_name);
        }
    }
    else
    {
        printf("Wrong input\n");
        printf("Type \"coeus help\" for more info\n");
    }
    return 0;
}
