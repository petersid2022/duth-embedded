#include <rt_misc.h>

__value_in_regs struct __initial_stackheap __user_initial_stackheap(
    unsigned R0, unsigned SP, unsigned R2, unsigned SL) {
    struct __initial_stackheap config;
    config.heap_base = 0x007110e0;
    config.stack_base = 0x00a99510;
    return config;
}
