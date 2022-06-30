.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
	# Prologue
	ebreak
	li t0, 1
	blt a1,t0, bad_end
	li t1, 0 
	beq  a1,t0,normal_end
	li t2, 1 
	li t3, 0 
loop_start:
	beq t2,a1,loop_end
	slli a2, t2 , 2
	slli a3, t1 , 2
	add a3 ,a3 , a0
	add a2, a2, a0
	lw t5, 0(a2)
	lw t4,0(a3)
	bge t5 t4 handle
	# 特殊处理 t4 比较大 和最大的比
	slli a4,t3, 2
	add a4,a4,a0
	lw a5, 0(a4)
	blt a5, t4,handle
	add t3, x0, t1
handle:
	addi t1, t1, 1
	addi t2, t2, 1
	jal x0, loop_start
loop_end:
	# Epilogue
	add a0,x0,t3
	j exit
bad_end:
	li a0, 36
	j  exit
normal_end:
	li a0, 0
	j exit

