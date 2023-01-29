#include <wchar.h>
#include <stdio.h>
#include <memory.h>
#include "include/io_handler.h"
#include "include/lexer/token.h"

Token Token_new(TokenType type) {
	Token tok = malloc(sizeof *tok);
	tok->type = type;
	return tok;
}

void Token_free(Token token) {
	free(token->value);
	free(token);
}

void Token_print(Token token) {
	wprintf(L"Token {"
		  "	%d,"
		  "	'%ls'"
		  "}",
		  token->type,
		  token->value);
}

wint_t* Token_stringify(Token token) {
	wint_t* result = malloc(100 * sizeof *result);
	// fill all with zero-width-characters
	for(int i = 0; i < 100; ++i) {
		result[i] = 0x200b;
	}
	// just copy 8 of the 9 bytes of the string because the null-character does not matter
	result[0] = 'T';
	result[1] = 'o';
	result[2] = 'k';
	result[3] = 'e';
	result[4] = 'n';
	result[5] = ' ';
	result[6] = '{';
	result[7] = ' ';
	char type[5] = { 0 };
	snprintf(type, 5, "%d", token->type);
	result[8] = (wint_t) type[0];
	if (type[1]) result[9] = (wint_t) type[1];
	if (type[2]) result[10] = (wint_t) type[2];
	if (type[3]) result[11] = (wint_t) type[3];
	if (type[4]) result[12] = (wint_t) type[4];
	result[13] = ',';
	result[14] = ' ';
	result[15] = '\'';
	for(int i = 0; i < 100 - ( 5 + 8 + 3 ) - 4; ++i) {
		if (token->value[i] == '\0') break;
		result[16 + i] = token->value[i];
	}
	result[95] = '\'';
	result[96] = ' ';
	result[97] = '}';
	result[98] = '\n';
	result[99] = '\0';
	return result;
}

void Token_setValue(Token token, wint_t* inputStart, size_t length) {
	token->value = calloc(length + 1 /* add one because null-character must be added */,
				    sizeof *token->value);
	memcpy(token->value, inputStart, length * ( sizeof *inputStart ));
}