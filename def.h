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

//============= lexical part ================

#define KEYWORD_N 13

const char* keywords[KEYWORD_N];

#define KEYCHAR_N 13

const char keychars[KEYCHAR_N];

#define SPECIAL_N 16

const char* special_chars[SPECIAL_N];

SYM getKeywordType(const char* str);
SYM getSpecialType(const char* str);

int isLetter(char ch);
int isDigit(char ch);

int isSpecial(char ch);

void strrm(char str[], int *index, int *len);

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

#endif