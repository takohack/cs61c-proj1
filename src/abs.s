.globl abs

.text
# =================================================================
# FUNCTION: Given an int return its absolute value.
# Arguments:
#   a0 (int) is input integer
# Returns:
#   a0 (int) the absolute value of the input
# =================================================================
abs:
	# ebreak
	# Prologue
	bge a0, zero, done

	# PASTE HERE
	sub a0, x0, a0
	# Epilogue
done:
	ret
