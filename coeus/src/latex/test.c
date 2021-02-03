
#include "latex.h"
#include <stdio.h>
#include <unistd.h>

#define test_main main //not to be confues with the coeus main main

/*this main is for testing latex.h interface not the entry point for coeus*/
int test_main()
{
    const char* ptr_to_str = latex_document_type_to_string(latex_book);
    printf("doctype %d is  %s \n", latex_string_to_doc_type(latex_document_type_to_string(latex_article)), latex_document_type_to_string(latex_article));
    printf("doctype %d is  %s \n", latex_string_to_doc_type(latex_document_type_to_string(latex_book)),latex_document_type_to_string(latex_book));
    printf("%s \n", latex_document_type_to_string(latex_report));
    printf("%s \n", latex_document_type_to_string(latex_letter));
    printf("%s \n", latex_document_type_to_string(latex_beamer));
    printf("%s \n", latex_document_type_to_string(99));

    char path[FILENAME_MAX];
    char *filename = "latex_test";
    LaTeXDocType doc_type = latex_book;
    if(getcwd(path, FILENAME_MAX) != NULL)
    {
        int status = latex_generate_template(path, filename, 1);
        if (status  != 0)
        {
            printf("LaTeX ERROR: %s\n", latex_status_to_str(status));
        }
    }
    else
    {
        printf("getcwd failed\n");
    }
    return 0;
}

