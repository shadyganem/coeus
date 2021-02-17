
#include "liblatex.h"
#include <stdio.h>
#include <unistd.h>

#define test_main main //not to be confues with the coeus main main

/*this main is for testing latex.h interface not the entry point for coeus*/
int test_main()
{
    char *filename = "latex_test";
    char path[FILENAME_MAX];
    LaTeXDocType doc_type = latex_book;
    const char* ptr_to_str = liblatex_document_type_to_string(latex_book);

    printf("doctype %d is  %s \n", liblatex_string_to_document_type(liblatex_document_type_to_string(latex_article)), liblatex_document_type_to_string(latex_article));
    printf("doctype %d is  %s \n", liblatex_string_to_document_type(liblatex_document_type_to_string(latex_book)),liblatex_document_type_to_string(latex_book));
    printf("%s \n", liblatex_document_type_to_string(latex_report));
    printf("%s \n", liblatex_document_type_to_string(latex_letter));
    printf("%s \n", liblatex_document_type_to_string(latex_beamer));
    printf("%s \n", liblatex_document_type_to_string(99));


    int status = liblatex_generate_template(filename, latex_beamer);
    if (status != 0)
    {
        printf("LaTeX ERROR: %s\n", liblatex_status_to_string(status));
    }
    return 0;
}

