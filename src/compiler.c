#include "include/compiler.h"
#include "include/lexer/lexer.h"
#include "include/parser/parser.h"
#include <wchar.h>


/**
 * compiles the given input to llvm IR
 * @param input ==> the string to compile
 */
char* cq_compile(wint_t* input, size_t inputLen) {
	LinkedList tokens = cq_tokenize(input, inputLen);
	LinkedList_print(tokens, printFunction_cast(Token_print));
	wprintf(L"--------\n");
	Node ast = cq_parseTokens(tokens);
	wprintf(L"%d", ast->type);
	LinkedList_free(tokens, freeFunction_cast(Token_free));
	return NULL;
}


