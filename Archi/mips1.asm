	addi $s1, $0, 4
	addi $s2, $0, 6
	add $s3, $zero $zero
	beq $s1, $0, fin
multi:	beq $s2, $0, fin
	add $s3, $s3, $s1
	addi $s2, $s2, -1
	j multi
fin:	move $a0, $s3
	li $v0, 1
	syscall
	li $v0, 10
	syscall