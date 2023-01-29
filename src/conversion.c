#include <math.h>
#include "include/parser/conversion.h"
#include "include/io_handler.h"

int wintS2int(wint_t* input, size_t length) {
	long result = 0;
	int base = 10;
	unsigned int index = 0;
	if (input[0] == (wint_t) '#'){
		base = 16;
		input++;
	} else if (input[0] == (wint_t) '~'){
		base = 2;
		input++;
	}

	wint_t ch = input[length - (( sizeof *input ) * index )];
	while(ch != 0) {
		if (base == 2) addBinChar(&result, ch, index);
		if (base == 10) addDecChar(&result, ch, index);
		if (base == 16) addHexChar(&result, ch, index);
		// update character ch to next wint
		index++;
		ch = input[length - (( sizeof *input ) * index )];
	}
	return (int) result;
}

void addHexChar(long* result, wint_t ch, uint index) {
	switch(ch) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			*result += ( ch - '0' ) * ((unsigned int) pow(16, index));
			break;
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			*result += ( ch - 'a' + 10 ) * (unsigned int) pow(16, index);
			break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			*result += ( ch - 'A' + 10 ) * (unsigned int) pow(16, index);
			break;
		default:
			exit_error(EXIT_FAILURE, "could not parse %lc to number", ch);
	}
}

void addDecChar(long* result, wint_t ch, uint index) {
	if (ch >= '0' && ch <= '9') *result += ( ch - '0' ) * ((unsigned int) pow(10, index));
	else exit_error(EXIT_FAILURE, "could not parse %lc to decimal number", ch);
}

void addBinChar(long* result, wint_t ch, uint index) {
	if (ch == '0' || ch == '1') *result += ( ch - '0' ) * ((unsigned int) pow(2, index));
	else exit_error(EXIT_FAILURE, "could not parse %lc to decimal number", ch);
}