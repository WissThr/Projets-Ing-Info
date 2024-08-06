.data
	label: .asciiz "Entrez 1 valeur: \n"
	label2: .asciiz "Leur produit vaut: "

.text 
	la $a0, label 		#demande i
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	add $t0, $0, $v0
	
	la $a0, label 			#demande j
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	
	add $a1, $0, $v0		#init la fonction récursive
	add $a0, $0, $t0
	or $v0,$0,$0
	jal mult
	add $s1, $0, $v0
	
	
	la $a0, label2 			#affiche la valeur du produit
	addi $v0, $0, 4
	syscall
	
	add $a0, $0, $s1
	addi $v0, $0, 1
	syscall
	addi $v0, $0, 10		#return EXIT_SUCCEss
	syscall
	
	
	
	
	
mult:	
	beq $a1,$0,casZero
	
	addi $sp, $sp, -8
	sw $ra, 4($sp)
	sw $a0, 0($sp)
	
	add $t0,$0,$a1 #échange i et j
	add $a1,$0,$a0
	add $a0,$0,$t0
	addi $a0,$a0,-1
	
	jal mult
	lw $ra, 4($sp)
	lw $a0, 0($sp)
	addi $sp, $sp, 8
	add $v0, $v0, $a0
	jr $ra
	  
casZero:add $v0,$0,$0
	jr $ra















