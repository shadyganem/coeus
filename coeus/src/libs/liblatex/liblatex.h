/*
 * @author: Shady Ganem <shadyganem@gmail.com>
 * all rights reserved 
 * Do not use, copy or redistribute without the author's permession.
 */

#ifndef _LIBLATEX_H_
#define _LIBLATEX_H_ 

typedef enum 
{
	latex_article,
    latex_report,
	latex_book,
	latex_letter,
	latex_slides,
	latex_beamer,
	//proc    - support will added in the future
	//minimal - support will added in the future
	//memoir  - support will added in the future
    latex_undefined
} LaTeXDocType;

extern unsigned int liblatex_generate_template(const char* project_title, LaTeXDocType doc_type);
extern const char*  liblatex_document_type_to_string(LaTeXDocType);
extern LaTeXDocType liblatex_string_to_document_type(const char* doc_type_srt);
extern const char* liblatex_status_to_string(int status);

#endif
