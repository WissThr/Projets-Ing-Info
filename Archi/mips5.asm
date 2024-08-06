.data
	label: .asciiz "Entrez 1 nombre entier et positif: \n"
	label2: .asciiz "La somme de ses chiffres vaut: "
	label3: .space 10

.text 
verif:	la $a0, label 
	addi $v0, $0, 4
	syscall
	
	la $a0, label3
	addi $a1, $0,10
	addi $v0, $0, 8
	syscall
	
	la $t3, label3
		
	add $s2, $0, $0
	add $t1, $a0, $0
	
tab:	slt $t2, $a1, $t1
	beq $t2, 1, fin
	
	lbu $t0, 0(
	
	
	lw $t0, 0($t1)
	
	addi $t1, $t1, 4
				
	
	addi $s2, $s2, 4
	
	
	la $a0, label2 
	addi $v0, $0, 4
	syscall
	
	add $a0, $s1, $s2
	add $a0, $a0, $s3
	addi $v0, $0, 1
	syscall

	
