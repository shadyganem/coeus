#include "latex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/* defines
 * typdefs
 * static globals
 * globals
 * fucntion decelartions
 * function impelmentation
 */

enum STATUS
{
    STATUS_OK,
    STATUS_BAD_FOLDER,
    STATUS_BAD_FILE,
    STATUS_BAD_MEM_ALLOC,
    STATUS_BAD_DOC_TYPE
};

static struct 
{
    enum STATUS status;
    const char * status_str;
} status_handler[] = { {STATUS_OK,            "STATUS_OK"             },
                       {STATUS_BAD_FOLDER,    "STATUS_BAD_FOLDER"     },
                       {STATUS_BAD_FILE,      "STATUS_BAD_FILE"       },
                       {STATUS_BAD_MEM_ALLOC, "STATUS_BAD_MEM_ALLOC"  },
                       {STATUS_BAD_DOC_TYPE,  "STATUS_BAD_DOC_TYPE" } };

static struct
{
    LaTeXDocType document;
    const char * latex_doc_str;
} document_type_handler[] = { {latex_article, "article" },
                              {latex_report,  "report"  },
                              {latex_book,    "book"    },
                              {latex_letter,  "letter"  },
                              {latex_slides,  "slides"  },
                              {latex_beamer,  "beamer"  } };

/*static fucntions declarations*/
static void latex_append_document_environment(FILE* latex_file, const char* title);
static char* latex_malloc_append_path(const char* str1, const char* str2);
static void latex_str_replace(char* str, char ch1, char ch2);

static char* latex_malloc_append_path(const char* str1, const char* str2)
{
    int str1_len = 0;
    int str2_len = 0;
    int new_str_len = 0;
    char * new_str;
    str1_len = strlen(str1);
    str2_len = strlen(str2);
    new_str_len = str1_len + str2_len + 2;
    new_str = (char*) malloc(new_str_len * sizeof (char));
    if(new_str == NULL)
        return NULL;
    for (int i = 0; i < str1_len; i++)
    {
        new_str[i] = str1[i];
    }
    new_str[str1_len++] = '/';
    for (int i = 0; i < str2_len; i++)
    {
        new_str[str1_len + i] = str2[i];
    }
    new_str[str1_len + str2_len] = '\0';
    return new_str;
}

static void latex_str_replace(char* str,char ch1, char ch2)
{
    printf("original str %s\n", str);
    int str_len = 0;
    str_len = strlen(str);
    for (int i = 0; i < str_len; i++)
    {
        if (str[i] == ch1)
        {
            str[i] = ch2;
        }
    }
    printf("modified str %s\n", str);
}

static void latex_append_document_environment(FILE* latex_file, const char* title)
{
    int title_len = strlen(title);
    char * title_copy = (char *) malloc(title_len * sizeof (char)); 
    latex_str_replace(strcpy(title_copy, title), '_', ' '); 
    fprintf(latex_file, "\\title{%s}\n", title_copy);
    free(title_copy);
    fprintf(latex_file, "\\author{Johnny English}\n\n");
    fprintf(latex_file, "\\begin{document}\n");
    fprintf(latex_file, "\\maketitle\n");
    fprintf(latex_file, "%%Content goes here\n");
    fprintf(latex_file, "\\end{document}\n");
}

extern unsigned int latex_generate_template(const char* path, const char* output_filename, LaTeXDocType document)
{
    enum STATUS status = STATUS_OK;
    int check;
    check = mkdir(output_filename, 0777);
    if (check == 0)
    {
        FILE * latex_file;
        char* filename = latex_malloc_append_path(output_filename, "main.tex");
        if (filename != NULL)
        {
            latex_file = fopen(filename, "w");
            if (latex_file != NULL)
            {
                fprintf(latex_file, "\\documentclass{%s}\n\n", latex_document_type_to_string(document));
                latex_append_document_environment(latex_file, output_filename);
                fclose(latex_file);
            }
            else
            {
                status = STATUS_BAD_FILE;
            }
            free(filename);
        }
        else
        {
            status = STATUS_BAD_MEM_ALLOC;
        }
    }
    else
    {
        status = STATUS_BAD_FOLDER;
    }
	return status;
}

extern const char* latex_document_type_to_string(LaTeXDocType doc_type)
{
    static const char* wrong_type_str = "document type not found ";
    int document_type_handler_num_of_el =  sizeof(document_type_handler)/sizeof(document_type_handler[0]);
    for (int i = 0; i < document_type_handler_num_of_el; i++)
    {
        if (document_type_handler[i].document == doc_type)
        {
            return document_type_handler[i].latex_doc_str;
        }
    }
    return wrong_type_str;
}

extern LaTeXDocType latex_string_to_document_type(const char* doc_type_str)
{
    int document_type_handler_num_of_el =  sizeof(document_type_handler)/sizeof(document_type_handler[0]);
    for (int i = 0; i < document_type_handler_num_of_el; i++)
    {
        if (strcmp(document_type_handler[i].latex_doc_str, doc_type_str) == 0)
        {
            return document_type_handler[i].document;
        }
    }
    return STATUS_BAD_DOC_TYPE;
}

extern const char* latex_status_to_string(int status)
{
    static const char* status_not_defined_str = "STATUS NOT DEFINED";
    int status_handler_num_of_el =  sizeof(status_handler)/sizeof(status_handler[0]);
    for (int i = 0; i < status_handler_num_of_el; i++)
    {
        if (status_handler[i].status == status)
        {
            return status_handler[i].status_str;
        }
    }
    return status_not_defined_str;
}
