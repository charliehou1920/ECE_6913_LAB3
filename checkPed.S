.section .text
.align 2
.globl wait

#include "memoryMap.inc"
#include "GPIO.inc"

// a0 is milliseconds passed through the parameter
wait:
	addi sp, sp, -16
	sw ra, 12(sp)

	li t0, MTIME
	li t1, GPIO_CTRL_ADDR
	lw t2, 0(t0)    // here t2 is current time
	li t3, MTIME_FREQUENCY
	mul t3, t3, a0
	add t3, t3, t2  // t3 is time to return
	
1:
	lw t2, GPIO_INPUT_VAL(t1)   // here t2 is GPIO input value
	and t2, t2, GPIO_PIN_15
	beqz t2, pressed            // when input is 0, button is pressed
	lw t2, 0(t0)
	blt t2, t3, 1b
	li a0, 0
	j exit
pressed:
	li a0, 1
exit:
	lw ra, 12(sp)
	addi sp, sp, 16
	ret
