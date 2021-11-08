#include "def.h"

const char keychars[] = {'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':'};

const char* SYM_table[] = {
	[NUL_TYPE] 	"",	// null

	// Keywords
	[K_BEGIN] 	"begin",
	[K_CALL] 	"call",
	[K_CONST] 	"const",
	[K_DO] 		"do",
	[K_END] 	"end",
	[K_IF]		"if",
	[K_ODD]		"odd",
	[K_PROCEDURE]"procedure",
	[K_READ]	"read",
	[K_THEN]	"then",
	[K_VAR]		"var",
	[K_WHILE]	"while",
	[K_WRITE]	"write",

	// Operators
	[O_PLUS]	"+",
	[O_MINUS]	"-",
	[O_MULTI]	"*",
	[O_DIV]		"/",
	[O_ASSIGN]	":=",
	[O_EQ]		"=",
	[O_LESS]	"<",
	[O_LEQ]		"<=",
	[O_GTR]		">",
	[O_GEQ]		">=",
	[O_NEQ]		"#",

	// Delimiters
	[D_COMMA]	",",
	[D_SEMICOLON]";",
	[D_PERIOD]	".",
	[D_LP]		"(",
	[D_RP]		")",
};

const char* SYM_name[] = {
	[NUL_TYPE] 	"NUL_TYPE",	// null

	// Keywords
	[K_BEGIN] 	"K_BEGIN",
	[K_CALL] 	"K_CALL",
	[K_CONST] 	"K_CONST",
	[K_DO] 		"K_DO",
	[K_END] 	"K_END",
	[K_IF]		"K_IF",
	[K_ODD]		"K_ODD",
	[K_PROCEDURE]"K_PROCEDURE",
	[K_READ]	"K_READ",
	[K_THEN]	"K_THEN",
	[K_VAR]		"K_VAR",
	[K_WHILE]	"K_WHILE",
	[K_WRITE]	"K_WRITE",

	// Operators
	[O_PLUS]	"O_PLUS",
	[O_MINUS]	"O_MINUS",
	[O_MULTI]	"O_MULTI",
	[O_DIV]		"O_DIV",
	[O_ASSIGN]	"O_ASSIGN",
	[O_EQ]		"O_EQ",
	[O_LESS]	"O_LESS",
	[O_LEQ]		"O_LEQ",
	[O_GTR]		"O_GTR",
	[O_GEQ]		"O_GEQ",
	[O_NEQ]		"O_NEQ",

	// Delimiters
	[D_COMMA]	"D_COMMA",
	[D_SEMICOLON]"D_SEMICOLON",
	[D_PERIOD]	"D_PERIOD",
	[D_LP]		"D_LP",
	[D_RP]		"D_RP",
};

SYM getKeywordType(const char* str) {
	int i;
	for (i = K_BEGIN; i <= K_WRITE; i++) {
		if (strcmp(str, SYM_table[i]) == 0) {
			return (SYM) i;
		}
	}

	return NUL_TYPE;
}

SYM getSpecialType(const char* str) {
	int i;
	for (i = O_PLUS; i <= D_RP; i++) {
		if (strcmp(str, SYM_table[i]) == 0) {
			return (SYM) i;
		}
	}

	return NUL_TYPE;
}

int isLetter(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

int isSpecial(char ch) {
	if (ch == ' ' || ch == 0) return 0;

	int i;
	for (i = 0; i < KEYCHAR_N; i++) {
		if (keychars[i] == ch) return 1;
	}
	return -1;
}

void print_token(FILE* out, Token *token) {
	SYM symbol = token->sym;

	if (symbol == ID) {
		fprintf(out, "ID             %s\n", token->id);
	} else if(symbol == NUMBER) {
		fprintf(out, "NUM            %d\n", token->num);
	} else {
		fprintf(out, "%-15s%s\n", SYM_name[token->sym], SYM_table[token->sym]);
	}
}