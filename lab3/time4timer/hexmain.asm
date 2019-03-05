  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,15		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc:
	andi	$a0, $a0, 15	#mask the 4 least significant bits
	slti 	$t0, $a0, 10	#break condition
	beq	$t0, $zero, letter
	nop
	j	number
	nop
	
number:
	addi	$a0, $a0, 48
	add	$v0, $a0, $zero
	andi	$v0, $v0, 127
	jr	$ra
	nop

letter:
	addi	$a0, $a0, 87
	add	$v0, $a0, $zero
	andi	$v0, $v0, 127
	jr	$ra
	nop
	
	
	
