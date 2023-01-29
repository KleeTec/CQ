#include <ctype.h>
#include <string.h>
#include "include/lexer/lexer.h"
#include "include/lexer/token.h"
#include "include/io_handler.h"
#include "include/lexer/wintS.h"


struct LexerData Lexer = { 0 };


LinkedList cq_tokenize(wint_t* input, size_t inputLen) {
	LinkedList tokens = LinkedList_new();
	Lexer.position.line = 1;
	Lexer.tokens = tokens;
	Lexer.inputLen = inputLen;
	Lexer.input = input;
	Lexer.character = input[0];

	while(Lexer.index < inputLen) {
		bool tokenFound = (
			cq_lex_empty()
			|| cq_lex_oneLineComment()
			|| cq_lex_number()
			|| cq_lex_plus()
			|| cq_lex_minus()
			|| cq_lex_star()
			|| cq_lex_slash()
			|| cq_lex_openParenthesis()
			|| cq_lex_closeParenthesis()
			|| cq_lex_openCurlyParenthesis()
			|| cq_lex_closeCurlyParenthesis()
			|| cq_lex_equals()
			|| cq_lex_colon()
			|| cq_lex_comma()
			|| cq_lex_identifier()
		);
		if (!tokenFound)
			exit_error(EXIT_FAILURE,
				     "illegal character '%c' at position %zu in line %zu\n",
				     Lexer.input[Lexer.index],
				     Lexer.position.character,
				     Lexer.position.line);
	}
	return tokens;
}

/**
 * increments the lexer index and updates the character
 * @return 1 if the index exceeds the input length; 0 on success
 */
int cq_lexer_next() {
	if (Lexer.index >= Lexer.inputLen) return 1;
	Lexer.character = Lexer.input[++Lexer.index];
	Lexer.position.line++;
	return 0;
}

bool cq_lex_empty() {
	if (isspace(Lexer.character)){
		if (Lexer.character == '\n'){
			Lexer.position.line++;
			Lexer.position.character = 0;
		}
		cq_lexer_next();
		return true;
	}
	return false;
}

bool cq_lex_oneLineComment() {
	if (Lexer.character == '/'){
		cq_lexer_next();
		if (Lexer.character == '/'){
			cq_lexer_next();
			while(Lexer.character != '\n') if (cq_lexer_next()) break;
			return true;
		}
	}
	return false;
}

bool cq_lex_number_hex() {
	if (!isxdigit(Lexer.character)) return false;
	size_t start = Lexer.index - 1;
	while(!cq_lexer_next()) {
		// Zahlen können mit einem "'" dazwischen geschrieben werden. Also zum Beispiel: 100'000 statt 100000
		if (!isxdigit(Lexer.character) && Lexer.character != '\'') break;
	}
	Token number = Token_new(TOKEN_NUMBER);
	Token_setValue(number, Lexer.input + start, Lexer.index - start);
	LinkedList_append(Lexer.tokens, number);
	return true;
}

bool cq_lex_number() {
	if (Lexer.character == '#'){
		cq_lexer_next();
		return cq_lex_number_hex();
	}
	if (Lexer.character == '~'){
		cq_lexer_next();
//		cq_lex_number_bin();
	}
	return false;
}

bool cq_lex_plus() {
	if (Lexer.character == '+'){
		cq_lexer_next();
		if (Lexer.character == '+'){
			// increment
			Token inc = Token_new(TOKEN_INCREMENT);
			inc->value = wint_string("++", 3);
			LinkedList_append(Lexer.tokens, inc);
			return true;
		}
		Token plus = Token_new(TOKEN_PLUS);
		plus->value = wint_string("+", 2);
		LinkedList_append(Lexer.tokens, plus);
		return true;
	}
	return false;
}

bool cq_lex_minus() { return false; }

bool cq_lex_star() { return false; }

bool cq_lex_slash() { return false; }

bool cq_lex_openParenthesis() {
	if (Lexer.character == '('){
		Token openParen = Token_new(TOKEN_OPEN_PARENTHESIS);
		openParen->value = wint_string("(", 2);
		LinkedList_append(Lexer.tokens, openParen);
		cq_lexer_next();
		return true;
	}
	return false;
}

bool cq_lex_closeParenthesis() {
	if (Lexer.character == ')'){
		Token closeParen = Token_new(TOKEN_CLOSE_PARENTHESIS);
		closeParen->value = wint_string(")", 2);
		LinkedList_append(Lexer.tokens, closeParen);
		cq_lexer_next();
		return true;
	}
	return false;
}

bool cq_lex_openCurlyParenthesis() {
	if (Lexer.character == '{'){
		Token openParen = Token_new(TOKEN_OPEN_CURLY_PARENTHESIS);
		openParen->value = wint_string("{", 2);
		LinkedList_append(Lexer.tokens, openParen);
		cq_lexer_next();
		return true;
	}
	return false;
}

bool cq_lex_closeCurlyParenthesis() {
	if (Lexer.character == '}'){
		Token closeParen = Token_new(TOKEN_CLOSE_CURLY_PARENTHESIS);
		closeParen->value = wint_string("}", 2);
		LinkedList_append(Lexer.tokens, closeParen);
		cq_lexer_next();
		return true;
	}
	return false;
}

bool cq_lex_equals() { return false; }

bool cq_lex_colon() { return false; }

bool cq_lex_comma() { return false; }

bool cq_lex_identifier() {
	if (isalpha(Lexer.character)){
		size_t start = Lexer.index;
		while(!cq_lexer_next()) {
			if (!isalnum(Lexer.character)) break;
		}
		Token identifier = Token_new(TOKEN_IDENTIFIER);
		Token_setValue(identifier, Lexer.input + start, Lexer.index - start);
		LinkedList_append(Lexer.tokens, identifier);
		return true;
	}
	return false;
}