#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include <unistd.h>
#include "latex/latex.h"


struct flag
{
    char* flag_str;
    bool flag_on;
    bool optional;
    bool arg;
};  

struct command 
{
    const char* command_name;
    int num_of_flags;
    struct flag* flags;
    int (* command_callback)(int argc, char ** argv, struct flag* command_flags, int num_of_flags);
};

void print_latex_help_and_die(void)
{
    printf("coeus manage LaTeX documentation");
    printf("Usage:\n");
    printf("coeus latex help/-h - print help on latex\n");
    exit(EXIT_SUCCESS);
}

int latex_new(int argc, char ** argv, struct flag * new_flags, int num_of_flags)
{
    LaTeXDocType doc;
    int flag_check = true;
    char * output_dir;
    //checking that all requried flags exit
    for (int i = 0; i < num_of_flags; i++)
    {
        if (new_flags[i].optional == false && new_flags[i].flag_on == false)
        {
            printf("please provide docment type after %s is required for command new\n", new_flags[i].flag_str);
            flag_check = false;
        }
    }
    if (flag_check == true)
    {
        for (int i = 0; i < num_of_flags; i ++)
        {
            if (new_flags[i].flag_on == true)
            {
                if (strcmp(new_flags[i].flag_str,"-d") == 0)
                {
                    for (int j = 0; j < argc; j++)
                    {
                        if (strcmp(argv[j], new_flags[i].flag_str) == 0)
                        {
                            if (j+1 < argc)
                                doc = latex_string_to_document_type(argv[j+1]);
                            //TODO: handle the case where input is missing 
                                
                        }
                    }
                }
                else if (strcmp(new_flags[i].flag_str,"-o") == 0)
                {
                    for (int j = 0; j < argc; j++)
                    {
                        if (strcmp(argv[j], new_flags[i].flag_str) == 0)
                        {
                            if (j+1 < argc)
                            output_dir = argv[j+1];
                            //TODO:handler the case whete input is missing 
                        }
                    }
                }
            }
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

int latex_find(int argc, char ** argv, struct flag * find_flags, int num_of_flags)
{
    printf("latex find\n");
    return 0;
}

void latex_callback_and_die(int argc, char** argv)
{
    int status;
    // command for latex "new", "find", "delete", "check", "help"
    // {flag_str, falg_on , optional, arg
    struct flag new_flags[] = {{"-o", false, true, true}, {"-d", false, false, true}, {"-h", false, true, false}};
    struct flag find_flags[] = {{"-h", false, true, false}};
    // { command_name, flag_array )}
    // help is not includes here 
    struct command latex_commands[] = { {"new" ,sizeof(new_flags)/sizeof(new_flags[0]), new_flags, latex_new},
                                        {"find",sizeof(find_flags)/sizeof(find_flags[0]), find_flags, latex_find}};
    
    int num_of_commands = sizeof(latex_commands)/sizeof(latex_commands[0]);

    if (argc == 0) print_latex_help_and_die();
    if (strcmp(argv[0], "help") == 0) print_latex_help_and_die();
    if (strcmp(argv[0], "-h") == 0) print_latex_help_and_die();
    
    for (int i = 0; i < num_of_commands; i++)
    {
        if (strcmp(latex_commands[i].command_name, argv[0]) == 0)
        {
            //finding which flags are on and which are not 
            for (int j = 0; j < latex_commands[i].num_of_flags; j++)
            {
                for (int k = 1; k < argc; k++)
                {
                    if (strcmp(argv[k], latex_commands[i].flags[j].flag_str) == 0)
                    {
                        latex_commands[i].flags[j].flag_on = true;
                    }
                }
            }
            status = latex_commands[i].command_callback(--argc, ++argv,latex_commands[i].flags, latex_commands[i].num_of_flags);
            //brek from the loop
            break;
        }
    } 
    if (status == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("LaTeX ERROR: something went wrong\n");
        exit(EXIT_SUCCESS);
    }
}

void print_help_and_die(void)
{
    printf("coeus is a documentation assistance tool\n");
    printf("Usage:\n");
    printf("coeus -h for help\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    //skipping the first arg
    argc--;
    argv++;
    if (argc == 0) print_help_and_die();
    if (strcmp(argv[0], "help") == 0) print_help_and_die();
    if (strcmp(argv[0], "-h") == 0) print_help_and_die();
    if (strcmp(argv[0], "latex") == 0) latex_callback_and_die(--argc, ++argv);
    printf("Wrong Input\n");
    print_help_and_die();
    return 0;
}
