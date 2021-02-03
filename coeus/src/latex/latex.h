/*
 * @author: Shady Ganem <shadyganem@gmail.com>
 * all rights reserved 
 * Do not use, copy or redistribute without the author's permession.
 */

#ifndef LATEX_H 
#define LATEX_H 

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

extern unsigned int latex_generate_template(const char* project_title, LaTeXDocType doc_type);
extern const char*  latex_document_type_to_string(LaTeXDocType);
extern LaTeXDocType latex_string_to_document_type(const char* doc_type_srt);
extern const char* latex_status_to_string(int status);

#endif
