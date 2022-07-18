#include "lain.h"
#include "str.h"
#include "lex.h"
#include "../kernel/kb.h"
#include "../kernel/vga.h"
#include "../kernel/mem.h"
#include "../kernel/utils.h"

static char *lain_buffer;

void lain_shell()
{
        lain_buffer[0] = '\0';
        print_string("lain> ");
}

void lain_help()
{
        print_string("lain - the general purpose interpreter for FuminOS\n");
        print_string("usage: <command> arg1 arg2 ...\navailable commands:\n");
        print_string("        CLEAR - clears screen\n");
        print_string("        HALT - exits FuminOS\n");
        print_string("        HELP - shows this menu\n");
        print_string("        PRINT - puts a string on screen\n");
}

void lain_halt()
{
        print_string("Goodbye. Stopping the CPU.");
        asm volatile("hlt");
}

void lain_print(char *msg)
{
        print_string(msg);
        print_nl();
}

void lain_clear()
{
        clear_screen();
}

void lain_type(uint8_t scancode, char letter)
{
        if (scancode == BACKSPACE)
        {
                lain_backspace();
                return;
        }
        else if (scancode == ENTER)
        {
                print_nl();
                parse_term(&lain_buffer, PREC_PAR);
                lain_shell();
                return;
        }

        append(lain_buffer, letter);
        char str[2] = {letter, '\0'};
        print_string(str);
}

void lain_backspace()
{
        int len = string_length(lain_buffer);
        if (len > 0)
        {
                lain_buffer[len - 1] = '\0';
                print_backspace();
        }
}

void lain_init()
{
        print_string("lain - the general purpose interpreter for FuminOS\n");
	lain_buffer = (char *)mem_alloc(sizeof(char) * 256);
	//*lain_buffer = '\0';
        lain_shell();
}

void lain_debug(char *msg) {
	print_string("DEBUG: ");
	print_string(msg);
	print_nl();
}
