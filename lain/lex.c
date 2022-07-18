#include "lex.h"
#include "lain.h"
#include "str.h"
#include "../kernel/mem.h"
#include "../kernel/utils.h"
#include "../kernel/utils.h"

static void (*next_func)(char *);
static char *arg;

uint8_t lex_func(char **code)
{
	char *mod_code = *code;
	
	arg = mod_code + 1;
	return TK_EOL;
}

bool is_this_function(char **code, char *func_str)
{
	uint8_t i;
	char *mod_code = *code;
	bool is_instruction = true;

	while (func_str[i] != '\0')
	{
		if (func_str[i] != *mod_code)
		{
			is_instruction = false;
			break;
		}

		++mod_code;
		++i;
	}

	if (is_instruction)
	{
		*code = mod_code;
		return true;
	}

	return false;
}

uint8_t lex(char **code, int32_t *return_number)
{
	char *mod_code = *code;
	int32_t number;

	switch (*mod_code)
	{
	case '\n':
		return TK_EOF;
	case ' ':
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
		do
		{
			// Shift number: 13 --> 130
			// Convert char to number
			// Add it
			number = (int32_t)number * 10 + **code - '0';
			mod_code++;
		} while ('0' <= *mod_code && *mod_code <= '9');
		*return_number = number;
		*code = mod_code;
		return TK_NUM;

	default:
		break;
	}

	if (**code == IN_CLEAR[0])
	{
		if(is_this_function(code, IN_CLEAR)) {
			return TK_CLEAR;
		}
	} else if (**code == IN_PRINT[0]) {
		if(is_this_function(code, IN_PRINT)) {
			return TK_PRINT;
		}
	} else if (**code == IN_HELP[0]) {  // || **code == IN_HALT[0]
		if(is_this_function(code, IN_HELP)) {
			return TK_HELP;
		}
		if(is_this_function(code, IN_HALT)) {
			return TK_HALT;
		}
	}
	
	return TK_EOL;
}

uint8_t parse(char **code)
{
	int32_t number;
	switch (lex(code, &number))
	{
	case TK_NUM:
		result += number;
		return PREC_TERM;
	case TK_CLEAR:
		next_func = lain_clear;
		return PREC_EXPR;
	case TK_PRINT:
		next_func = lain_print;
		return PREC_EXPR;
	case TK_HELP:
		next_func = lain_help;
		return PREC_EXPR;
	case TK_HALT:
		next_func = lain_halt;
		return PREC_EXPR;
	case TK_EOL:
	case TK_EOF:
		return PREC_EOF;
	default:
		break;
	}
}

uint8_t parse_term(char **code, uint8_t highest_prec)
{
	uint8_t current_prec;
	char *mod_code;
	while (1)
	{
		mem_free(arg);
		switch (parse(code))
		{
		case PREC_EXPR:
			lex_func(code);
			next_func(arg);
			break;
		case PREC_EOF:
			return 0;

		default:
			break;
		}
	}
}
