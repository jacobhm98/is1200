.text

	addi	$a0, $0, 3	#n
	add	$v0, $a0, $0	#n
	addi	$a1, $0, 0	#i
	beq	$a0, $0, zero	#if n is equal to 0, set v0 to 1 and end
	add	$0, $0, $0	#nop

factloop:
	addi	$a1, $a1, 1	#increment i
	beq	$a0, $a1, done	#if i is equal to n, we are done
	add	$0, $0, $0	#nop
	add	$a3, $a1, $0	#move i to temporary value
	add	$v1, $v0, $0
	beq	$0, $0, multiply	#jump to multiplyl
	add	$0, $0, $0

multiply:
	addi	$a2, $0, 1
	beq	$a3, $a2, factloop
	add	$0, $0, $0
	add	$v0, $v1, $v0	
	addi	$a3, $a3, -1
	beq	$0, $0, multiply
	add	$0, $0, $0

zero:
	addi	$v0, $0, 1
	beq	$0, $0, done
	add	$0, $0, $0
	
done:
	add	$0, $0, $0
	beq	$0, $0, done
	add	$0, $0, $0