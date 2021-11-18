#include "def.h"

int compile(FILE* source, FILE* lex_code, FILE* synt_code, FILE* inter_code, FILE* compile_info, FILE* err) {
    if (lexical_analysis(source, lex_code, err) < 0) {
        fputs("lexical analysis failed!!!\nplease checkout errmsg.err for more detail.", compile_info);

        return -2;
    }

    if (syntax_analysis(synt_code, inter_code, err) < 0) {
        fputs("syntax analysis failed!!!\nplease checkout errmsg.err for more detail.", compile_info);

        return -1;
    }
    
    fputs("success!!", compile_info);

    fprintf(compile_info, "global entry is: %d\n", global_entry);

    return 0;    
}