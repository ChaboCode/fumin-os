#pragma once

#include "../kernel/utils.h"

/********************
 * LEXICAL ANALYSER *
 ********************/

#define IN_PRINT "PRINT"
#define IN_CLEAR "CLEAR"
#define IN_HELP "HELP"
#define IN_HALT "HALT"

#define TK_EOF		0
#define TK_EOL		1
#define TK_NUM		2
#define TK_OP		3
#define TK_PAR_LEFT	4
#define TK_PAR_RIGHT	5

// TODO: Symbols table
#define TK_CLEAR	100
#define TK_PRINT	101
#define TK_HELP		102
#define TK_HALT		103

#define PREC_EOF	0
#define PREC_EXPR	1
#define PREC_TERM	2
#define PREC_MUL	3
#define PREC_ADD	4
#define PREC_PAR	5  // Parenthesis

typedef struct symbol_entry
{
	char *identifier;
	void *value;
} symbol_entry_t;

static symbol_entry_t *symbols_table;

#define OP_SUM 1
#define OP_SUB 2
#define OP_MUL 3
#define OP_DIV 4

static int32_t result;

uint8_t lex(char **src, int32_t *return_number);
uint8_t parse_term(char **code, uint8_t highest_prec);
