
#include "latex.h"
#include <stdio.h>

//#define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

/*this main is for testing latex.h interface not the entry point for coeus*/
int main()
{
    const char* ptr_to_str = latex_document_type_to_string(latex_book);
    printf("%s \n", latex_document_type_to_string(latex_article));
    printf("%s \n", latex_document_type_to_string(latex_book));
    printf("%s \n", latex_document_type_to_string(latex_report));
    printf("%s \n", latex_document_type_to_string(latex_letter));
    printf("%s \n", latex_document_type_to_string(latex_beamer));

    printf("FILENAME_MAX = %d\n", FILENAME_MAX);
    char path[FILENAME_MAX];
    char *filename = "latex_test";
    LaTeXDocType doc_type = latex_article;
    if(GetCurrentDir(path, FILENAME_MAX) != NULL)
    {
        printf("cwd = %s\n", path);
        unsigned int status = latex_generate_template(path, filename, doc_type);
    }
    else
    {
        printf("getcwd failed\n");
    }
    return 0;
}
