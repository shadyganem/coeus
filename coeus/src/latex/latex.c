#include "latex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

enum STATUS
{
    STATUS_OK,
    STATUS_BAD_FOLDER,
    STATUS_BAD_FILE,
    STATUS_BAD_MEM_ALLOC,
    STATUS_BAD_DOC_TYPE
};

/*static fucntions declarations*/
static unsigned int latex_generate_article_template(const char* path, const char* output_filename);
static unsigned int latex_generate_report_template(const char* path, const char* output_filename);
static unsigned int latex_generate_book_template(const char* path, const char* output_filename);
static unsigned int latex_generate_letter_template(const char* path, const char* output_filename);
static unsigned int latex_generate_slides_template(const char* path, const char* output_filename);
static unsigned int latex_generate_beamer_template(const char* path, const char* output_filename);
static void latex_append_document_environment(FILE* latex_file);

//static unsigned int latex_create_folder_by_name(const char* folder_name);
//static unsigned int latex_create_folder_by_name(const char* path)
//{
//    enum STATUS status;
//    status = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//    return status;
//}

static char * latex_malloc_append_path(const char* str1, const char* str2)
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

static void latex_append_document_environment(FILE* latex_file)
{
    fprintf(latex_file, "\\title{Template}\n");
    fprintf(latex_file, "\\author{Johnny English}\n\n");
    fprintf(latex_file, "\\begin{document}\n");
    fprintf(latex_file, "\\maketitle\n");
    fprintf(latex_file, "%%Content goes here\n");
    fprintf(latex_file, "\\end{document}\n");
}


static unsigned int latex_generate_article_template(const char* path, const char* output_filename)
{
    enum STATUS status = STATUS_OK;
    FILE * latex_file;
    latex_file = fopen("main.tex", "w");
    if (latex_file != NULL)
    {
        fprintf(latex_file, "\\documentclass{article}\n\n");
        latex_append_document_environment(latex_file);
        fclose(latex_file);
    }
    else
    {
        status = STATUS_BAD_FILE;
    }
    return status; 
}

static unsigned int latex_generate_report_template(const char* path, const char* output_filename)
{
    enum STATUS status = STATUS_OK;
    FILE * latex_file;
    latex_file = fopen("main.tex", "w");
    if (latex_file != NULL)
    {
        fprintf(latex_file, "\\documentclass{report}\n\n");
        latex_append_document_environment(latex_file);
        fclose(latex_file);
    }
    else
    {
        status = STATUS_BAD_FILE;
    }
    return status; 
}

static unsigned int latex_generate_book_template(const char* path, const char* output_filename)
{
    enum STATUS status = STATUS_OK;
    FILE * latex_file;
    latex_file = fopen("main.tex", "w");
    if (latex_file != NULL)
    {
        fprintf(latex_file, "\\documentclass{book}\n\n");
        latex_append_document_environment(latex_file);
        fclose(latex_file);
    }
    else
    {
        status = STATUS_BAD_FILE;
    }
    return status; 
}

static unsigned int latex_generate_letter_template(const char* path, const char* output_filename)
{
    enum STATUS status = STATUS_OK;
    FILE * latex_file;
    latex_file = fopen("main.tex", "w");
    if (latex_file != NULL)
    {
        fprintf(latex_file, "\\documentclass{letter}\n\n");
        latex_append_document_environment(latex_file);
        fclose(latex_file);
    }
    else
    {
        status = STATUS_BAD_FILE;
    }
    return status; 
}

static unsigned int latex_generate_slides_template(const char* path, const char* output_filename)
{
    enum STATUS status = STATUS_OK;
    FILE * latex_file;
    latex_file = fopen("main.tex", "w");
    if (latex_file != NULL)
    {
        fprintf(latex_file, "\\documentclass{slides}\n\n");
        latex_append_document_environment(latex_file);
        fclose(latex_file);
    }
    else
    {
        status = STATUS_BAD_FILE;
    }
    return status; 
}

static unsigned int latex_generate_beamer_template(const char* path, const char* output_filename)
{
    enum STATUS status = STATUS_OK;
    FILE * latex_file;
    latex_file = fopen("main.tex", "w");
    if (latex_file != NULL)
    {
        fprintf(latex_file, "\\documentclass{beamer}\n\n");
        latex_append_document_environment(latex_file);
        fclose(latex_file);
    }
    else
    {
        status = STATUS_BAD_FILE;
    }
    return status; 
}

extern unsigned int latex_generate_template(const char* path, const char* output_filename, LaTeXDocType document)
{
    char *full_path;
    enum STATUS status = STATUS_OK;
    full_path = latex_malloc_append_path(path, output_filename);
    if (full_path != NULL)
    {
        printf("full_path = %s\n", full_path);
        switch(document)
        {
            case latex_article:
                status = latex_generate_article_template(path, output_filename);
                break;
            case latex_report:
                status = latex_generate_report_template(path, output_filename);
                break;
            case latex_book:
                status = latex_generate_book_template(path, output_filename);
                break;
            case latex_letter:
                status = latex_generate_letter_template(path, output_filename);
                break;
            case latex_slides:
                status = latex_generate_slides_template(path, output_filename);
                break;
            case latex_beamer:
                status = latex_generate_beamer_template(path, output_filename);
                break;
            default:
                printf("no document type is not recognized\n");
                status = STATUS_BAD_DOC_TYPE;
        }
        free(full_path);
    } 
    else
    {
        status = STATUS_BAD_MEM_ALLOC;
    }    
	return status;
}

extern const char* latex_document_type_to_string(LaTeXDocType doc_type)
{
    /* allocating strings in data segement */ 
    static const char* latex_article_str  = "article";
    static const char* latex_report_str   = "report";
    static const char* latex_book_str     = "book";
    static const char* latex_letter_str   = "letter";
    static const char* latex_slides_str   = "slides";
    static const char* latex_beamer_str   = "beamer";
    static const char* latex_wrong_str    = "wrong type";
    const char * return_str;
    switch(doc_type)
    {
        case latex_article:
            return_str = latex_article_str;
            break;
        case latex_report:
            return_str = latex_report_str;
            break;
        case latex_book:
            return_str = latex_book_str;
            break;
        case latex_letter:
            return_str = latex_letter_str;
            break;
        case latex_slides:
            return_str = latex_slides_str;
            break;
        case latex_beamer:
            return_str = latex_beamer_str;
                break;
        default:
            return_str = latex_wrong_str;
    }
    return return_str;
}
