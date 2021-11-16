#include "def.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: compiler source.pas\n");

        return -1;
    }

    FILE *source, *lex_code, *synt_code, *err;

    source = fopen(argv[1], "r");
    lex_code = fopen("_lex_code", "w");
    synt_code = fopen("_synt_code", "w");
    err = fopen("_errmsg.err", "w");

    lexical_analysis(source, lex_code, err);

    fclose(source);
    fclose(lex_code);

    // test();

    int status = syntax_analysis(synt_code, err);

    if (status < 0) {
        puts("syntax analysis failed!!!\nplease checkout errmsg.err for more detail.");

        return -1;
    } else {
        puts("success!!");
    }

    fclose(err);
    fclose(synt_code);

    return 0;
}