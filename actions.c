#include "def.h"
#include "grammar.h"

NT* create_a_NT() {
    NT* nt = checked_malloc(sizeof *nt);
    memset(nt, 0, sizeof *nt);

    return nt;
}
// S -> M P
NT* f1(int* ret) {
    global_entry = get_NT(0)->val;
    table_pop("main");

    return 0;
}
// P -> C V PC N SMT
NT* f2(int* ret) {
    NT* P = create_a_NT();
    P->val = get_NT(1)->val;

    return P;
}
// PC' -> PH M P ;
NT* f5(int* ret) {
    get_NT(3)->place->addr = get_NT(1)->val; table_pop(get_NT(3)->place->name);

    return 0;
}
// PC' -> PC' PH M P ;
NT* f6(int* ret) {
    get_NT(3)->place->addr = get_NT(1)->val;
    table_pop(get_NT(3)->place->name);

    return 0;
}
// PH -> procedure id ;
NT* f7(int* ret) {
    if (table_lookup(get_T(1)->id)) {
        *ret = -1;
        return 0;
    }

    Var* place = table_enter(get_T(1)->id, T_PROCEDURE, 0);
    NT* PH = create_a_NT();
    PH->place = place;

    return PH;
}
// CD -> id = num
NT* f12(int* ret) {
    if (table_lookup(get_T(2)->id)) {
        *ret = -1;
        return 0;
    }

    table_enter(get_T(2)->id, T_CONST, get_T(0)->num);

    return 0;
}
// V' -> var id |  V' -> V' , id
NT* f15_16(int* ret) {
    if (table_lookup(get_T(0)->id)) {
        *ret = -1;
        return 0;
    }

    table_enter(get_T(0)->id, T_VARIABLE, 0);

    return 0;
}
// M -> ^
NT* f17(int* ret) {
    table_make();

    return 0;
}
// N -> ^
NT* f18(int* ret) {
    NT* nt = create_a_NT();
    nt->val = nxq;

    return nt;
}
// A -> id := E
NT* f27(int* ret) {
    Var* place = table_lookup(get_T(2)->id);
    gen("=", get_NT(0)->place, 0, place);

    return 0;
}
// COND -> E REL E
NT* f31(int* ret) {
    gen(">", get_NT(2)->place, get_NT(0)->place, 0);

    return 0;
}
// COND -> odd E
NT* f32(int* ret) {
    NT* COND = create_a_NT();
    COND->place = new_temp();
    gen("odd", get_NT(0)->place, 0, COND->place);

    return COND;
}
// CONDSMT -> if COND W then SMT
NT* f39(int* ret) {
    // TODO

    return 0;
}
// CALL -> call id
NT* f40(int* ret) {
    Var* place = table_lookup(get_T(0)->id);
    gen("call", place, 0, 0);

    return 0;
}
// WRITEBEGIN -> write ( id |  WRITEBEGIN -> WRITEBEGIN , id
NT* f42_43(int* ret) {
    Var* place = table_lookup(get_T(0)->id);
    gen("write", place, 0, 0);

    return 0;
}
// READBEGIN -> read ( id |  READBEGIN -> READBEGIN , id
NT* f45_46(int* ret) {
    Var* place = table_lookup(get_T(0)->id);
    gen("read", place, 0, 0);

    return 0;
}
// E -> PLUS T
NT* f47(int* ret) {
    NT* E = create_a_NT();
    
    SYM op = (SYM) get_NT(1)->val;
    if (op == NUL_TYPE) E->place = get_NT(0)->place;
    else {
        E->place = new_temp();
        gen("+", get_NT(0)->place, 0, E->place);
    }

    return E;
}
// E -> E_1 + T
NT* f48(int* ret) {
    NT* E = create_a_NT();
    E->place = new_temp();
    gen("+", get_NT(2)->place, get_NT(0)->place, E->place);

    return E;
}
// PLUS -> +
NT* f49(int* ret) {
    NT* PLUS = create_a_NT();
    PLUS->val = get_T(0)->sym;

    return PLUS;
}
// PLUS -> ^
NT* f50(int* ret) {
    NT* PLUS = create_a_NT();
    PLUS->val = 0;

    return PLUS;
}
// T -> F
NT* f51(int* ret) {
    NT* T = create_a_NT();
    T->place = get_NT(0)->place;

    return T;
}
// T -> T_1 * F
NT* f52(int* ret) {
    NT* T = create_a_NT();
    T->place = new_temp();
    gen("*", get_NT(2)->place, get_NT(0)->place, T->place);

    return T;
}
// F -> id
NT* f53(int* ret) {
    Var* place = table_lookup(get_T(0)->id);
    NT* F = create_a_NT();
    F->place = place;
    return F;
}
// F -> num
NT* f54(int* ret) {
    NT* F = create_a_NT();
    F->place = new_temp();
    // TODO
    gen("=", 0, 0, F->place);

    return F;
}
//  F -> ( E )
NT* f55(int* ret) {
    NT* F = create_a_NT();
    F->place = get_NT(1)->place;

    return F;
}
// WHILE -> while N COND W do SMT
NT* f56(int* ret) {
    gen("jmp", get_NT(4)->place, 0, 0);
    // TODO
    // fill

    return 0;
}
// W -> ^
NT* f57(int* ret) {
    NT* W = create_a_NT();
    W->val = nxq;
    gen("j0", 0, 0, 0);

    return W;
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
    [27] f27,
    [31] f31,
    [32] f32,
    [39] f39,
    [40] f40,
    [42] f42_43,
    [43] f42_43,
    [45] f45_46,
    [46] f45_46,
    [47] f47,
    [48] f48,
    [49] f49,
    [50] f50,
    [51] f51,
    [52] f52,
    [53] f53,
    [54] f54,
    [55] f55,
    [56] f56,
    [57] f57,
};