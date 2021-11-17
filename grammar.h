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
18:          N -> ^ {}
19:        SMT -> A
20:        SMT -> CONDSMT
21:        SMT -> WHILE
22:        SMT -> CALL
23:        SMT -> READ
24:        SMT -> WRITE
25:        SMT -> COMP
26:        SMT -> ^
27:          A -> id := E
28:       COMP -> COMPBEGIN end
29:  COMPBEGIN -> begin SMT
30:  COMPBEGIN -> COMPBEGIN ; SMT
31:       COND -> E REL E
32:       COND -> odd E
33:        REL -> <
34:        REL -> <=
35:        REL -> >
36:        REL -> >=
37:        REL -> =
38:        REL -> #
39:    CONDSMT -> if COND W then SMT
40:       CALL -> call id
41:      WRITE -> WRITEBEGIN )
42: WRITEBEGIN -> write ( id
43: WRITEBEGIN -> WRITEBEGIN , id
44:       READ -> READBEGIN )
45:  READBEGIN -> read ( id
46:  READBEGIN -> READBEGIN , id
47:          E -> PLUS T
48:          E -> E + T
49:       PLUS -> +
50:       PLUS -> ^
51:          T -> F
52:          T -> T * F
53:          F -> id
54:          F -> num
55:          F -> ( E )
56:      WHILE -> while N COND W do SMT
57:          W -> ^
 * 
 */

#endif