#include "lain.h"
#include "str.h"
#include "../kernel/kb.h"
#include "../kernel/vga.h"
#include <stdbool.h>
#include "../kernel/mem.h"

static char lain_buffer[256];

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

void lain_print()
{
        char *param = lain_buffer + split_spaces(lain_buffer, 1);
        print_string(param);
        print_nl();
}

void lain_clear()
{
        clear_screen();
}

uint8_t lain_compare(char *command, void (*lain_do)(void))
{

        bool has_space = true;
        int i = 1;
        while (lain_buffer[i] != ' ')
        {
                if (lain_buffer[i] == '\0')
                {
                        has_space = false;
                };
                ++i;
        }

        char *buffer_command = mem_alloc(i);
        if (has_space)
        {
                for (int j = 0; j < i; j++)
                {
                        buffer_command[j] = lain_buffer[j];
                }
                buffer_command[i] = '\0';
        }
        else
        {
                buffer_command = lain_buffer;
        }

        if (compare_string(buffer_command, command, false) == 0)
        {
                lain_do();
                return 1;
        }
        mem_free(buffer_command);
        return 0;
}

void lain_parse()
{
        uint8_t result = 0;
        result += lain_compare("HELP", lain_help);
        result += lain_compare("HALT", lain_halt);
        result += lain_compare("PRINT", lain_print);
        result += lain_compare("CLEAR", lain_clear);

        if (result == 0)
        {
                print_string("Unknown command: ");
                print_string(lain_buffer);
                print_string(", maybe try HELP?\n");
        }
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
                lain_parse();
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
        lain_shell();
}
