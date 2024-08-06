.data   # segment de donnees
tab0:   .word 1,4,3,7
tail0:  .word 4
tab1:   .word 4,4,5,6,1,7
tail1:  .word 6

.text   # segment texte
main:   la    $a0, tab0   # a0 = adresse referencee par tab0
        la    $a1, tab1
        lw    $a2, tail0  # a2 = valeur stockee a l'adresse 
                          # referencee par tail0
        lw    $a3, tail1
        sll   $a2, $a2, 2  # 1re ligne du code TD2.2
        sll   $a3, $a3, 2
        add   $v0, $zero, $zero
        add   $t0, $zero, $zero
out:    add   $t4, $a0, $t0
        lw    $t4, 0($t4)
        add   $t1, $zero, $zero
int:    add   $t3, $a1, $t1
        lw    $t3, 0($t3)
        bne   $t3, $t4, skip
        addi  $v0, $v0, 1
skip:   addi  $t1, $t1, 4
        bne   $t1, $a3, int
        addi  $t0, $t0, 4
        bne   $t0, $a2, out
