#pragma once
#include <stdlib.h>
#include <wchar.h>

typedef struct cq_ReadResult {
	wint_t* result;
	long length;
} cq_ReadResult;

cq_ReadResult cq_readLine();
cq_ReadResult cq_readUtf8File(char* location);
void exit_error(int exit_code, char* reason, ...);
