#include "def.h"
#include "grammar.h"

/*************** lexical part ***************/

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

SYM getType(const char* str) {
	int i;
	for (i = K_BEGIN; i <= D_RP; i++) {
		if (strcmp(str, SYM_table[i]) == 0) {
			return (SYM) i;
		}
	}

	return NUL_TYPE;
}

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
		fprintf(out, "ID             %-19s%3d\n", token->id, token->row);
	} else if(symbol == NUMBER) {
		fprintf(out, "NUM            %-5d%17d\n", token->num, token->row);
	} else {
		fprintf(out, "%-15s%-15s%7d\n", SYM_name[token->sym], SYM_table[token->sym], token->row);
	}
}

/*************** syntax part ***************/

void read_map_table() {
	FILE* in = fopen("table.grammar", "r");

	// table info

	fscanf(in, "%d%d", &state_n, &symbols_n);

	int i, j;
	for (i = 0; i < state_n; i++) {
		for (j = 0; j < symbols_n; j++) {
			fscanf(in, "%d", &map_table[i][j]);
		}
	}

	// grammar length

	fscanf(in, "%d", &grammar_n);
	for (i = 0; i < grammar_n; i++) {
		fscanf(in, "%d", &grammar_length[i]);
	}

	// symbols indexed by table

	fscanf(in, "%d", &terminal_n);
	char t[16];

	for (i = 0; i < terminal_n; i++) {
		fscanf(in, "%s", t);
		if (strcmp(t, "$") == 0) {
			action_header[i] = D_PERIOD;
		} else if (strcmp(t, "id") == 0) {
			action_header[i] = ID;
		} else if (strcmp(t, "num") == 0) {
			action_header[i] = NUMBER;
		} else {
			action_header[i] = getType(t);
		}
	}


	// grammar LHS index in table goto header

	for (i = 0; i < grammar_n; i++) {
		fscanf(in, "%d", &grammar_index[i]);
	}

	fclose(in);
}

int get_next_action(int state, SYM input_sym) {
	int i;
	for (i = 0; i < terminal_n; i++) {
		if (input_sym == action_header[i]) {
			return map_table[state][i];
		}

		if (input_sym == O_MINUS && action_header[i] == O_PLUS) {
			return map_table[state][i];
		}

		if (input_sym == O_DIV && action_header[i] == O_MULTI) {
			return map_table[state][i];
		}
	}

	return 0;
}

int cur_state() {
	return state_stack[top];
}

void action_shift(int nxt_state) {
	state_stack[++top] = nxt_state;
}

void action_reduction(int grammar) {
	top -= grammar_length[grammar];

	if (grammar_index[grammar] < 0) {
		puts("[action_reduction]: grammar_index < 0!!!");
		exit(-1);
	}

	action_shift(map_table[cur_state()][grammar_index[grammar] + terminal_n]);
}