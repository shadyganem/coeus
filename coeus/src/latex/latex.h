/*
 * @author: Shady Ganem <shadyganem@gmail.com>
 * all rights reserved 
 * Do not use, copy or redistribute without the author's
 * permession.
 */
#ifndef LATEX_H 
#define LATEX_H 
typedef enum 
{
	book,
	article,
	beamer,
	proc,
	minimal,
	slides,
	memoir,
	letter
} TexDocType;
typedef unsigned int uint;
extern uint latex_generate_template(const char* Path, const char*OutpuFileName, TexDocType Document);
#endif
