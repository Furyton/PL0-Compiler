#ifndef DEF
#define DEF

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PL0.h"

void *checked_malloc(int len);

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

typedef struct {
	char name[MAX_ID_LEN];
	TableTermType kind;
	int val, lev, addr;
} Var; // used in table

typedef struct {
	Var *place;
	int val;
} NT; // non terminals

typedef struct {
	union {
		NT * V;
		Token * T;
	} u;

	StackTermType kind;
} Item; // used in the stack

struct Table_{
	Var* variables[MAX_VAR_PER_TABLE];
	char name[MAX_ID_LEN];
	int val_len;
	struct Table_* prev;
};

typedef struct Table_ Table;

// item stack

Item item_stack[MAX_STACK_SIZE];
int item_top;

void stack_push_NT(NT * nt);
void stack_push_T(Token * t);
void stack_pop();
Token* get_T(int);
NT* get_NT(int);

// table

Table* tables_stack[MAX_STACK_SIZE];
int table_top;

int table_n;

Table tables[MAX_TABLE_N];
Table* cur_table;

void table_pop(char* name);
Var* table_enter(char* name, TableTermType type, int val);
void table_make();
Var* table_lookup(char* name);

void table_print_all();

// offset

int offset_stack[MAX_LEV];
int offset_top;


// SLR dealer

int state_stack[MAX_STACK_SIZE];
int state_top;

int state_n, symbols_n;

int map_table[MAX_STATE_N][MAX_TERMS];

SYM action_header[MAX_TERMS];

void read_map_table();

int get_next_action(int state, SYM input_sym);

int cur_state();

void action_shift(int nxt_state);
int action_reduction(int grammar);

int syntax_analysis(FILE* out, FILE* err);

// intercode gen part

int nxq; // next quad
int cur_tmp_cnt;
char cur_tmp_name[MAX_ID_LEN];

Var* new_temp(); // new temperory variable

void gen(char* code_name, Var* s1, Var* s2, Var* dst);

int global_entry;


#endif