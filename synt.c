#include "def.h"
#include "grammar.h"

void syntax_analysis() {
    read_map_table();

    memset(state_stack, 0, sizeof(state_stack));
    state_top = 0;

    int i;
    for (i = 0; i < token_n; i++) {
        int nxt_action = get_next_action(cur_state(), tokens[i].sym);

        printf("[nxt_action]: %d\n", nxt_action);

        if (!nxt_action || state_top < 0) {
            puts("error!!!");

            FILE* err = fopen("error.err", "w");

            print_token(err, &tokens[i]);

            printf("%d %d %d", i, state_top, cur_state());

            fclose(err);

            return;
        }

        if (nxt_action > state_n) {
            puts("acc !!!");
            return;
        }

        if (nxt_action > 0) {
            action_stack(nxt_action);
        } else {
            action_reduction(-nxt_action);
        }
    }
}