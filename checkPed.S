.section .text
.align 2
.globl wait

#include "memoryMap.inc"
#include "GPIO.inc"

# a0 is milliseconds passed through the parameter
checkPed:
	addi sp, sp, -16
	sw ra, 12(sp)

	li t0, MTIME	# load the timer register
	li t1, GPIO_CTRL_ADDR 
	lw t2, 0(t0)    # load the current value of the timer
	li t3, MTIME_FREQUENCY # get our approximate clock freq
	mul t3, t3, a0 # multiply milliseconds with freq
	add t3, t3, t2  # the target MTIME is now in t3


	
1:
	lw t2, GPIO_INPUT_VAL(t1) # load GPIO input value into t2
	and t2, t2, PIN_15	# get the value from PIN_15
	beqz t2, pressed
	lw t2, 0(t0)
	blt t2, t3, 1b	# keep looping until time out
	li a0, 0
	j exit

pressed:
	li a0, 1 # load 1 into a0


exit:
	lw ra, 12(sp)
	addi sp, sp, 16
	ret
