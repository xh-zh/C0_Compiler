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
la	$t0, str
li	$t1, 0
sll	$t1, $t1, 2
add	$t0, $t0, $t1
li	$t1, 1
sw	$t1, 0($t0)
li	$t0, 40
add	$t0, $t0, $sp
li	$t1, 1
sll	$t1, $t1, 2
add	$t0, $t0, $t1
li	$t1, 2
sw	$t1, 0($t0)
la	$t0, str
li	$t1, 2
sll	$t1, $t1, 2
add	$t0, $t0, $t1
li	$t1, 3
sw	$t1, 0($t0)
li	$t0, 40
add	$t0, $t0, $sp
li	$t1, 3
sll	$t1, $t1, 2
add	$t0, $t0, $t1
li	$t1, 4
sw	$t1, 0($t0)
la	$t0, str
li	$t1, 4
sll	$t1, $t1, 2
add	$t0, $t0, $t1
li	$t1, 5
sw	$t1, 0($t0)
li	$t0, 40
add	$t0, $t0, $sp
li	$t1, 5
sll	$t1, $t1, 2
add	$t0, $t0, $t1
li	$t1, 6
sw	$t1, 0($t0)
la	$t0, str
lw	$t1, 36($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 136($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 136($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 144($sp)
la	$t0, str
lw	$t1, 144($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 152($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 152($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 160($sp)
la	$t0, str
lw	$t1, 160($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 168($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 168($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 176($sp)
la	$t0, str
lw	$t1, 176($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
li	$t1, 7
sw	$t1, 0($t0)
la	$t0, str
lw	$t1, 36($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 192($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 192($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 200($sp)
la	$t0, str
lw	$t1, 200($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 208($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 208($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 216($sp)
la	$t0, str
lw	$t1, 216($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 224($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 224($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 232($sp)
la	$t0, str
lw	$t1, 232($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 300($sp)
lw	$t0, 300($sp)
sw	$t0, 240($sp)
lw	$t0, 300($sp)
lw	$t1, 232($sp)
add	$t2, $t0, $t1
sw	$t2, 300($sp)
li	$t0, 40
add	$t0, $t0, $sp
lw	$t1, 240($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 300($sp)
sw	$t1, 0($t0)
li	$t0, 4
sw	$t0, 352($sp)
lw	$t0, 192($sp)
sw	$t0, 364($sp)
li	$t0, 6
sw	$t0, 368($sp)
li	$t0, 5
sw	$t0, 372($sp)
li	$t0, 0
li	$t1, 1
neg	$t2, $t1
sw	$t2, 376($sp)
la	$t0, str
li	$t1, 0
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 384($sp)
lw	$t0, 376($sp)
lw	$t1, 384($sp)
add	$t2, $t0, $t1
sw	$t2, 376($sp)
lw	$t0, 376($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 376($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 376($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 388($sp)
li	$t0, 5
lw	$t1, 388($sp)
add	$t2, $t0, $t1
sw	$t2, 372($sp)
lw	$t0, 372($sp)
li	$t1, 5
sub	$t2, $t0, $t1
sw	$t2, 372($sp)
la	$t0, str
lw	$t1, 372($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 392($sp)
li	$t0, 6
lw	$t1, 392($sp)
mul	$t2, $t0, $t1
sw	$t2, 368($sp)
lw	$t0, 368($sp)
li	$t1, 2
div	$t0, $t1
mflo	$t2
sw	$t2, 368($sp)
lw	$t0, 368($sp)
li	$t1, 3
div	$t0, $t1
mflo	$t2
sw	$t2, 368($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 368($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 400($sp)
lw	$t0, 192($sp)
lw	$t1, 400($sp)
mul	$t2, $t0, $t1
sw	$t2, 364($sp)
la	$t0, str
lw	$t1, 364($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 408($sp)
li	$t0, 4
lw	$t1, 408($sp)
add	$t2, $t0, $t1
sw	$t2, 352($sp)
la	$t0, str
li	$t1, 2
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 420($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 420($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 424($sp)
lw	$t0, 352($sp)
lw	$t1, 424($sp)
sub	$t2, $t0, $t1
sw	$t2, 352($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 352($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 432($sp)
la	$t0, str
lw	$t1, 432($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 440($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 440($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 448($sp)
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
lw	$a0, 36($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$a0, 40($sp)
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
li	$t1, 1
seq	$t2, $t0, $t1
sw	$t2, 48($sp)
lw	$t0, 48($sp)
beq	$t0, $0, lable_0
li	$v0, 1
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra
j	lable_1
lable_0:
lw	$t0, 36($sp)
sw	$t0, 56($sp)
lw	$t0, 36($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 60($sp)
lw	$t0, 60($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
lw	$t0, 56($sp)
mul	$t2, $t0, $v0
sw	$t2, 56($sp)
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
sw	$t0, 188($sp)
li	$t0, 97
sw	$t0, 184($sp)
li	$t0, 1
sw	$t0, 172($sp)
li	$t0, 2
sw	$t0, 176($sp)
li	$t0, 3
sw	$t0, 180($sp)
li	$t0, 1
sw	$t0, 64($sp)
li	$t0, 1
sw	$t0, 72($sp)
li	$t0, 2
sw	$t0, 76($sp)
li	$t0, 43
sw	$t0, 120($sp)
li	$t0, 1
li	$t1, 100
seq	$t2, $t0, $t1
sw	$t2, 248($sp)
lw	$t0, 248($sp)
beq	$t0, $0, lable_2
la	$a0, string_2
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_2:
li	$t0, 0
beq	$t0, $0, lable_4
la	$a0, string_2
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_4:
lw	$t0, 76($sp)
li	$t1, 1
sgt	$t2, $t0, $t1
sw	$t2, 264($sp)
lw	$t0, 264($sp)
beq	$t0, $0, lable_6
li	$t0, 0
lw	$t1, 76($sp)
neg	$t2, $t1
sw	$t2, 268($sp)
lw	$t0, 268($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 76($sp)
lw	$t0, 76($sp)
sw	$t0, 268($sp)
lw	$a0, 76($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_6:
lw	$t0, 76($sp)
lw	$t1, 36($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 284($sp)
lw	$t0, 284($sp)
beq	$t0, $0, lable_8
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
li	$t0, 132
add	$t0, $t0, $sp
lw	$t1, 64($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 64($sp)
sw	$t1, 0($t0)
la	$t0, 132
add	$t0, $t0 ,$sp
lw	$t1, 64($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 308($sp)
lw	$a0, 308($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 312($sp)
lw	$t0, 312($sp)
sw	$t0, 64($sp)
li	$t0, 97
li	$t1, 10
add	$t2, $t0, $t1
sw	$t2, 316($sp)
lw	$t0, 312($sp)
lw	$t1, 316($sp)
slt	$t2, $t0, $t1
sw	$t2, 320($sp)
lw	$t0, 320($sp)
bne	$t0, $0, lable_10
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
sw	$t2, 332($sp)
lw	$a0, 332($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 72($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 72($sp)
lw	$t0, 72($sp)
li	$t1, 3
slt	$t2, $t0, $t1
sw	$t2, 344($sp)
lw	$t0, 344($sp)
bne	$t0, $0, lable_12
lw	$t0, 64($sp)
li	$t1, 2
add	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
li	$t1, 5
slt	$t2, $t0, $t1
sw	$t2, 356($sp)
lw	$t0, 356($sp)
bne	$t0, $0, lable_11
la	$t0, 80
add	$t0, $t0 ,$sp
li	$t1, 9
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 368($sp)
lw	$a0, 368($sp)
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
li	$t0, 0
sw	$t0, 64($sp)
lable_13:
la	$a0, string_7
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
li	$t1, 1
seq	$t2, $t0, $t1
sw	$t2, 384($sp)
lw	$t0, 384($sp)
bne	$t0, $0, lable_13
la	$t0, 80
add	$t0, $t0 ,$sp
li	$t1, 8
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 396($sp)
lw	$a0, 396($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
subi	$sp, $sp, 56
sw	$t0, 36($sp)
addi	$sp, $sp, 56
lw	$t0, 64($sp)
subi	$sp, $sp, 56
sw	$t0, 40($sp)
addi	$sp, $sp, 56
jal	fun1
move	$a0, $v0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
jal	fun5
lw	$t0, 64($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 420($sp)
lw	$t0, 420($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 424($sp)
lw	$t0, 424($sp)
bne	$t0, $0, lable_15
lw	$t0, 64($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
li	$t1, 1
sub	$t2, $v0, $t1
sw	$t2, 440($sp)
lw	$t0, 440($sp)
bne	$t0, $0, lable_17
la	$a0, string_8
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_17:
lw	$t0, 120($sp)
sw	$t0, 444($sp)
lw	$t0, 120($sp)
li	$t1, 43
sub	$t2, $t0, $t1
sw	$t2, 448($sp)
lw	$t0, 448($sp)
bne	$t0, $0, lable_19
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
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
li	$t1, 4
slt	$t2, $t0, $t1
sw	$t2, 476($sp)
lw	$t0, 476($sp)
bne	$t0, $0, lable_20
j	lable_21
lable_19:
lw	$t0, 444($sp)
li	$t1, 45
sub	$t2, $t0, $t1
sw	$t2, 480($sp)
lw	$t0, 480($sp)
bne	$t0, $0, lable_21
la	$a0, string_2
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_21:
j	lable_14
lable_15:
lw	$t0, 420($sp)
li	$t1, 2
sub	$t2, $t0, $t1
sw	$t2, 484($sp)
lw	$t0, 484($sp)
bne	$t0, $0, lable_22
li	$t0, 9
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
j	lable_14
lable_22:
li	$t0, 0
sw	$t0, 64($sp)
lable_23:
li	$t0, 9
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
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
li	$t1, 1
seq	$t2, $t0, $t1
sw	$t2, 524($sp)
lw	$t0, 524($sp)
bne	$t0, $0, lable_23
lable_14:
li	$t0, 0
lw	$t1, 120($sp)
neg	$t2, $t1
sw	$t2, 64($sp)
li	$t0, 0
li	$t1, 43
neg	$t2, $t1
sw	$t2, 536($sp)
lw	$t0, 64($sp)
lw	$t1, 536($sp)
seq	$t2, $t0, $t1
sw	$t2, 540($sp)
lw	$t0, 540($sp)
beq	$t0, $0, lable_24
la	$a0, string_9
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_24:
lw	$t0, 64($sp)
li	$t1, 43
add	$t2, $t0, $t1
sw	$t2, 544($sp)
lw	$t0, 544($sp)
beq	$t0, $0, lable_26
la	$a0, string_10
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_26:
lw	$t0, 64($sp)
li	$t1, -43
sub	$t2, $t0, $t1
sw	$t2, 552($sp)
lw	$t0, 552($sp)
bne	$t0, $0, lable_29
la	$a0, string_11
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_29:
lw	$t0, 120($sp)
li	$t1, 43
sub	$t2, $t0, $t1
sw	$t2, 560($sp)
lw	$t0, 560($sp)
bne	$t0, $0, lable_31
la	$a0, string_12
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_31:
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
lw	$a0, 64($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
li	$t1, 122
sle	$t2, $t0, $t1
sw	$t2, 624($sp)
lw	$t0, 624($sp)
bne	$t0, $0, lable_32
li	$t0, 65
sw	$t0, 64($sp)
lable_33:
lw	$a0, 64($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
li	$t1, 90
sle	$t2, $t0, $t1
sw	$t2, 648($sp)
lw	$t0, 648($sp)
bne	$t0, $0, lable_33
lw	$t0, 172($sp)
lw	$t1, 176($sp)
sgt	$t2, $t0, $t1
sw	$t2, 660($sp)
lw	$t0, 660($sp)
beq	$t0, $0, lable_34
la	$a0, string_13
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_34:
lw	$t0, 176($sp)
lw	$t1, 172($sp)
sgt	$t2, $t0, $t1
sw	$t2, 672($sp)
lw	$t0, 672($sp)
beq	$t0, $0, lable_36
la	$a0, string_14
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_36:
lw	$t0, 180($sp)
lw	$t1, 176($sp)
slt	$t2, $t0, $t1
sw	$t2, 684($sp)
lw	$t0, 684($sp)
beq	$t0, $0, lable_38
la	$a0, string_15
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_38:
lw	$t0, 176($sp)
lw	$t1, 180($sp)
slt	$t2, $t0, $t1
sw	$t2, 696($sp)
lw	$t0, 696($sp)
beq	$t0, $0, lable_40
la	$a0, string_16
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_40:
lw	$t0, 180($sp)
lw	$t1, 176($sp)
sle	$t2, $t0, $t1
sw	$t2, 708($sp)
lw	$t0, 708($sp)
beq	$t0, $0, lable_42
la	$a0, string_17
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_42:
lw	$t0, 176($sp)
lw	$t1, 180($sp)
sle	$t2, $t0, $t1
sw	$t2, 720($sp)
lw	$t0, 720($sp)
beq	$t0, $0, lable_44
la	$a0, string_18
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_44:
lw	$t0, 176($sp)
lw	$t1, 176($sp)
sle	$t2, $t0, $t1
sw	$t2, 732($sp)
lw	$t0, 732($sp)
beq	$t0, $0, lable_46
la	$a0, string_18
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_46:
lw	$t0, 176($sp)
lw	$t1, 180($sp)
sge	$t2, $t0, $t1
sw	$t2, 744($sp)
lw	$t0, 744($sp)
beq	$t0, $0, lable_48
la	$a0, string_19
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_48:
lw	$t0, 180($sp)
lw	$t1, 176($sp)
sge	$t2, $t0, $t1
sw	$t2, 756($sp)
lw	$t0, 756($sp)
beq	$t0, $0, lable_50
la	$a0, string_20
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_50:
lw	$t0, 180($sp)
lw	$t1, 180($sp)
sge	$t2, $t0, $t1
sw	$t2, 768($sp)
lw	$t0, 768($sp)
beq	$t0, $0, lable_52
la	$a0, string_20
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_52:
lw	$t0, 172($sp)
lw	$t1, 176($sp)
seq	$t2, $t0, $t1
sw	$t2, 780($sp)
lw	$t0, 780($sp)
beq	$t0, $0, lable_54
la	$a0, string_21
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_54:
lw	$t0, 188($sp)
lw	$t1, 184($sp)
seq	$t2, $t0, $t1
sw	$t2, 792($sp)
lw	$t0, 792($sp)
beq	$t0, $0, lable_56
la	$a0, string_22
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_56:
lw	$t0, 188($sp)
lw	$t1, 184($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 804($sp)
lw	$t0, 804($sp)
beq	$t0, $0, lable_58
la	$a0, string_23
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_58:
lw	$t0, 172($sp)
lw	$t1, 176($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 816($sp)
lw	$t0, 816($sp)
beq	$t0, $0, lable_60
la	$a0, string_24
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_60:
la	$a0, string_25
li	$v0, 4
syscall
jal	testArray
move	$a0, $v0
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 5
syscall
sw	$v0, 64($sp)
lw	$a0, 64($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 12
syscall
sw	$v0, 120($sp)
lw	$a0, 120($sp)
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
