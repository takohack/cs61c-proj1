.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
	# Prologue
	li t0, 1
	blt a1, t0, end
	li t1, 0
loop_start:
	beq t1,a1,endnormal
	slli t2, t1, 2
	add t3,a0,t2
	lw t4 0(t3)
	bge t4 x0 big
	sw x0 0(t3)
big:
	addi t1 ,t1 ,1
	jal x0, loop_start
end:
	li a0, 36
	j  exit

endnormal:
	li a0 0
    jal exit








loop_continue:



loop_end:


	# Epilogue


	ret
