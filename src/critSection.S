        .globl disableInterrupts
        .type  disableInterrupts,%function
        .globl enableInterrupts
        .type  enableInterrupts,%function

// int disableInterrupts(void)
disableInterrupts:
        MRS r0, PRIMASK
        CPSID i
        BX lr

// void reenableInterrupts(int)
enableInterrupts:
        CPSIE i
        MSR PRIMASK, r0
        BX lr
