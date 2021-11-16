#ifndef GRAMMAR
#define GRAMMAR

/********grammar info********/

#include "def.h"

#define MAX_GRAMMAR_N 64

int grammar_n;

int terminal_n;

int grammar_length[MAX_GRAMMAR_N];

int grammar_index[MAX_GRAMMAR_N];




/**
 * @brief grammar
 * 
 * 
 0:         S' -> S
 1:          S -> M Q P
 2:          P -> C V PC N SMT {table_pop(); P.place.addr = N.val; }
 3:         PC -> ^
 4:         PC -> PC'
 5:        PC' -> PH M P ; {}
 6:        PC' -> PC' PH M P ;
 7:         PH -> procedure id ; {table_lookup(id.id); table_enter(id.id, T_PROCEDURE, 0); }
 8:          C -> ^
 9:          C -> C' ;
10:         C' -> const CD
11:         C' -> C' , CD
12:         CD -> id = num {table_lookup(id.id); table_enter(id.id, T_CONST, num.num); }
13:          V -> V' ;
14:          V -> ^
15:         V' -> V' , id {table_lookup(id.id); table_enter(id.id, T_VARIABLE, 0); }
16:         V' -> var id {table_lookup(id.id); table_enter(id.id, T_VARIABLE, 0); }
17:          M -> ^ {table_make();}
18:          Q -> ^ {}
19:          N -> ^ {N.val = nxq;}
20:        SMT -> READ
21:        SMT -> CONDSMT
22:        SMT -> WRITE
23:        SMT -> ^
24:        SMT -> A
25:        SMT -> CALL
26:        SMT -> COMP
27:        SMT -> WHILE
28:          A -> id := E
29:       COMP -> COMPBEGIN end
30:  COMPBEGIN -> begin SMT
31:  COMPBEGIN -> COMPBEGIN ; SMT
32:       COND -> E REL E
33:       COND -> odd E
34:        REL -> >=
35:        REL -> <
36:        REL -> #
37:        REL -> <=
38:        REL -> =
39:        REL -> >
40:    CONDSMT -> if COND W then SMT
41:       CALL -> call id
42:      WRITE -> WRITEBEGIN )
43: WRITEBEGIN -> write ( id
44: WRITEBEGIN -> WRITEBEGIN , id
45:       READ -> READBEGIN )
46:  READBEGIN -> READBEGIN , id
47:  READBEGIN -> read ( id
48:          E -> E + T
49:          E -> PLUS T
50:       PLUS -> +
51:       PLUS -> ^
52:          T -> F
53:          T -> T * F
54:          F -> num
55:          F -> ( E )
56:          F -> id
57:      WHILE -> while N COND W do SMT
58:          W -> ^
 * 
 */

#endif