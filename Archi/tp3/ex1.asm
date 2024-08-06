.data
	label: .asciiz "Entrez 1 valeur: \n"
	label2: .asciiz "Leur produit vaut: "

.text 
	la $a0, label 
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	add $t0, $0, $v0
	
	la $a0, label 
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	add $a1, $0, $v0
	add $a0, $0, $t0
	jal mult
	add $s1, $0, $v0
	
	
	la $a0, label2 
	addi $v0, $0, 4
	syscall
	
	add $a0, $0, $s1
	addi $v0, $0, 1
	syscall
	addi $v0, $0, 10
	syscall
	
mult:	or $v0,$0,$0 # calcule $a0 * $a1
Loop:	slt $t0,$0,$a1
	beq $t0,$0,Exit
	add $v0,$v0,$a0
	addi $a1,$a1,-1
	j Loop
Exit:	jr $ra
   # résultat dans $v0
