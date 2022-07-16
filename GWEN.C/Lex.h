#pragma once

#include "Utils.h"

#define TK_EOF 0

typedef struct {
        int token_number
} LexToken;

int Lex(char *src, LexList tokens);