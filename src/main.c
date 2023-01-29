#include <locale.h>
#include "include/io_handler.h"
#include "include/compiler.h"

int main() {
	setlocale(LC_ALL, "");
	wprintf(L"Welcome to CQbd. The funny pun on 'C cubed'\n");
	char* fileName = "examples/main.cq";
	cq_ReadResult input = cq_readUtf8File(fileName);
	if (input.result == NULL) exit_error(EXIT_FAILURE, "file not found: '%s'", fileName);
	wprintf(L"--------\n"
		  "%ls\n"
		  "--------\n", input.result);
	char* llvm_IR = cq_compile(input.result, input.length);
	wprintf(L"LLVM IR: %s", llvm_IR);
	free(input.result);
	free(llvm_IR);
}
