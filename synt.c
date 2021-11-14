#include "def.h"
#include "grammar.h"

int syntax_analysis(FILE *err) {
    read_map_table();

    top = 0;

    int i = 0;
    while(i < token_n) {
        int nxt_action = get_next_action(cur_state(), tokens[i].sym);

        // fprintf(err, "[synt]: %d\n", nxt_action);

        if (!nxt_action) {
            puts("error!!!");

            fprintf(err, "                SYM name       SYM value           SYM row\n");

            fprintf(err, "previous token: ");
            print_token(err, &tokens[i - 1]);
            fprintf(err, "----error---->: ");
            print_token(err, &tokens[i]);
            fprintf(err, "follow   token: ");
            print_token(err, &tokens[i + 1]);
            fputc('\n', err);

            fprintf(err, "error occurs on %d th token in %d th row, LR state stack top is %d, current LR state is %d\n", i + 1, tokens[i].row, top, cur_state());

            return -1;
        }

        if (nxt_action > state_n) {
            return 0; // acc
        }

        if (nxt_action > 0) {
            action_shift(nxt_action);
            i ++;
        } else {
            action_reduction(-nxt_action);
        }
    }
}