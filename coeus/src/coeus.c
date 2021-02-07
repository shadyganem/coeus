#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include <unistd.h>
#include <limits.h>
#include "libs/liblatex/liblatex.h"
#include "libs/libargparse/libargparse.h"


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
    char title[100];
    LaTeXDocType doc;
    char * current_path;
    const char * path;

    for (int i = 0; i < flagc; i++)
    {
        if (flagv[i].f_on == true)
        {
            if (strcmp(flagv[i].f_str, "-d") == 0)
            {
                doc = liblatex_string_to_document_type(flagv[i].f_arg);
                if (doc == latex_undefined)
                {
                    printf("undefined LaTeX Document\n");
                    return 1;
                }
            }
            else if (strcmp(flagv[i].f_str, "-o") == 0)
            {
                current_path = (char*) malloc(PATH_MAX * sizeof (char));
                if (current_path == NULL)
                { 
                    printf("malloc failed at latex_new_callback line: %d\n", __LINE__);
                    return 1;
                }
                path = flagv[i].f_arg;
                printf("path = %s\n", path);
                if (getcwd(current_path, PATH_MAX) != NULL)
                {
                    if(chdir(path) != 0)
                    {
                        printf("debug print chdir failed");
                        free(current_path);
                        return 1;
                    }
                }
                else 
                {
                    printf("debug print getcwd faild\n");

                    free(current_path);
                    return 1;
                }
            }
        }
    }

    printf("Enter Document title: ");
    scanf("%s", title);
    if (liblatex_generate_template(title, doc) != 0)
    {
        return 1;
    }
   
    if (is_flag_on(flagc, flagv, "-o") == 0) 
    {
        if(chdir(current_path) != 0)
        {
            printf("debug print chdir failed on the second attepmt\n");
            free(current_path);
            return 1;
        }
    }
    free(current_path);
    return 0;
}

void print_help_and_die(void)
{
    printf("coeus is a documentation assistance tool\n");
    printf("Usage:\n");
    printf("coeus help for printing help\n");
    printf("coeus latex of LaTeX related commands\n");
    exit(EXIT_SUCCESS);
}

bool flags_ok(int flagc, struct flag* flagv, int argc, char** argv)
{
    //assuming argument start from argv[0]
    //need to check porinter are ok 

    //first we will check that the required flags are here
    bool flag_found = false;
    for (int i = 0; i < flagc; i++)
    {
        if (flagv[i].f_opt == false)
        {
            for (int j = 0; j < argc; j++)
            {
                if (strcmp(argv[j], flagv[i].f_str) == 0)
                {
                    flag_found = true;
                    break;
                }
            }
            if (flag_found == false)
            { 
                for (int j = 0; j < flagc; j++)
                {
                    if (flagv[j].f_opt == false)
                        printf("flag %s is required\n", flagv[j].f_str);
                }
                return false;
            }
        }
    }
    // now that we know that all the required input is here
    for (int i = 0; i < argc; i++)
    {
        for (int j = 0; j < flagc; j++)
        {
            if (strcmp(flagv[j].f_str, argv[i]) == 0)
            {
                flagv[j].f_on = true;
                if (flagv[j].f_arg_req == true)
                {
                    if (i == argc - 1)
                    {
                        return false;
                    }
                    else
                    {
                        flagv[j].f_arg = argv[++i];
                        break;
                    }
                }
            }
        }
    }
    return true;
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
