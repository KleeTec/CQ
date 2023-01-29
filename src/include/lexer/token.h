#pragma once
#include <wchar.h>
#include "../linked_list.h"

typedef enum TokenType {
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_INCREMENT,
	TOKEN_DECREMENT,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_SLASH,
	TOKEN_OPEN_PARENTHESIS,
	TOKEN_CLOSE_PARENTHESIS,
	TOKEN_OPEN_CURLY_PARENTHESIS,
	TOKEN_CLOSE_CURLY_PARENTHESIS,
	TOKEN_EQUALS,
	TOKEN_COLON,
	TOKEN_COMMA,
	TOKEN_IDENTIFIER,
	TOKEN_END_OF_EXPRESSION = -1,
	TOKEN_BAD = -2,
} TokenType;

typedef struct Token {
	wint_t* value;
	TokenType type;
} * Token;

typedef struct Position {
	size_t line;
	size_t character;
} Position;

Token Token_new(TokenType type);
void Token_free(Token token);
void Token_setValue(Token token, wint_t* inputStart, size_t length);
void Token_print(Token token);
wint_t* Token_stringify(Token token);