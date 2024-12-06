#include <rt_misc.h>

__value_in_regs struct __initial_stackheap __user_initial_stackheap(
    unsigned R0, unsigned SP, unsigned R2, unsigned SL) {
    struct __initial_stackheap config;
    config.heap_base = 0x0021fa7c;
    config.stack_base = 0x0043f4dc;
    return config;
}
