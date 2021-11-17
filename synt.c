#include "def.h"
#include "grammar.h"

int syntax_analysis(FILE* out, FILE *err) {
    read_map_table();

    memset(offset_stack, 0, sizeof(offset_stack));

    state_top = 0;

    int i = 0;
    while(i < token_n) {
        int nxt_action = get_next_action(cur_state(), tokens[i].sym);

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

            fprintf(err, "error occurs on %d th token in %d th row, LR state stack top is %d, current LR state is %d\n", i + 1, tokens[i].row, state_top, cur_state());

            return -1;
        }

        if (nxt_action > state_n) {
            
            table_print_all(out);
            return 0; // acc
        }

        if (nxt_action > 0) {
            action_shift(nxt_action);
            
            stack_push_T(&tokens[i]);
            
            i ++;
        } else {
            if (action_reduction(-nxt_action) < 0) {
                puts("error!!!");

                fprintf(err, "                SYM name       SYM value           SYM row\n");

                fprintf(err, "previous token: ");
                print_token(err, &tokens[i - 1]);
                fprintf(err, "----error---->: ");
                print_token(err, &tokens[i]);
                fprintf(err, "follow   token: ");
                print_token(err, &tokens[i + 1]);
                fputc('\n', err);

                fprintf(err, "multiple definition on %d th token in %d th row, LR state stack top is %d, current LR state is %d\n", i + 1, tokens[i].row, state_top, cur_state());

                return -1;
            }
        }
    }
}