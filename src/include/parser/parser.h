#pragma once
#include "../linked_list.h"
#include "node.h"

extern struct Parser {
	LinkedListItem item;
	Token token;
} Parser;

Node cq_parseTokens(LinkedList tokens);
Node cq_parseNode();
bool cq_parser_token_matches(const char* str);
void cq_parser_nextToken();
Node cq_parse_identifier();
Node cq_parse_function();
Node cq_parse_number();
Node cq_parse_return();