#include "def.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: compiler source.pas\n");

        return -1;
    }

    FILE *source, *lex_code, *synt_code, *err, *inter_code;

    source = fopen(argv[1], "r");
    lex_code = fopen("_lex_code", "w");
    err = fopen("_errmsg.err", "w");

    if (lexical_analysis(source, lex_code, err) < 0) {
        puts("lexical analysis failed!!!\nplease checkout errmsg.err for more detail.");

        fclose(source);
        fclose(lex_code);
        fclose(err);

        return -2;
    }

    fclose(source);
    fclose(lex_code);

    synt_code = fopen("_synt_code", "w");
    inter_code = fopen("_inter_code", "w");
    
    if (syntax_analysis(synt_code, inter_code,err) < 0) {
        puts("syntax analysis failed!!!\nplease checkout errmsg.err for more detail.");
        fclose(err);
        fclose(synt_code);

        return -1;
    }
    
    puts("success!!");

    printf("global entry is: %d\n", global_entry);

    fclose(err);
    fclose(synt_code);

    return 0;
}