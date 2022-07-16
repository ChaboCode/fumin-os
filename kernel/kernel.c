#include "vga.h"
#include "kb.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "utils.h"
#include "mem.h"
#include "../lain/lain.h"

void main() {
    clear_screen();
    print_string("It works\nAmazing\n");
    print_string("Installing ISRs... ");
    isr_install();
    print_string("done!\nEnabling external inputs... ");
    asm volatile("sti");
    print_string("done!\nInit kb... \n");
    init_keyboard();
    clear_screen();
    
    lain_init();
}
