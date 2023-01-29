#include "include/io_handler.h"
#include <malloc.h>
#include <stdarg.h>
#include <wchar.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>

cq_ReadResult cq_readUtf8File(char* location) {
	cq_ReadResult returnVal = { 0 };
	// open the file to read
	FILE* file = fopen(location, "r");
	if (file == NULL) return returnVal;
	// calculating the size of the file
	struct stat st;
	stat(location, &st);
	long length = st.st_size;
	// currently only supports files with up to LONG_MAX length
	if (length > LONG_MAX) exit_error(EXIT_FAILURE, "file size too big to fit in a long int");
	wint_t* result = calloc(100, sizeof *result);
	// read every char at the time
	for(int i = 0; i < 99; ++i) {
		wint_t ch = getwc(file);
		if (ch == WEOF) break;
		result[i] = ch;
	}
	returnVal.length = length;
	returnVal.result = result;
	fclose(file);
	return returnVal;
}

void exit_error(int exit_code, char* reason, ...) {
	fflush(stdout);
	va_list args;
	va_start(args, reason);
	vfprintf(stderr, reason, args);
	va_end(args);
	fflush(stderr);
	exit(exit_code);
}