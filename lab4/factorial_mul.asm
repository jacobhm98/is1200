.text

	addi	$a0, $0, 4
	add	$v0, $0, $a0
	addi	$a0, $a0, -1
	addi	$a1, $0, 1
factloop:
	beq	$a0, $a1, done
	mul	$v0, $v0, $a0
	addi	$a0, $a0, -1
	beq	$0, $0, factloop
	
	
done:
	add	$0, $0, $0
	beq	$0, $0, done
	add	$0, $0, $0