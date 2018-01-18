.data
string_0:	.asciiz	"\n"
string_1:	.asciiz	"Funtion_5"
string_2:	.asciiz	"Error!"
string_3:	.asciiz	"Test_1"
string_4:	.asciiz	"Test_2"
string_5:	.asciiz	"Test_3"
string_6:	.asciiz	"Test_4"
string_7:	.asciiz	"Test_5"
string_8:	.asciiz	"Test_6"
string_9:	.asciiz	"Test_7"
string_10:	.asciiz	"Test_7_ERROR"
string_11:	.asciiz	"Test_7_1"
string_12:	.asciiz	"Test_7_2"
string_13:	.asciiz	"Test_1_Error"
string_14:	.asciiz	"Test_1_Correct"
string_15:	.asciiz	"Test_2_Error"
string_16:	.asciiz	"Test_2_Correct"
string_17:	.asciiz	"Test_3_Error"
string_18:	.asciiz	"Test_3_Correct"
string_19:	.asciiz	"Test_4_Error"
string_20:	.asciiz	"Test_4_Correct"
string_21:	.asciiz	"Test_5_Error"
string_22:	.asciiz	"Test_5_Correct"
string_23:	.asciiz	"Test_6_Error"
string_24:	.asciiz	"Test_6_Correct"
string_25:	.asciiz	"test array "
string_26:	.asciiz	"DONE!"
con_i_1: .word	1
con_i_2: .word	1
con_i_3: .word	2
con_c_1: .word	43
con_c_2: .word	45
con_c_3: .word	42
i_1: .word	0
i_2: .word	0
i_3: .word	0
i_4: .word	1 : 10
str: .word	1 : 10
c_1: .word	0
c_2: .word	0
c_3: .word	0
c_4: .word	1 : 10
.text
j	main
testArray:
subi	$sp, $sp, 452
sw	$ra, 0($sp)
li	$t0, 0
sw	$t0, 36($sp)
la	$a2, str
li	$a3, 0
sll	$a3, $a3, 2
add	$a2, $a2, $a3
li	$a3, 1
sw	$a3, 0($a2)
li	$a2, 40
add	$a2, $a2, $sp
li	$a3, 1
sll	$a3, $a3, 2
add	$a2, $a2, $a3
li	$a3, 2
sw	$a3, 0($a2)
la	$a2, str
li	$a3, 2
sll	$a3, $a3, 2
add	$a2, $a2, $a3
li	$a3, 3
sw	$a3, 0($a2)
li	$a2, 40
add	$a2, $a2, $sp
li	$a3, 3
sll	$a3, $a3, 2
add	$a2, $a2, $a3
li	$a3, 4
sw	$a3, 0($a2)
la	$a2, str
li	$a3, 4
sll	$a3, $a3, 2
add	$a2, $a2, $a3
li	$a3, 5
sw	$a3, 0($a2)
li	$a2, 40
add	$a2, $a2, $sp
li	$a3, 5
sll	$a3, $a3, 2
add	$a2, $a2, $a3
li	$a3, 6
sw	$a3, 0($a2)
la	$a2, str
lw	$t0, 36($sp)
sll	$a3, $t0, 2
add	$a2, $a2, $a3
lw	$t1, 0($a2)
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t1, 2
add	$a2, $a2, $a3
lw	$t2, 0($a2)
la	$a2, str
sll	$a3, $t2, 2
add	$a2, $a2, $a3
lw	$t3, 0($a2)
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t3, 2
add	$a2, $a2, $a3
lw	$t4, 0($a2)
la	$a2, str
sll	$a3, $t4, 2
add	$a2, $a2, $a3
lw	$t5, 0($a2)
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t5, 2
add	$a2, $a2, $a3
lw	$t6, 0($a2)
la	$a2, str
sll	$a3, $t6, 2
add	$a2, $a2, $a3
li	$a3, 7
sw	$a3, 0($a2)
la	$a2, str
sll	$a3, $t0, 2
add	$a2, $a2, $a3
lw	$t7, 0($a2)
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t7, 2
add	$a2, $a2, $a3
lw	$t8, 0($a2)
la	$a2, str
sll	$a3, $t8, 2
add	$a2, $a2, $a3
lw	$t9, 0($a2)
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t9, 2
add	$a2, $a2, $a3
lw	$t0, 0($a2)
la	$a2, str
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 216($sp)
lw	$t0, 0($a2)
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 224($sp)
lw	$t0, 0($a2)
la	$a2, str
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 232($sp)
lw	$t0, 0($a2)
sw	$t1, 136($sp)
lw	$t1, 232($sp)
sw	$t0, 240($sp)
add	$t0, $t0, $t1
li	$a2, 40
add	$a2, $a2, $sp
sw	$t0, 300($sp)
lw	$t0, 240($sp)
sll	$a3, $t0, 2
add	$a2, $a2, $a3
lw	$t1, 300($sp)
sw	$t1, 0($a2)
li	$t0, 4
sw	$t0, 352($sp)
li	$t0, 6
sw	$t0, 368($sp)
li	$t0, 5
li	$a2, 0
li	$a3, 1
sw	$t0, 372($sp)
neg	$t0, $a3
la	$a2, str
li	$a3, 0
sll	$a3, $a3, 2
add	$a2, $a2, $a3
sw	$t0, 376($sp)
lw	$t0, 0($a2)
sw	$t0, 384($sp)
lw	$t0, 376($sp)
lw	$t1, 384($sp)
add	$t0, $t0, $t1
li	$a3, 1
add	$t0, $t0, $a3
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 376($sp)
lw	$t0, 0($a2)
li	$a2, 5
sw	$t0, 388($sp)
add	$t0, $a2, $t0
li	$a3, 5
sub	$t0, $t0, $a3
la	$a2, str
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 372($sp)
lw	$t0, 0($a2)
li	$a2, 6
sw	$t0, 392($sp)
mul	$t0, $a2, $t0
li	$a3, 2
div	$t0, $a3
mflo	$t0
li	$a3, 3
div	$t0, $a3
mflo	$t0
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 368($sp)
lw	$t0, 0($a2)
sw	$t7, 192($sp)
mul	$t7, $t7, $t0
la	$a2, str
sll	$a3, $t7, 2
add	$a2, $a2, $a3
sw	$t0, 400($sp)
lw	$t0, 0($a2)
li	$a2, 4
sw	$t0, 408($sp)
add	$t0, $a2, $t0
la	$a2, str
li	$a3, 2
sll	$a3, $a3, 2
add	$a2, $a2, $a3
sw	$t0, 352($sp)
lw	$t0, 0($a2)
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 420($sp)
lw	$t0, 0($a2)
sw	$t0, 424($sp)
lw	$t0, 352($sp)
lw	$t1, 424($sp)
sub	$t0, $t0, $t1
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 352($sp)
lw	$t0, 0($a2)
la	$a2, str
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 432($sp)
lw	$t0, 0($a2)
la	$a2, 40
add	$a2, $a2 ,$sp
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 440($sp)
lw	$t0, 0($a2)
sw	$t0, 448($sp)
sw	$t2, 144($sp)
sw	$t3, 152($sp)
sw	$t4, 160($sp)
sw	$t5, 168($sp)
sw	$t6, 176($sp)
sw	$t7, 364($sp)
sw	$t8, 200($sp)
sw	$t9, 208($sp)
lw	$v0, 448($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 452
jr	$ra
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 452
jr	$ra
fun0:
subi	$sp, $sp, 44
sw	$ra, 0($sp)
lw	$v0, 36($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 44
jr	$ra
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 44
jr	$ra
fun1:
subi	$sp, $sp, 56
sw	$ra, 0($sp)
lw	$t0, 36($sp)
lw	$t1, 40($sp)
add	$t2, $t0, $t1
sw	$t2, 44($sp)
lw	$v0, 44($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 56
jr	$ra
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 56
jr	$ra
fun2:
subi	$sp, $sp, 40
sw	$ra, 0($sp)
li	$v0, 65
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra
fun3:
subi	$sp, $sp, 40
sw	$ra, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra
fun4:
subi	$sp, $sp, 52
sw	$ra, 0($sp)
lw	$t0, 36($sp)
move	$a0, $t0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t1, 40($sp)
move	$a0, $t1
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$ra, 0($sp)
addi	$sp, $sp, 52
jr	$ra
fun5:
subi	$sp, $sp, 36
sw	$ra, 0($sp)
la	$a0, string_1
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$ra, 0($sp)
addi	$sp, $sp, 36
jr	$ra
fun6:
subi	$sp, $sp, 72
sw	$ra, 0($sp)
lw	$t0, 36($sp)
li	$a3, 1
seq	$t1, $t0, $a3
sw	$t1, 48($sp)
lw	$a3, 48($sp)
beq	$a3, $0, lable_0
li	$v0, 1
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra
j	lable_1
lable_0:
lw	$t0, 36($sp)
li	$a3, 1
sub	$t1, $t0, $a3
subi	$sp, $sp, 72
sw	$t1, 36($sp)
addi	$sp, $sp, 72
sw	$t0, 56($sp)
sw	$t1, 60($sp)
jal	fun6
lw	$t0, 56($sp)
mul	$t0, $t0, $v0
sw	$t0, 56($sp)
lw	$v0, 56($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra
lable_1:
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra
main:
subi	$sp, $sp, 836
sw	$ra, 0($sp)
li	$t0, 1
sw	$t0, 36($sp)
li	$t0, 100
sw	$t0, 40($sp)
li	$t0, 1
sw	$t0, 44($sp)
li	$t0, 2
sw	$t0, 48($sp)
li	$t0, 43
sw	$t0, 52($sp)
li	$t0, 45
sw	$t0, 56($sp)
li	$t0, 42
sw	$t0, 60($sp)
li	$t0, 97
li	$t1, 97
li	$t2, 1
li	$t3, 2
li	$t4, 3
li	$t5, 1
li	$t6, 1
li	$t7, 2
li	$t8, 43
li	$a2, 1
li	$a3, 100
seq	$t9, $a2, $a3
sw	$t0, 188($sp)
sw	$t1, 184($sp)
sw	$t2, 172($sp)
sw	$t3, 176($sp)
sw	$t4, 180($sp)
sw	$t5, 64($sp)
sw	$t6, 72($sp)
sw	$t7, 76($sp)
sw	$t8, 120($sp)
sw	$t9, 248($sp)
lw	$a3, 248($sp)
beq	$a3, $0, lable_2
la	$a0, string_2
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_3
lable_2:
lable_3:
li	$a3, 0
beq	$a3, $0, lable_4
la	$a0, string_2
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_5
lable_4:
lable_5:
lw	$t0, 76($sp)
li	$a3, 1
sgt	$t1, $t0, $a3
sw	$t1, 264($sp)
lw	$a3, 264($sp)
beq	$a3, $0, lable_6
li	$a2, 0
lw	$t0, 76($sp)
neg	$t1, $t0
li	$a3, 1
add	$t0, $t1, $a3
move	$a0, $t0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
sw	$t0, 76($sp)
sw	$t0, 268($sp)
j	lable_7
lable_6:
lable_7:
lw	$t0, 76($sp)
lw	$t1, 36($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 284($sp)
lw	$a3, 284($sp)
beq	$a3, $0, lable_8
la	$a0, string_3
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_9
lable_8:
la	$a0, string_4
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_9:
li	$t0, 97
sw	$t0, 64($sp)
lable_10:
li	$a2, 132
add	$a2, $a2, $sp
lw	$t0, 64($sp)
sll	$a3, $t0, 2
add	$a2, $a2, $a3
sw	$t0, 0($a2)
la	$a2, 132
add	$a2, $a2 ,$sp
sll	$a3, $t0, 2
add	$a2, $a2, $a3
lw	$t1, 0($a2)
move	$a0, $t1
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$a3, 1
add	$t2, $t0, $a3
li	$a2, 97
li	$a3, 10
add	$t0, $a2, $a3
slt	$t3, $t2, $t0
sw	$t0, 316($sp)
sw	$t1, 308($sp)
sw	$t2, 312($sp)
sw	$t2, 64($sp)
sw	$t3, 320($sp)
lw	$a3, 320($sp)
bne	$a3, $0, lable_10
la	$a0, string_5
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 0
sw	$t0, 64($sp)
lable_11:
li	$t0, 0
sw	$t0, 72($sp)
lable_12:
lw	$t0, 64($sp)
lw	$t1, 72($sp)
add	$t2, $t0, $t1
move	$a0, $t2
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$a3, 1
add	$t1, $t1, $a3
li	$a3, 3
slt	$t3, $t1, $a3
sw	$t1, 72($sp)
sw	$t2, 332($sp)
sw	$t3, 344($sp)
lw	$a3, 344($sp)
bne	$a3, $0, lable_12
lw	$t0, 64($sp)
li	$a3, 2
add	$t0, $t0, $a3
li	$a3, 5
slt	$t1, $t0, $a3
sw	$t0, 64($sp)
sw	$t1, 356($sp)
lw	$a3, 356($sp)
bne	$a3, $0, lable_11
la	$a2, 80
add	$a2, $a2 ,$sp
li	$a3, 9
sll	$a3, $a3, 2
add	$a2, $a2, $a3
lw	$t0, 0($a2)
move	$a0, $t0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
la	$a0, string_6
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t1, 0
sw	$t0, 368($sp)
sw	$t1, 64($sp)
lable_13:
la	$a0, string_7
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
li	$a3, 1
add	$t0, $t0, $a3
li	$a3, 1
seq	$t1, $t0, $a3
sw	$t0, 64($sp)
sw	$t1, 384($sp)
lw	$a3, 384($sp)
bne	$a3, $0, lable_13
la	$a2, 80
add	$a2, $a2 ,$sp
li	$a3, 8
sll	$a3, $a3, 2
add	$a2, $a2, $a3
lw	$t0, 0($a2)
move	$a0, $t0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t1, 64($sp)
subi	$sp, $sp, 56
sw	$t1, 36($sp)
addi	$sp, $sp, 56
subi	$sp, $sp, 56
sw	$t1, 40($sp)
addi	$sp, $sp, 56
sw	$t0, 396($sp)
jal	fun1
move	$a0, $v0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
jal	fun5
lw	$t0, 64($sp)
li	$a3, 1
sub	$t1, $t0, $a3
li	$a3, 1
sub	$t2, $t1, $a3
sw	$t1, 420($sp)
sw	$t2, 424($sp)
lw	$a3, 424($sp)
bne	$a3, $0, lable_15
lw	$t0, 64($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
li	$a3, 1
sub	$t0, $v0, $a3
sw	$t0, 440($sp)
lw	$a3, 440($sp)
bne	$a3, $0, lable_17
la	$a0, string_8
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_16
lable_17:
lable_16:
lw	$t0, 120($sp)
li	$a3, 43
sub	$t1, $t0, $a3
sw	$t0, 444($sp)
sw	$t1, 448($sp)
lw	$a3, 448($sp)
bne	$a3, $0, lable_19
li	$t0, 1
sw	$t0, 64($sp)
lable_20:
lw	$t0, 64($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
move	$a0, $v0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
li	$a3, 1
add	$t0, $t0, $a3
li	$a3, 4
slt	$t1, $t0, $a3
sw	$t0, 64($sp)
sw	$t1, 476($sp)
lw	$a3, 476($sp)
bne	$a3, $0, lable_20
j	lable_18
lable_19:
lw	$t0, 444($sp)
li	$a3, 45
sub	$t1, $t0, $a3
sw	$t1, 480($sp)
lw	$a3, 480($sp)
bne	$a3, $0, lable_21
la	$a0, string_2
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_18
lable_21:
lable_18:
j	lable_14
lable_15:
lw	$t0, 420($sp)
li	$a3, 2
sub	$t1, $t0, $a3
sw	$t1, 484($sp)
lw	$a3, 484($sp)
bne	$a3, $0, lable_22
li	$a3, 9
subi	$sp, $sp, 72
sw	$a3, 36($sp)
addi	$sp, $sp, 72
jal	fun6
move	$a0, $v0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_14
lable_22:
li	$t0, 0
sw	$t0, 64($sp)
lable_23:
li	$a3, 9
subi	$sp, $sp, 72
sw	$a3, 36($sp)
addi	$sp, $sp, 72
jal	fun6
move	$a0, $v0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
li	$a3, 1
add	$t0, $t0, $a3
li	$a3, 1
seq	$t1, $t0, $a3
sw	$t0, 64($sp)
sw	$t1, 524($sp)
lw	$a3, 524($sp)
bne	$a3, $0, lable_23
lable_14:
li	$a2, 0
lw	$t0, 120($sp)
neg	$t1, $t0
li	$a2, 0
li	$a3, 43
neg	$t2, $a3
seq	$t3, $t1, $t2
sw	$t1, 64($sp)
sw	$t2, 536($sp)
sw	$t3, 540($sp)
lw	$a3, 540($sp)
beq	$a3, $0, lable_24
la	$a0, string_9
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_25
lable_24:
lable_25:
lw	$t0, 64($sp)
li	$a3, 43
add	$t1, $t0, $a3
sw	$t1, 544($sp)
lw	$a3, 544($sp)
beq	$a3, $0, lable_26
la	$a0, string_10
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_27
lable_26:
lable_27:
lw	$t0, 64($sp)
li	$a3, -43
sub	$t1, $t0, $a3
sw	$t1, 552($sp)
lw	$a3, 552($sp)
bne	$a3, $0, lable_29
la	$a0, string_11
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_28
lable_29:
lable_28:
lw	$t0, 120($sp)
li	$a3, 43
sub	$t1, $t0, $a3
sw	$t1, 560($sp)
lw	$a3, 560($sp)
bne	$a3, $0, lable_31
la	$a0, string_12
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_30
lable_31:
lable_30:
li	$a0, 43
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$a0, 45
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$a0, 42
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$a0, 47
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$a0, 95
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 97
sw	$t0, 64($sp)
lable_32:
lw	$t0, 64($sp)
move	$a0, $t0
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$a3, 1
add	$t0, $t0, $a3
li	$a3, 122
sle	$t1, $t0, $a3
sw	$t0, 64($sp)
sw	$t1, 624($sp)
lw	$a3, 624($sp)
bne	$a3, $0, lable_32
li	$t0, 65
sw	$t0, 64($sp)
lable_33:
lw	$t0, 64($sp)
move	$a0, $t0
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$a3, 1
add	$t0, $t0, $a3
li	$a3, 90
sle	$t1, $t0, $a3
sw	$t0, 64($sp)
sw	$t1, 648($sp)
lw	$a3, 648($sp)
bne	$a3, $0, lable_33
lw	$t0, 172($sp)
lw	$t1, 176($sp)
sgt	$t2, $t0, $t1
sw	$t2, 660($sp)
lw	$a3, 660($sp)
beq	$a3, $0, lable_34
la	$a0, string_13
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_35
lable_34:
lable_35:
lw	$t0, 176($sp)
lw	$t1, 172($sp)
sgt	$t2, $t0, $t1
sw	$t2, 672($sp)
lw	$a3, 672($sp)
beq	$a3, $0, lable_36
la	$a0, string_14
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_37
lable_36:
lable_37:
lw	$t0, 180($sp)
lw	$t1, 176($sp)
slt	$t2, $t0, $t1
sw	$t2, 684($sp)
lw	$a3, 684($sp)
beq	$a3, $0, lable_38
la	$a0, string_15
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_39
lable_38:
lable_39:
lw	$t0, 176($sp)
lw	$t1, 180($sp)
slt	$t2, $t0, $t1
sw	$t2, 696($sp)
lw	$a3, 696($sp)
beq	$a3, $0, lable_40
la	$a0, string_16
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_41
lable_40:
lable_41:
lw	$t0, 180($sp)
lw	$t1, 176($sp)
sle	$t2, $t0, $t1
sw	$t2, 708($sp)
lw	$a3, 708($sp)
beq	$a3, $0, lable_42
la	$a0, string_17
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_43
lable_42:
lable_43:
lw	$t0, 176($sp)
lw	$t1, 180($sp)
sle	$t2, $t0, $t1
sw	$t2, 720($sp)
lw	$a3, 720($sp)
beq	$a3, $0, lable_44
la	$a0, string_18
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_45
lable_44:
lable_45:
lw	$t0, 176($sp)
sle	$t1, $t0, $t0
sw	$t1, 732($sp)
lw	$a3, 732($sp)
beq	$a3, $0, lable_46
la	$a0, string_18
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_47
lable_46:
lable_47:
lw	$t0, 176($sp)
lw	$t1, 180($sp)
sge	$t2, $t0, $t1
sw	$t2, 744($sp)
lw	$a3, 744($sp)
beq	$a3, $0, lable_48
la	$a0, string_19
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_49
lable_48:
lable_49:
lw	$t0, 180($sp)
lw	$t1, 176($sp)
sge	$t2, $t0, $t1
sw	$t2, 756($sp)
lw	$a3, 756($sp)
beq	$a3, $0, lable_50
la	$a0, string_20
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_51
lable_50:
lable_51:
lw	$t0, 180($sp)
sge	$t1, $t0, $t0
sw	$t1, 768($sp)
lw	$a3, 768($sp)
beq	$a3, $0, lable_52
la	$a0, string_20
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_53
lable_52:
lable_53:
lw	$t0, 172($sp)
lw	$t1, 176($sp)
seq	$t2, $t0, $t1
sw	$t2, 780($sp)
lw	$a3, 780($sp)
beq	$a3, $0, lable_54
la	$a0, string_21
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_55
lable_54:
lable_55:
lw	$t0, 188($sp)
lw	$t1, 184($sp)
seq	$t2, $t0, $t1
sw	$t2, 792($sp)
lw	$a3, 792($sp)
beq	$a3, $0, lable_56
la	$a0, string_22
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_57
lable_56:
lable_57:
lw	$t0, 188($sp)
lw	$t1, 184($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 804($sp)
lw	$a3, 804($sp)
beq	$a3, $0, lable_58
la	$a0, string_23
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_59
lable_58:
lable_59:
lw	$t0, 172($sp)
lw	$t1, 176($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 816($sp)
lw	$a3, 816($sp)
beq	$a3, $0, lable_60
la	$a0, string_24
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_61
lable_60:
lable_61:
jal	testArray
move	$t0, $v0
la	$a0, string_25
li	$v0, 4
syscall
move	$a0, $t0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 5
syscall
move	$t1, $v0
move	$a0, $t1
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 12
syscall
move	$t2, $v0
move	$a0, $t2
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
la	$a0, string_26
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 10
syscall
