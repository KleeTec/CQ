#include "include/parser/parser.h"
#include "include/io_handler.h"
#include "include/parser/conversion.h"

struct Parser Parser = { 0 };


Node cq_parseTokens(LinkedList tokens) {
	Node ast = Node_new(NODE_PROGRAM);
	ast->program.children = LinkedList_new();
	Parser.item = tokens->first;
	Parser.token = Parser.item->content;
	while(Parser.item != NULL) {
		LinkedList_append(ast->program.children, cq_parseNode());
		cq_parser_nextToken();
	}
	return ast;
}

bool cq_parser_token_matches(const char* str) {
	int i = 0;
	while(true) {
		if (str[i] == '\0') return Parser.token->value[i] == '\0';
		if ((wint_t) str[i] != Parser.token->value[i]) return false;
		i++;
	}
}

void cq_parser_nextToken() {
	Parser.item = Parser.item->next;
	if (Parser.item) Parser.token = Parser.item->content;
}

Node cq_parseNode() {
	switch(Parser.token->type) {
		case TOKEN_IDENTIFIER:
			return cq_parse_identifier();
		case TOKEN_NUMBER:
			return cq_parse_number();
		case TOKEN_PLUS: {
			Node node = Node_new(NODE_EXPRESSION_BINARY);
			node->expression_binary.type = EXPRESSION_BINARY_ADD;
			return node;
		}
		default: {
			exit_error(EXIT_FAILURE, "illegal token:\n\t%ls", Token_stringify(Parser.token));
			return NULL;
		}
	}
}

Node cq_parse_identifier() {
	if (cq_parser_token_matches("fnc"))
		return cq_parse_function();
	if (cq_parser_token_matches("return"))
		return cq_parse_return();

	exit_error(EXIT_FAILURE, "unknown identifier:\n\t%ls", Token_stringify(Parser.token));
	return NULL;
}

Node cq_parse_function() {
	Node node = Node_new(NODE_FUNCTION_DECLARATION);
	// Param
	// Name
	cq_parser_nextToken();
	if (Parser.token->type != TOKEN_IDENTIFIER)
		exit_error(EXIT_FAILURE, "function name expected at %ls", Parser.token->value);
	node->function.name = Parser.token->value;
	// Param
	// Definition
	cq_parser_nextToken();
	if (cq_parser_token_matches("{")){
		node->type = NODE_FUNCTION_DEFINITION;
		node->function.children = LinkedList_new();
		cq_parser_nextToken();
		while(!cq_parser_token_matches("}")) {
			LinkedList_append(node->function.children, cq_parseNode());
			cq_parser_nextToken();
		}
	}
	if (cq_parser_token_matches(";")) return node;
	return node;
}

Node cq_parse_number() {
	Node node = Node_new(NODE_LITERAL_NUMBER);
	node->literal_int.value = wintS2int(Parser.token->value, 0);
	return node;
}

Node cq_parse_return() {
	Node node = Node_new(NODE_RETURN);
	return node;
}