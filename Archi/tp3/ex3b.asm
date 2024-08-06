.data
	label: .asciiz "Entrez la valeur n: \n"
	label2: .asciiz "La suite à l'ordre n vaut: "

.text 
	la $a0, label 		#demande n
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 5
	syscall
	add $a2, $0, $v0
	addi $a0, $0,0
	addi $a1, $0,1
	
	or $v0,$0,$0
	jal fib1
	add $s1, $0, $v0
	la $a0, label2 			#affiche la valeur du produit
	addi $v0, $0, 4
	syscall
	
	add $a0, $0, $s1
	addi $v0, $0, 1
	syscall
	addi $v0, $0, 10		#return EXIT_SUCCESS
	syscall
	
fib1:	addi $sp, $sp, -4		#on sauvegarde les paramètres
	sw $ra, 0($sp)
	add $a2,$0,$a0
	add $a0,$0,$0
	addi $a1,$0,1
	jal fib
	lw $ra,0($sp)
	addi $sp,$sp,4
	jr $ra
	
	
fib:	addi $sp, $sp, -4		#on sauvegarde les paramètres
	sw $ra, 0($sp)
	
	bne $a2,$0,else		#if n=0
	add $v0,$a1,$0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	
else:	
	addi $a2,$a2,-1
	add $t0,$a0,$0
	add $t1,$a1,$0
	add $a0,$t0,$t1
	add $a1,$0,$t1
	jal fib
	
	
	#retourne 1 quoiqu'il arrive
	
	
	
	
	
	
	