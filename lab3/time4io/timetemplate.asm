  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
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

delay:
	addi	$a0, $a0, -1
	addi	$t0, $zero, 0
	addi	$a1, $zero, 20000
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
	PUSH ($ra)
	PUSH ($s0)
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

	POP	($s0)
	POP	($ra)
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
	
	
	
	
	
	
	
	
	
