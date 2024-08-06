.data
	label: .asciiz "Entrez 1 valeur: \n"
	label2: .asciiz "Leur somme vaut: "

.text 
	la $a0, label 
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	add $s1, $0, $v0
	
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	add $s2, $0, $v0
	
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	add $s3, $0, $v0
	
	la $a0, label2 
	addi $v0, $0, 4
	syscall
	
	add $a0, $s1, $s2
	add $a0, $a0, $s3
	addi $v0, $0, 1
	syscall

	