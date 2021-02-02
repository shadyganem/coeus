#include "latex.h"
#include <stdio.h>
#define STATUS_OK 0
#define STATUS_ERROR 1
typedef unsigned int uint; 

/*static fucntion declarations*/
static uint latex_generate_book_template(const char* path, const char* output_filename);
static uint latex_generate_article_template(const char* path, const char* output_filename);
static uint latex_generate_beamer_template(const char* path, const char* output_filename);
static uint latex_generate_proc_template(const char* path, const char* output_filename);
static uint latex_generate_article_template(const char* path, const char* output_filename);
static uint latex_generate_article_template(const char* path, const char* output_filename);

/*static global variables*/
static const char* _BookDocumentclass = "\documentclass{book}\n";

static uint latex_generate_book_template(const char* path, const char* output_filename)
{
	printf("latex_generate_book_template\n");	
    LatexStatus status = STATUS_OK;
    return status; 
}

static uint latex_generate_article_template(const char* path, const char* output_filename)
{
    LatexStatus status = STATUS_OK;
	printf("latex_generate_article_template\n");	
    return status; 
}

extern uint latex_generate_template(const char* path, const char* output_filename, LaTeXDocType document)
{
    LatexStatus status = LATEX_OK;
    switch(document)
    {
        case latex_book:
            status = latex_generate_book_template(path, output_filename);
            break;
        case latex_article:
            status = latex_generate_article_template(path, output_filename);
            break;
        default:
            printf("no document type is not recognized\n");
            status = LATEX_BAD_DOC_TYPE;
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
