  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw  \reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
.data
.globl hexasc
.globl time2string
.globl delay
.globl enable_interrupt
.text

enable_interrupt:
	ei
	jr	$ra
	nop

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

delay:
	addi	$a0, $a0, -1
	addi	$t0, $zero, 0
	addi	$a1, $zero, 2000
	bne	$a0, -1, forloop
	nop
return:
	jr	$ra
	nop

forloop:
	addi	$t0, $t0, 1
	beq	$t0, $a1, delay
	nop
	j	forloop
	nop



time2string:
	PUSH $ra
	PUSH $s0
	move	$s0, $a0
	andi	$a0, $a0, 0x0
	andi	$a1, $a1, 0xffff
	move 	$a0, $a1
	andi	$a0, 0xf000
	srl	$a0, $a0, 12
	jal	hexasc
	nop
	sb	$v0, 0($s0)
	
	move 	$a0, $a1
	andi	$a0, 0xf00
	srl	$a0, $a0, 8
	jal	hexasc
	nop
	sb	$v0, 1($s0)
	
	addi	$t2, $zero, 0x3a
	sb	$t2, 2($s0)
	
	move 	$a0, $a1
	andi	$a0, 0xf0
	srl	$a0, $a0, 4
	jal	hexasc
	nop
	sb	$v0, 3($s0)
	
	move 	$a0, $a1
	andi	$a0, 0xf
	addi	$t1, $zero, 2
	beq	$a0, $t1, two
	nop

	jal	hexasc
	nop
	sb	$v0, 4($s0)
	
	addi	$t5, $zero, 0x0
	sb	$t5, 5($s0)
continue:

	POP	$s0
	POP	$ra
	jr	$ra
	nop
	
	
two:	
	andi	$a0, $a0, 0
	addi	$a0, $zero, 84
	sb	$a0, 4($s0)
	andi	$a0, $a0, 0
	addi	$a0, $0, 87
	sb	$a0, 5($s0)
	andi	$a0, $a0, 0
	addi	$a0, $zero, 79
	sb	$a0, 6($s0)
	andi	$a0, $a0, 0
	sb	$a0, 7($s0)
	j	continue
	nop