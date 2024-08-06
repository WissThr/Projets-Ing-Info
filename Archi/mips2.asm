	addi $s1, $0, 14
	addi $s2, $0, 3
	add $s3, $zero $zero
	add $s4, $zero $zero
	beq $s1, $0, fin
div:	slt $t1, $s1, $s2
	beq $t1, 1, fin
	addi $s3, $s3, 1
	sub $s1, $s1, $s2
	j div
fin:	add $s4, $s4, $s1
	move $a0, $s3
	li $v0, 1
	syscall
	move $a0, $s4
	li $v0, 1
	syscall
	li $v0, 10
	syscall