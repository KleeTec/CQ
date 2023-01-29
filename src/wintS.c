#include <malloc.h>
#include "include/lexer/wintS.h"

/**
 * @param str ==> a string of chars to convert to wint_t
 * @param length ==> the length of the string + 1 (because of null-character)
 * @return an array of wint_t with the chars from str in it
 */
wint_t* wint_string(const char* str, size_t length) {
	wint_t* result = calloc(length, sizeof *result);
	for(size_t i = 0; i < length; ++i) {
		result[i] = (wint_t) str[i];
	}
	return result;
}