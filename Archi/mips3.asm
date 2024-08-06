	addi $s1, $0, 10
	addi $s2, $0, 0
	addi $s3, $0, 1
	add $t0, $0, $0
	add $t4, $0, $0
	
verif:	slt $t1, $s2, $s1
	beq $t1, $0, fin
	
	addi $s2, $s2, 1
	add $t0, $s2, $0
	add $t4, $0, $0
	
multi:	beq $t0, $0, chg
	add $t4, $s3, $t4
	addi $t0, $t0, -1
	j multi
	
chg:	add $s3, $0, $t4
	j verif
	
fin:	move $a0, $s3
	li $v0, 1
	syscall
	li $v0, 10
	syscall