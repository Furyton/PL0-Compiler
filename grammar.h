#ifndef GRAMMAR
#define GRAMMAR

/********grammar info********/

#include "def.h"

#define MAX_GRAMMAR_N 64

int grammar_n;

int terminal_n;

int grammar_length[MAX_GRAMMAR_N];

int grammar_index[MAX_GRAMMAR_N];

NT* (*grammar_action[64])(int*);

/**
 * @brief grammar
 * 
 * 
 0:         S' -> S
 1:          S -> M P {global_entry = P.val; table_pop("main"); }
 2:          P -> C V PC N SMT { P.val = N.val; }
 3:         PC -> PC'
 4:         PC -> ^
 5:        PC' -> PH M P ; { PH.place.addr = P.val; table_pop(PH.place.id); }
 6:        PC' -> PC' PH M P ; { PH.place.addr = P.val; table_pop(PH.place.id); }
 7:         PH -> procedure id ; {table_lookup(id.id); p = table_enter(id.id, T_PROCEDURE, 0); PH.place = p; }
 8:          C -> C' ;
 9:          C -> ^
10:         C' -> const CD
11:         C' -> C' , CD
12:         CD -> id = num {table_lookup(id.id); table_enter(id.id, T_CONST, num.num); }
13:          V -> V' ;
14:          V -> ^
15:         V' -> var id {table_lookup(id.id); table_enter(id.id, T_VARIABLE, 0); }
16:         V' -> V' , id {table_lookup(id.id); table_enter(id.id, T_VARIABLE, 0); }
17:          M -> ^ {table_make();}
18:          N -> ^ {N.val = nxq; }
19:        SMT -> A
20:        SMT -> CONDSMT
21:        SMT -> WHILE
22:        SMT -> CALL
23:        SMT -> READ
24:        SMT -> WRITE
25:        SMT -> COMP
26:        SMT -> ^
27:          A -> id := E { place = lookup(id); gen(=, E.place, 0, place); }
28:       COMP -> COMPBEGIN end
29:  COMPBEGIN -> begin SMT
30:  COMPBEGIN -> COMPBEGIN ; SMT
31:       COND -> E REL E { COND.place = new_temp(); gen(REL.op, E_1.place, E_2.place, COND.place); }
32:       COND -> odd E { COND.place = new_temp(); gen(odd, E.place, 0, COND.place); }
33:        REL -> < {..}
34:        REL -> <= {..}
35:        REL -> > {..}
36:        REL -> >= {..}
37:        REL -> = {..}
38:        REL -> # {..}
39:    CONDSMT -> if COND W then SMT { refill(W.nxq, j0, COND.place, 0, nxq); }
40:       CALL -> call id { place = lookup(id); gen(call, place, 0, 0); }
41:      WRITE -> WRITEBEGIN )
42: WRITEBEGIN -> write ( id { place = lookup(id); gen(write, place, 0, 0); }
43: WRITEBEGIN -> WRITEBEGIN , id { place = lookup(id); gen(write, place, 0, 0); }
44:       READ -> READBEGIN )
45:  READBEGIN -> read ( id { place = lookup(id); gen(read, place, 0, 0); }
46:  READBEGIN -> READBEGIN , id { place = lookup(id); gen(read, place, 0, 0); }
47:          E -> PLUS T { E.place = new_temp(); gen(PLUS.op, T.place, 0, E.place); }
48:          E -> E_1 + T { E.place = new_temp(); gen(+, E_1.place, T.place, E.place); }
49:       PLUS -> + { PLUS.val = +/-; }
50:       PLUS -> ^ { PLUS.val = 0; }
51:          T -> F { T.place = F.place; }
52:          T -> T_1 * F { T.place = new_temp(); gen(*, T_1.place, F.place, T.place); }
53:          F -> id { place = lookup(id); F.place = place; }
54:          F -> num { F.place = new_temp(); gen(=, num, 0, F.place); }
55:          F -> ( E ) { F.place = E.place; }
56:      WHILE -> while N COND W do SMT { gen(j, N.place, 0, 0); fill(W.nxq, j0, COND.place, 0, nxq); }
57:          W -> ^ { W.nxq = nxq; gen(j0, 0, 0, 0); }
 * 
 */

#endif