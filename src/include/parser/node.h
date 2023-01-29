#pragma once
#include <malloc.h>
#include "../linked_list.h"
#include "../lexer/token.h"

typedef enum NodeType {
	NODE_PROGRAM,
	NODE_LITERAL_NUMBER,
	NODE_EXPRESSION_BINARY,
	NODE_FUNCTION_DECLARATION,
	NODE_FUNCTION_DEFINITION,
	NODE_RETURN,
} NodeType;

typedef enum BinaryExpressionType {
	EXPRESSION_BINARY_ADD,
	EXPRESSION_BINARY_SUB,
	EXPRESSION_BINARY_DIV,
	EXPRESSION_BINARY_MUL,
	EXPRESSION_BINARY_AND,
	EXPRESSION_BINARY_OR,
	EXPRESSION_BINARY_XOR,
	EXPRESSION_BINARY_POW,
} BinaryExpressionType;

typedef struct Node {
	NodeType type;
	/**
	 * The different types of nodes
	 */
	union {
		struct {
			LinkedList children;
		} program;
		struct {
			wint_t* name;
			LinkedList children;
		} function;
		struct { int value; } literal_int;
		struct {
			struct Node* left;
			struct Node* right;
			BinaryExpressionType type;
		} expression_binary;
	};
} * Node;

Node Node_new(NodeType type);