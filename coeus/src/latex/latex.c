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

extern unsigned int latex_generate_template(const char* project_title, LaTeXDocType document)
{
    enum STATUS status = STATUS_OK;
    FILE* make_file;
    FILE* latex_file;
    char* filename;
    int check;

    check = mkdir(project_title, 0777);
    if (check == 0)
    {
        filename = latex_malloc_append_path(project_title, "main.tex");
        if (filename != NULL)
        {
            latex_file = fopen(filename, "w");
            if (latex_file != NULL)
            {
                fprintf(latex_file, "\\documentclass{%s}\n\n", latex_document_type_to_string(document));
                latex_append_document_environment(latex_file, project_title);
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
        //Makefile block
        filename = latex_malloc_append_path(project_title, "Makefile");
        if (filename != NULL)
        {
            make_file = fopen(filename, "w");
            if (make_file != NULL)
            {
                fprintf(make_file,"OUTDIR = $(shell pwd)\n");
                fprintf(make_file,"TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error\n");
                fprintf(make_file,"PDFTEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error\n");
                fprintf(make_file,"PDFOUT = %s\n", project_title);
                fprintf(make_file,"PDF_TARGET = $(addsuffix .pdf, $(PDFOUT))\n");
                fprintf(make_file,"LATEXIN = main.tex\n\n");
                fprintf(make_file,"all: pdf\n\n");
                fprintf(make_file,"pdf: $(PDF_TARGET)\n\n");
                fprintf(make_file,"$(PDF_TARGET): $(LATEXIN)\n");
                fprintf(make_file,"\t$(PDFTEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)\n");
                fprintf(make_file,"\t$(PDFTEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)\n");
                fprintf(make_file,"\techo -e \"\\033[0\\32m Target Made Successfully \\033[0m\"\n\n");
                fprintf(make_file,"clean:\n");
                fprintf(make_file,"\trm  -f *.pdf *.aux *.dvi *.log *.toc\n");
            
                fclose(make_file);
            }
            else
            {
                status = STATUS_BAD_FILE;
            }
            free(filename);
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
    return latex_undefined;
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
