#pragma once

#include "../kernel/utils.h"

void lain_shel();
void lain_init();
void lain_type(uint8_t scancode, char letter);
void lain_backspace();

void lain_clear();
void lain_help();
void lain_halt();
void lain_print(char *msg);
void lain_debug(char *msg);