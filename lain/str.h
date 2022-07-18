#pragma once

#include "../kernel/utils.h"

int string_length(char s[]);
void append(char s[], char n);
int compare_string(char s1[], char s2[], bool only_first_word); 
int split_spaces(char *str, int spaces);
void string_copy(char *str1, char *str2); 