/*
 * @author: Shady Ganem <shadyganem@gmail.com>
 * all rights reserved 
 * Do not use, copy or redistribute without the author's
 * permession.
 */
#ifndef LATEX_H 
#define LATEX_H 

#define STATUS_OK 0


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
	//proc - support will added in the future
	//minimal - support will added in the future
	//memoir - support will added in the future
} LaTeXDocType;

typedef unsigned int uint;

extern uint latex_generate_template(const char*, const char*, LaTeXDocType);
extern const char* latex_document_type_to_string(LaTeXDocType);

#endif
