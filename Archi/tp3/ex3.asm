.data
	label: .asciiz "Entrez la valeur n: \n"
	label2: .asciiz "La suite à l'ordre n vaut: "

.text 
	la $a0, label 		#demande n
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	add $a0, $0, $v0
	
	or $v0,$0,$0
	jal fib
	add $s1, $0, $v0
	la $a0, label2 			#affiche la valeur du produit
	addi $v0, $0, 4
	syscall
	
	add $a0, $0, $s1
	addi $v0, $0, 1
	syscall
	addi $v0, $0, 10		#return EXIT_SUCCESS
	syscall
	
fib:	
	bne $a0,$0,else		#if n=0
	add $v0,$0,$0
	jr $ra
	
else:	addi $t0,$0,1		#if n = 1
	bne $a0,$t0,pasUn
	add $v0,$0,$t0
	jr $ra
	
pasUn:	addi $sp, $sp, -8		#on sauvegarde les paramètres
	sw $ra, 4($sp)
	sw $a0, 0($sp)
	addi $a0,$a0,-1
	
	jal fib
	#add $t0,$v0,$0
	
	lw $a0, 0($sp)
	addi $a0,$a0,-2
	sw $v0, 0($sp)
	jal fib
	lw $t0, 0($sp)
	add $v0,$v0,$t0
	
	lw $ra, 4($sp)
	lw $a0, 0($sp)
	addi $sp, $sp, 8
	jr $ra
	
	
	
	
	