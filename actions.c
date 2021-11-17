#include "def.h"
#include "grammar.h"

int global_entry;

NT* create_a_NT() {
    NT* nt = checked_malloc(sizeof *nt);
    memset(nt, 0, sizeof *nt);

    return nt;
}

NT* f1(int* ret) {
    global_entry = get_NT(0)->val;
    table_pop("main");
    *ret = 0;

    return 0;
}

NT* f2(int* ret) {
    NT* P = create_a_NT();
    P->val = get_NT(1)->val;
    *ret = 0;

    return P;
}

NT* f5(int* ret) {
    get_NT(3)->place->addr = get_NT(1)->val; table_pop(get_NT(3)->place->name);
    *ret = 0;

    return 0;
}

NT* f6(int* ret) {
    get_NT(3)->place->addr = get_NT(1)->val;
    table_pop(get_NT(3)->place->name);
    *ret = 0;

    return 0;
}

NT* f7(int* ret) {
    if (table_lookup(get_T(1)->id)) {
        *ret = -1;
        return 0;
    }

    *ret = 0;

    Var* place = table_enter(get_T(1)->id, T_PROCEDURE, 0);
    NT* PH = create_a_NT();
    PH->place = place;

    return PH;
}

NT* f12(int* ret) {
    if (table_lookup(get_T(2)->id)) {
        *ret = -1;
        return 0;
    }

    *ret = 0;

    table_enter(get_T(2)->id, T_CONST, get_T(0)->num);

    return 0;
}

NT* f15_16(int* ret) {
    if (table_lookup(get_T(0)->id)) {
        *ret = -1;
        return 0;
    }

    *ret = 0;

    table_enter(get_T(0)->id, T_VARIABLE, 0);

    return 0;
}

NT* f17(int* ret) {
    *ret = 0;

    table_make();

    return 0;
}

NT* f18(int* ret) {
    *ret = 0;
    NT* nt = create_a_NT();
    nt->val = 99;

    return nt;
}

NT* (*grammar_action[64])(int*) = {
    [1] f1,
    [2] f2,
    [5] f5,
    [6] f6,
    [7] f7,
    [12] f12,
    [15] f15_16,
    [16] f15_16,
    [17] f17,
    [18] f18,
};