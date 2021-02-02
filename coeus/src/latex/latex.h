/*
 * @author: Shady Ganem <shadyganem@gmail.com>
 * all rights reserved 
 * Do not use, copy or redistribute without the author's permession.
 */

#ifndef LATEX_H 
#define LATEX_H 

#define STATUS_OK 0

typedef unsigned int uint;

typedef enum
{
    LATEX_OK = 0,
    LATEX_BAD_FILE = 100,
    LATEX_BAD_DOC_TYPE = 101
} LatexStatus;
    
typedef enum 
{
	latex_article,
    latex_report,
	latex_book,
	latex_letter,
	latex_slides,
	latex_beamer
	//proc    - support will added in the future
	//minimal - support will added in the future
	//memoir  - support will added in the future
} LaTeXDocType;


extern unsigned int latex_generate_template(const char* path, const char* output_filename, LaTeXDocType doc_type);
extern const char*  latex_document_type_to_string(LaTeXDocType);

#endif
