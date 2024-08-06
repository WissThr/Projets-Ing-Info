.data
    label:      .asciiz "Entrez la valeur n: \n"
    label2:     .asciiz "La suite à l'ordre n vaut: "

.text 
    la $a0, label        # demande n
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $a2, $v0
    li $a0, 0
    li $a1, 1
    
    or $v0, $0, $0
    jal fib1
    move $a2, $v0       # Mise à jour de $a2 avec le résultat de fib1
    
    la $a0, label2       # affiche la valeur du produit
    li $v0, 4
    syscall
    
    move $a0, $a2
    li $v0, 1
    syscall
    
    li $v0, 10           # return EXIT_SUCCESS
    syscall

fib1:
    addi $sp, $sp, -4     # on sauvegarde les paramètres
    sw $ra, 0($sp)
    move $a2, $a0
    li $a0, 0
    li $a1, 1
    jal fib
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

fib:
    addi $sp, $sp, -4     # on sauvegarde les paramètres
    sw $ra, 0($sp)
    
    bne $a2,$0, else        # if n != 0
    move $v0, $a1
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

else:
    addi $a2, $a2, -1
    move $t0, $a0
    move $t1, $a1
    add $a0, $t0, $t1
    move $a1, $t1
    jal fib
    
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra
