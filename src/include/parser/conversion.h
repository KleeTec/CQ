#pragma once
#include <wchar.h>

int wintS2int(wint_t* input, size_t length);
void addHexChar(long* result, wint_t ch, unsigned int index);
void addDecChar(long* result, wint_t ch, unsigned int index);
void addBinChar(long* result, wint_t ch, unsigned int index);