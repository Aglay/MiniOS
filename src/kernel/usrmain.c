#include <asm.h>
#include <syscall.h>
#include <usrmain.h>

static void halt() {
    while (1);
}

static int delay() {
    volatile int i;

    for (i = 0; i < 0x100000; i++);
    return i;
}

void user_main() {

    while (1) {
        if (call(SYS_FORK) != 0) {
            delay();
            call(SYS_WAIT);
        } else {
            call(SYS_EXEC);
            call(SYS_EXIT);
            break;
        }
    }

    halt();
}
