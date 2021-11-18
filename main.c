#include "def.h"
#include "runner.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: compiler source.pas\n");

        return -1;
    }

    FILE *source, *lex_code, *synt_code, *err, *inter_code, *compile_info;

    source = fopen(argv[1], "r");
    lex_code = fopen("_lex_code", "w");
    err = fopen("_errmsg.err", "w");
    synt_code = fopen("_synt_code", "w");
    inter_code = fopen("_inter_code", "w");
    compile_info = fopen("_info", "w");

    int status = compile(source, lex_code, synt_code, inter_code, compile_info, err);

    fclose(err);
    fclose(source);
    fclose(lex_code);
    fclose(synt_code);
    fclose(compile_info);

    if (status != 0) return -1;

    run(global_entry);

    return 0;
}