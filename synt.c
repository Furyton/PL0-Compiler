#include "def.h"
#include "grammar.h"

int syntax_analysis(FILE *err) {
    read_map_table();

    memset(state_stack, 0, sizeof(state_stack));
    state_top = 0;

    int i = 0;
    while(i < token_n) {
        int nxt_action = get_next_action(cur_state(), tokens[i].sym);

        // fprintf(err, "[synt]: %d\n", nxt_action);

        if (!nxt_action) {
            puts("error!!!");

            print_token(err, &tokens[i - 1]);
            print_token(err, &tokens[i]);
            print_token(err, &tokens[i + 1]);

            fprintf(err, "error inccurs on %d th token, LR state stack top is %d, current LR state is %d\n", i + 1, state_top, cur_state());

            return -1;
        }

        if (nxt_action > state_n) {
            return 0; // acc
        }

        if (nxt_action > 0) {
            action_stack(nxt_action);
            i ++;
        } else {
            action_reduction(-nxt_action);
        }
    }
}