#ifndef DEF
#define DEF

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ID_LEN 10
#define MAX_PROG_LEN 512
#define MAX_TOKEN_N 256

typedef enum {
	NUL_TYPE,	// error

	// Keywords
	K_BEGIN, 	// begin
	K_CALL, 	// call
	K_CONST,	// const
	K_DO,		// do
	K_END,		// end
	K_IF,		// if
	K_ODD,		// odd
	K_PROCEDURE,// procedure
	K_READ,		// read
	K_THEN,		// then
	K_VAR,		// var
	K_WHILE,	// while
	K_WRITE,	// write

	// Operators
	O_PLUS,		// +
	O_MINUS,	// -
	O_MULTI,	// *
	O_DIV,		// /
	O_ASSIGN,	// :=
	O_EQ,		// =
	O_LESS,		// <
	O_LEQ,		// <=
	O_GTR,		// >
	O_GEQ,		// >=
	O_NEQ,		// # (NE, not equal)

	// Delimiters
	D_COMMA,	// ,
	D_SEMICOLON,// ;
	D_PERIOD,	// .
	D_LP,		// (
	D_RP,		// )

	// identifier
	ID,

	// number
	NUMBER,
} SYM;

typedef struct {
	SYM sym;
	char id[MAX_ID_LEN];
	int num;
} Token;

char prog[MAX_PROG_LEN];

int token_n;

Token tokens[MAX_TOKEN_N];

/*************** lexical part ***************/

#define KEYWORD_N 13

#define KEYCHAR_N 13

const char keychars[KEYCHAR_N];

#define SPECIAL_N 16

void lexical_analysis(FILE *in, FILE *out);

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

#define MAX_VAR_PER_TABLE 32
#define MAX_TABLE_N 8

int nxq; // next quad

typedef struct {
	
} Var;

typedef struct {
	Var *place;
	int nxq;
} NT; // non terminals

typedef struct {
	union {
		NT * V;
		SYM * T;
	} u;

	enum {NonTerminal, Terminal} kind;
} Item; // used in the stack

typedef struct {
	Var variables[MAX_VAR_PER_TABLE];
	int val_len;
	int offset;
	int lev;
} Table;

Table tables[MAX_TABLE_N];
int table_top;

#endif