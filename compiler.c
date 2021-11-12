#include "def.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: compiler source.pas\n");

        return -1;
    }

    FILE *source, *lex_code;

    source = fopen(argv[1], "r");
    lex_code = fopen("_lex_code", "w");

    lexical_analysis(source, lex_code);

    fclose(source);
    fclose(lex_code);

    // test();

    syntax_analysis();

    return 0;
}