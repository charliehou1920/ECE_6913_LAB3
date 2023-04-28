.section .text
.align 2
.globl delay
#include "memoryMap.inc"
# a0 is milliseconds passed through the parameter
delay:
    addi sp, sp, -16 # allocate a stack frame, moves the stack up by 16 bits
    sw ra, 12(sp) # save return address on stack
    li t0, MTIME # load the timer register
    lw t1, 0(t0) # load the current value of the timer
    li t2, MTIME_FREQUENCY
    mul t2, t2, a0
    add t2, t1, t2

# get our approximate clock freq
# multiply milliseconds with freq
# the target MTIME is now in t2

1:
    lw t1, 0(t0)
    blt t1, t2, 1b

# read M value again
# keep looping until time out

    lw ra, 12(sp)
    addi sp, sp, 16
    ret