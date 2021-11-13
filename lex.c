#include "def.h"

/*
* 
*/

int preprocess(int len) {
	int i = 0, status = 0;
	char ch;

	while(i < len) {
		ch = prog[i];

		switch (status)
		{
		case 0:
			if (ch == '/') status = 1;
			else if (ch == ' ') status = 5;
			else if (ch == '\r' || ch == '\n' || ch == '\t') {
				// strrm(prog, &i, &len);
				prog[i] = ' ';
			}
			break;
		
		case 1:
			if (ch == '/') status = 2;
			else if (ch == '*') status = 3;
			else {
				status = 0;
				i--;
			}
			break;

		case 2:
			if (ch == '\r' || ch == '\n') {
				status = 0;
				i --;
				// strrm(prog, &i, &len);
				// strrm(prog, &i, &len);
				prog[i++] = ' ';
				prog[i++] = ' ';
			} else {
				// strrm(prog, &i, &len);
				prog[i++] = ' ';
			}
			break;
		
		case 3:
			if (ch == '*') {
				// strrm(prog, &i, &len);
				prog[i++] = ' ';
				status = 4;
			} else {
				// strrm(prog, &i, &len);
				prog[i++] = ' ';
			}

			break;
		
		case 4:
			if (ch == '/') {
				// strrm(prog, &i, &len);
				// strrm(prog, &i, &len);
				// strrm(prog, &i, &len);
				prog[i++] = ' ';
				prog[i++] = ' ';
				prog[i++] = ' ';
				status = 0;
			} else if (ch == '*') {
				// strrm(prog, &i, &len);
				prog[i++] = ' ';
			} else {
				// strrm(prog, &i, &len);
				prog[i++] = ' ';
				status = 3;
			}

			break;
		
		case 5:
			if (ch == ' ') {
				// strrm(prog, &i, &len);
				prog[i++] = ' ';
			} else {
				status = 0;
				i--;
			}
		}

		i++;
	}

	return len;
}

char lookAhead(int i) {
	if (!prog[i + 1] || prog[i + 1] == ' ') return 0;

	return prog[i + 1];
}

STATE next_state(STATE cur_state, char last_read_ch, char nxt_ch) {
	int letter = isLetter(nxt_ch), digit = isDigit(nxt_ch), special = isSpecial(nxt_ch);

	if (!letter && !digit && !special && nxt_ch) return S_ERROR;

	if (!nxt_ch) return S_CHECK;
	if (nxt_ch == -1) return S_ERROR;

	switch (cur_state)
	{
	case S_START:
		if (letter) return S_STRING;
		if (digit) return S_NUM;
		if (special) return S_SPEC1;

		break;
	case S_STRING:
		if (letter) return S_STRING;
		if (digit) return S_ID;
		if (special) return S_CHECK;

		break;
	case S_ID:
		if (letter) return S_ID;
		if (digit) return S_ID;
		if (special) return S_CHECK;

		break;
	case S_NUM:
		if (letter) return S_ERROR;
		if (digit) return S_NUM;
		if (special) return S_CHECK;
	
		break;
	case S_SPEC1:
		if (letter) return S_CHECK;
		if (digit) return S_CHECK;
		if (special) {
			if (nxt_ch == '=') {
				if (last_read_ch == ':' || last_read_ch == '>' || last_read_ch == '<') return S_SPEC2;
				else return S_CHECK;
			} else {
				return S_CHECK;
			}
		}
		break;	
	case S_SPEC2:
		return S_CHECK;
		break;
	case S_CHECK:
		return S_START;

	default:
		printf("[lexical]: unknown status\n");

		exit(-2);
	}

	return S_ERROR;
}

int getSYM(int len, FILE* err) {
	token_n = 0;

	int i = 0, str_len = 0, num = 0;

	char ch, str[MAX_ID_LEN];

	STATE status = S_START, last_status;

	while(i < len) {
		ch = prog[i];

		if (ch ==' ') {
			i++;
			continue;
		}

		if (status != S_CHECK) last_status = status;

		switch (status)
		{
		case S_START:
			status = next_state(status, ch, ch);

			memset(str, 0, sizeof(str));
			str_len = 0;
			num = 0;

			break;
		
		case S_STRING:
			str[str_len ++] = ch;
			
			status = next_state(status, ch, lookAhead(i));

			if (status != S_CHECK) i++;

			break;

		case S_ID:
			str[str_len ++] = ch;

			status = next_state(status, ch, lookAhead(i));

			if (status != S_CHECK) i++;

			break;

		case S_NUM:
			num = num * 10 + ch - '0';

			status = next_state(status, ch, lookAhead(i));

			if (status != S_CHECK) i++;

			break;

		case S_SPEC1:
			status = next_state(status, ch, lookAhead(i));

			str[str_len ++] = ch;
			if (status != S_CHECK) i++;

			break;

		case S_SPEC2:
			status = next_state(status, ch, lookAhead(i));
			str[str_len ++] = ch;

			if (status != S_CHECK) i++;

			break;

		case S_ERROR:
			fprintf(err, "[lexical]: analysis error unknown %s. [location]: %d \n", str, i);

			return -1;

		case S_CHECK:
			if (last_status == S_ID) {
				tokens[token_n].sym = ID;
				memcpy(tokens[token_n].id, str, str_len);
				// tokens[token_n].num;
				token_n ++;
			} else if (last_status == S_STRING) {
				SYM type = getKeywordType(str);

				if (type) {
					tokens[token_n].sym = type;
					memcpy(tokens[token_n].id, str, str_len);
					// tokens[token_n].num;
					token_n ++;
				} else {
					tokens[token_n].sym = ID;
					memcpy(tokens[token_n].id, str, str_len);
					// tokens[token_n].num;
					token_n ++;
				}
			} else if (last_status == S_NUM) {
				tokens[token_n].sym = NUMBER;
				tokens[token_n].num = num;
				token_n ++;
			} else if (last_status == S_SPEC1 || last_status == S_SPEC2) {
				SYM type = getSpecialType(str);

				if (type) {
					tokens[token_n].sym = type;
					token_n ++;
				} else {
					status = S_ERROR;

					break;
				}
			}

			status = S_START;

			i ++;

		default:
			break;
		}
	}

	return 0;
}

int lexical_analysis(FILE *in, FILE *out, FILE* err) {
	char ch;

	int len = 0;

	if (in) {
		while((ch = fgetc(in)) != EOF ) prog[len ++] = ch;
	}

	fprintf(out, "original code:\n%s\n", prog);
	len = preprocess(len);

	fprintf(out, "\n=======\nafter preprocessing\n%s\n", prog);
	fputc('\n', out);

	if (getSYM(len, err)) {
		return -1;
	}

	fprintf(out, "SYM name       SYM value\n");

	int i;
	for (i = 0; i < token_n; i++) {
		print_token(out, &tokens[i]);
	}

	return 0;
}

