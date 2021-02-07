#ifndef _LIBMAKE_H_
#define _LIBMAKE_H_

enum GenericMakefile
{
    MF_C_module;
    MF_C_shared_lib;
    MF_C_static_lib;
    MF_C_program;
    MF_undefined;
}
extern int libmake_generate_template(GenericMakefile file_type, const char * path);
#endif
