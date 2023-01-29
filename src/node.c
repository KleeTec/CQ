#include "include/parser/node.h"

Node Node_new(NodeType type) {
	Node result = malloc(sizeof *result);
	result->type = type;
	return result;
}