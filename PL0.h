#ifndef PL0
#define PL0

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

/*************** lexical part ***************/

#define KEYWORD_N 13

#define KEYCHAR_N 13

#define SPECIAL_N 16

/*************** syntax part ***************/

#define MAX_VAR_PER_TABLE 32
#define MAX_TABLE_N 8
#define MAX_STACK_SIZE 1024
#define MAX_STATE_N 128
#define MAX_TERMS 64
#define MAX_LEV 12
#define MAX_ITEM_N 1024

typedef enum {
	T_CONST,
	T_VARIABLE,
	T_PROCEDURE
} TableTermType;

typedef enum {
	STK_NONT,
	STK_T
} StackTermType;

#endif