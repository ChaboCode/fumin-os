#include "Compiler.h"
#include "Lex.h"
#include "Utils.h"
#include "../kernel/vga.h"

// Just In Time compiling
int JIT() {

}
// Ahead Of Time compiling
int AOT(char *src, char *dst) {
        int err_code;
        LexList tokens;
        err_code = Lex(src, tokens);

        if (err_code) {
                print_string("Compilation failed. Exiting Gwen.\n");
                return GWN_ER_GENERIC;
        }
}