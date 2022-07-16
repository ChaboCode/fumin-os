#include "str.h"
#include <stdbool.h>
#include "../kernel/vga.h"

int string_length(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
}

void append(char s[], char n) {
    int len = string_length(s);
    s[len] = n;
    s[len + 1] = '\0';
}

int compare_string(char s1[], char s2[], bool only_first_word) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == ' ') return 0;
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int split_spaces(char *str, int spaces) {
        int spaces_counted = 0, i = 0;
        while(spaces_counted < spaces) {
                if(i >= string_length(str)) return 0;
                while (str[i] != ' ')
                {
                        ++i;
                }
                ++spaces_counted;
        }
        return ++i;        
}
