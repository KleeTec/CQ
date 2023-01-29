#pragma once
#include <wchar.h>
#include "../linked_list.h"
#include "token.h"


extern struct LexerData {
	Position position;
	LinkedList tokens;
	size_t index;
	wint_t* input;
	size_t inputLen;
	wint_t character;
} Lexer;

LinkedList cq_tokenize(unsigned int* input, size_t inputLen);
int cq_lexer_next();

bool cq_lex_empty();
bool cq_lex_oneLineComment();
bool cq_lex_number();
bool cq_lex_plus();
bool cq_lex_minus();
bool cq_lex_star();
bool cq_lex_slash();
bool cq_lex_openParenthesis();
bool cq_lex_closeParenthesis();
bool cq_lex_openCurlyParenthesis();
bool cq_lex_closeCurlyParenthesis();
bool cq_lex_equals();
bool cq_lex_colon();
bool cq_lex_comma();
bool cq_lex_identifier();