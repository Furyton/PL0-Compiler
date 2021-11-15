#ifndef DEF
#define DEF

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PL0.h"

typedef struct {
	SYM sym;
	char id[MAX_ID_LEN];
	int num, row; // row number in original code. start with 1.
} Token;

char prog[MAX_PROG_LEN];

int token_n;

Token tokens[MAX_TOKEN_N];

/*************** lexical part ***************/

const char keychars[KEYCHAR_N];

int lexical_analysis(FILE *in, FILE *out, FILE *err);

SYM getType(const char* str);
SYM getKeywordType(const char* str);
SYM getSpecialType(const char* str);

int isLetter(char ch);
int isDigit(char ch);

int isSpecial(char ch);

void print_token(FILE*, Token *token);

typedef enum {
    S_START,
    S_STRING,
    S_ID,
    S_NUM,
    S_SPEC1,
    S_SPEC2,
	S_CHECK,
    S_ERROR,
} STATE;

/*************** syntax part ***************/

int nxq; // next quad

typedef struct {
	char name[MAX_ID_LEN];
	enum {CONST, VARIABLE, PROCEDURE} kind;
	int val, lev, offset;
} Var;

typedef struct {
	Var *place;
	int val;
} NT; // non terminals

typedef struct {
	union {
		NT * V;
		SYM * T;
	} u;

	enum {NonTerminal, Terminal} kind;
} Item; // used in the stack

struct Table_{
	Var variables[MAX_VAR_PER_TABLE];
	int val_len;
	int lev;
	struct Table_* prev;
};

typedef struct Table_ Table;

Table tables_stack[MAX_STACK_SIZE];
int table_top;

int offset_stack[MAX_LEV];
int offset_top;

int state_stack[MAX_STACK_SIZE];
Item item_stack[MAX_STACK_SIZE];
int top;

// table

void table_pop();
// void table_enter(char* name, V_kind kind);

// SLR dealer

int state_n, symbols_n;

int map_table[MAX_STATE_N][MAX_TERMS];

SYM action_header[MAX_TERMS];

void read_map_table();

int get_next_action(int state, SYM input_sym);

int cur_state();

void action_shift(int nxt_state);
void action_reduction(int grammar);

int syntax_analysis(FILE* err);

#endif