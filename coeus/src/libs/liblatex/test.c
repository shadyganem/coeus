
#include "liblatex.h"
#include <stdio.h>
#include <unistd.h>

#define test_main main //not to be confues with the coeus main main

/*this main is for testing latex.h interface not the entry point for coeus*/
int test_main()
{
    char *filename = "latex_test";
    char original_path[FILENAME_MAX];
    char path[FILENAME_MAX];
    LaTeXDocType doc_type = latex_book;
    const char* ptr_to_str = latex_document_type_to_string(latex_book);

    printf("doctype %d is  %s \n", latex_string_to_document_type(latex_document_type_to_string(latex_article)), latex_document_type_to_string(latex_article));
    printf("doctype %d is  %s \n", latex_string_to_document_type(latex_document_type_to_string(latex_book)),latex_document_type_to_string(latex_book));
    printf("%s \n", latex_document_type_to_string(latex_report));
    printf("%s \n", latex_document_type_to_string(latex_letter));
    printf("%s \n", latex_document_type_to_string(latex_beamer));
    printf("%s \n", latex_document_type_to_string(99));

    if (getcwd(path, FILENAME_MAX))
    {
        printf("%s\n", path);
    }
    chdir("/home/svshared/test_dir");
    if (getcwd(path, FILENAME_MAX))
    {
        printf("%s\n", path);
    }
    chdir("-");
    if (getcwd(path, FILENAME_MAX))
    {
        printf("%s\n", path);
    }

    int status = latex_generate_template(filename, latex_beamer);
    if (status != 0)
    {
        printf("LaTeX ERROR: %s\n", latex_status_to_string(status));
    }
    return 0;
}

