#include "def.h"

const char* keywords[] = {"begin", "call", "const", "do", "end", "if", "odd", "procedure", "read", "then", "var", "while", "write"};

const char keychars[] = {'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':'};

const char* special_chars[] = {"+", "-", "*", "/", ":=", "=", "<", "<=", ">", ">=", "#", ",", ";", ".", "(", ")"};

SYM getKeywordType(const char* str) {
	int i;
	for (i = 0; i < KEYWORD_N; i++) {
		if (strcmp(str, keywords[i]) == 0) {
			return (SYM) (i + 1);
		}
	}

	return NUL_TYPE;
}

SYM getSpecialType(const char* str) {
	int i;
	for (i = 0; i < SPECIAL_N; i++) {
		if (strcmp(str, special_chars[i]) == 0) {
			return (SYM) (i + KEYWORD_N + 1);
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

void strrm(char str[], int *index, int *len) {
	int i;
	for (i = 0; str[i]; i++) {
		if (i >= *index) {
			str[i] = str[i + 1];
		}
	}

	(*index) --;
	(*len) --;
}