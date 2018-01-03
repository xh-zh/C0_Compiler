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
li	$t0, 0
sw	$t0, 80($sp)
li	$t0, 1
sw	$t0, 84($sp)
la	$t0, str
lw	$t1, 80($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 84($sp)
sw	$t1, 0($t0)
li	$t0, 1
sw	$t0, 88($sp)
li	$t0, 2
sw	$t0, 92($sp)
li	$t0, 40
add	$t0, $t0, $sp
lw	$t1, 88($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 92($sp)
sw	$t1, 0($t0)
li	$t0, 2
sw	$t0, 96($sp)
li	$t0, 3
sw	$t0, 100($sp)
la	$t0, str
lw	$t1, 96($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 100($sp)
sw	$t1, 0($t0)
li	$t0, 3
sw	$t0, 104($sp)
li	$t0, 4
sw	$t0, 108($sp)
li	$t0, 40
add	$t0, $t0, $sp
lw	$t1, 104($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 108($sp)
sw	$t1, 0($t0)
li	$t0, 4
sw	$t0, 112($sp)
li	$t0, 5
sw	$t0, 116($sp)
la	$t0, str
lw	$t1, 112($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 116($sp)
sw	$t1, 0($t0)
li	$t0, 5
sw	$t0, 120($sp)
li	$t0, 6
sw	$t0, 124($sp)
li	$t0, 40
add	$t0, $t0, $sp
lw	$t1, 120($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 124($sp)
sw	$t1, 0($t0)
lw	$t0, 36($sp)
sw	$t0, 128($sp)
la	$t0, str
lw	$t1, 128($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 132($sp)
lw	$t0, 132($sp)
sw	$t0, 136($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 136($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 140($sp)
lw	$t0, 140($sp)
sw	$t0, 144($sp)
la	$t0, str
lw	$t1, 144($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 148($sp)
lw	$t0, 148($sp)
sw	$t0, 152($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 152($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 156($sp)
lw	$t0, 156($sp)
sw	$t0, 160($sp)
la	$t0, str
lw	$t1, 160($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 164($sp)
lw	$t0, 164($sp)
sw	$t0, 168($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 168($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 172($sp)
lw	$t0, 172($sp)
sw	$t0, 176($sp)
li	$t0, 7
sw	$t0, 180($sp)
la	$t0, str
lw	$t1, 176($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 180($sp)
sw	$t1, 0($t0)
lw	$t0, 36($sp)
sw	$t0, 184($sp)
la	$t0, str
lw	$t1, 184($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 188($sp)
lw	$t0, 188($sp)
sw	$t0, 192($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 192($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 196($sp)
lw	$t0, 196($sp)
sw	$t0, 200($sp)
la	$t0, str
lw	$t1, 200($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 204($sp)
lw	$t0, 204($sp)
sw	$t0, 208($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 208($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 212($sp)
lw	$t0, 212($sp)
sw	$t0, 216($sp)
la	$t0, str
lw	$t1, 216($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 220($sp)
lw	$t0, 220($sp)
sw	$t0, 224($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 224($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 228($sp)
lw	$t0, 228($sp)
sw	$t0, 232($sp)
la	$t0, str
lw	$t1, 232($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 236($sp)
lw	$t0, 236($sp)
sw	$t0, 240($sp)
lw	$t0, 36($sp)
sw	$t0, 244($sp)
la	$t0, str
lw	$t1, 244($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 248($sp)
lw	$t0, 248($sp)
sw	$t0, 252($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 252($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 256($sp)
lw	$t0, 256($sp)
sw	$t0, 260($sp)
la	$t0, str
lw	$t1, 260($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 264($sp)
lw	$t0, 264($sp)
sw	$t0, 268($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 268($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 272($sp)
lw	$t0, 272($sp)
sw	$t0, 276($sp)
la	$t0, str
lw	$t1, 276($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 280($sp)
lw	$t0, 280($sp)
sw	$t0, 284($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 284($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 288($sp)
lw	$t0, 288($sp)
sw	$t0, 292($sp)
la	$t0, str
lw	$t1, 292($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 296($sp)
lw	$t0, 296($sp)
sw	$t0, 300($sp)
lw	$t0, 36($sp)
sw	$t0, 304($sp)
la	$t0, str
lw	$t1, 304($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 308($sp)
lw	$t0, 308($sp)
sw	$t0, 312($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 312($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 316($sp)
lw	$t0, 316($sp)
sw	$t0, 320($sp)
la	$t0, str
lw	$t1, 320($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 324($sp)
lw	$t0, 324($sp)
sw	$t0, 328($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 328($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 332($sp)
lw	$t0, 332($sp)
sw	$t0, 336($sp)
la	$t0, str
lw	$t1, 336($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 340($sp)
lw	$t0, 340($sp)
sw	$t0, 344($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 344($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 348($sp)
lw	$t0, 300($sp)
lw	$t1, 348($sp)
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
lw	$t0, 36($sp)
sw	$t0, 356($sp)
la	$t0, str
lw	$t1, 356($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 360($sp)
lw	$t0, 360($sp)
sw	$t0, 364($sp)
li	$t0, 6
sw	$t0, 368($sp)
li	$t0, 5
sw	$t0, 372($sp)
li	$t0, 0
li	$t1, 1
neg	$t2, $t1
sw	$t2, 376($sp)
li	$t0, 0
sw	$t0, 380($sp)
la	$t0, str
lw	$t1, 380($sp)
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
lw	$t0, 372($sp)
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
lw	$t0, 368($sp)
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
lw	$t0, 368($sp)
sw	$t0, 396($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 396($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 400($sp)
lw	$t0, 364($sp)
lw	$t1, 400($sp)
mul	$t2, $t0, $t1
sw	$t2, 364($sp)
lw	$t0, 364($sp)
sw	$t0, 404($sp)
la	$t0, str
lw	$t1, 404($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 408($sp)
lw	$t0, 352($sp)
lw	$t1, 408($sp)
add	$t2, $t0, $t1
sw	$t2, 352($sp)
li	$t0, 2
sw	$t0, 412($sp)
la	$t0, str
lw	$t1, 412($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 416($sp)
lw	$t0, 416($sp)
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
sw	$t0, 428($sp)
lw	$t0, 428($sp)
sw	$t0, 432($sp)
la	$t0, str
lw	$t1, 432($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 436($sp)
lw	$t0, 436($sp)
sw	$t0, 440($sp)
la	$t0, 40
add	$t0, $t0 ,$sp
lw	$t1, 440($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 444($sp)
lw	$t0, 444($sp)
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
lw	$t0, 36($sp)
sw	$t0, 40($sp)
lw	$v0, 40($sp)
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
sw	$t0, 48($sp)
lw	$t0, 48($sp)
lw	$t1, 40($sp)
add	$t2, $t0, $t1
sw	$t2, 48($sp)
lw	$t0, 48($sp)
sw	$t0, 44($sp)
lw	$t0, 44($sp)
sw	$t0, 52($sp)
lw	$v0, 52($sp)
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
li	$t0, 65
sw	$t0, 36($sp)
lw	$v0, 36($sp)
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
sw	$t0, 44($sp)
lw	$a0, 44($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 40($sp)
sw	$t0, 48($sp)
lw	$a0, 48($sp)
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
sw	$t0, 40($sp)
li	$t0, 1
sw	$t0, 44($sp)
lw	$t0, 40($sp)
lw	$t1, 44($sp)
seq	$t2, $t0, $t1
sw	$t2, 48($sp)
lw	$t0, 48($sp)
beq	$t0, $0, lable_0
li	$t0, 1
sw	$t0, 52($sp)
lw	$v0, 52($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra
j	lable_1
lable_0:
lw	$t0, 36($sp)
sw	$t0, 56($sp)
lw	$t0, 36($sp)
sw	$t0, 60($sp)
lw	$t0, 60($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 60($sp)
lw	$t0, 60($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 64($sp)
lw	$t0, 56($sp)
lw	$t1, 64($sp)
mul	$t2, $t0, $t1
sw	$t2, 56($sp)
lw	$t0, 56($sp)
sw	$t0, 68($sp)
lw	$v0, 68($sp)
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
sw	$t0, 192($sp)
lw	$t0, 192($sp)
sw	$t0, 188($sp)
li	$t0, 97
sw	$t0, 196($sp)
lw	$t0, 196($sp)
sw	$t0, 184($sp)
li	$t0, 1
sw	$t0, 200($sp)
lw	$t0, 200($sp)
sw	$t0, 172($sp)
li	$t0, 2
sw	$t0, 204($sp)
lw	$t0, 204($sp)
sw	$t0, 176($sp)
li	$t0, 3
sw	$t0, 208($sp)
lw	$t0, 208($sp)
sw	$t0, 180($sp)
li	$t0, 1
sw	$t0, 212($sp)
lw	$t0, 212($sp)
sw	$t0, 64($sp)
li	$t0, 100
sw	$t0, 216($sp)
lw	$t0, 216($sp)
sw	$t0, 68($sp)
li	$t0, 1
sw	$t0, 220($sp)
lw	$t0, 220($sp)
sw	$t0, 72($sp)
li	$t0, 2
sw	$t0, 224($sp)
lw	$t0, 224($sp)
sw	$t0, 76($sp)
li	$t0, 43
sw	$t0, 228($sp)
lw	$t0, 228($sp)
sw	$t0, 120($sp)
li	$t0, 45
sw	$t0, 232($sp)
lw	$t0, 232($sp)
sw	$t0, 124($sp)
li	$t0, 42
sw	$t0, 236($sp)
lw	$t0, 236($sp)
sw	$t0, 128($sp)
lw	$t0, 64($sp)
sw	$t0, 240($sp)
li	$t0, 100
sw	$t0, 244($sp)
lw	$t0, 240($sp)
lw	$t1, 244($sp)
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
j	lable_3
lable_2:
lable_3:
li	$t0, 0
sw	$t0, 252($sp)
lw	$t0, 252($sp)
beq	$t0, $0, lable_4
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
sw	$t0, 256($sp)
li	$t0, 1
sw	$t0, 260($sp)
lw	$t0, 256($sp)
lw	$t1, 260($sp)
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
sw	$t2, 268($sp)
lw	$t0, 268($sp)
sw	$t0, 76($sp)
lw	$t0, 76($sp)
sw	$t0, 272($sp)
lw	$a0, 272($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_7
lable_6:
lable_7:
lw	$t0, 76($sp)
sw	$t0, 276($sp)
lw	$t0, 36($sp)
sw	$t0, 280($sp)
lw	$t0, 276($sp)
lw	$t1, 280($sp)
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
sw	$t0, 288($sp)
lw	$t0, 288($sp)
sw	$t0, 64($sp)
lable_10:
lw	$t0, 64($sp)
sw	$t0, 292($sp)
lw	$t0, 64($sp)
sw	$t0, 296($sp)
li	$t0, 132
add	$t0, $t0, $sp
lw	$t1, 292($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 296($sp)
sw	$t1, 0($t0)
lw	$t0, 64($sp)
sw	$t0, 300($sp)
la	$t0, 132
add	$t0, $t0 ,$sp
lw	$t1, 300($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 304($sp)
lw	$t0, 304($sp)
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
sw	$t2, 64($sp)
lw	$t0, 64($sp)
sw	$t0, 312($sp)
li	$t0, 97
sw	$t0, 316($sp)
lw	$t0, 316($sp)
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
sw	$t0, 324($sp)
lw	$t0, 324($sp)
sw	$t0, 64($sp)
lable_11:
li	$t0, 0
sw	$t0, 328($sp)
lw	$t0, 328($sp)
sw	$t0, 72($sp)
lable_12:
lw	$t0, 64($sp)
sw	$t0, 332($sp)
lw	$t0, 332($sp)
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
sw	$t0, 336($sp)
li	$t0, 3
sw	$t0, 340($sp)
lw	$t0, 336($sp)
lw	$t1, 340($sp)
slt	$t2, $t0, $t1
sw	$t2, 344($sp)
lw	$t0, 344($sp)
bne	$t0, $0, lable_12
lw	$t0, 64($sp)
li	$t1, 2
add	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
sw	$t0, 348($sp)
li	$t0, 5
sw	$t0, 352($sp)
lw	$t0, 348($sp)
lw	$t1, 352($sp)
slt	$t2, $t0, $t1
sw	$t2, 356($sp)
lw	$t0, 356($sp)
bne	$t0, $0, lable_11
li	$t0, 9
sw	$t0, 360($sp)
la	$t0, 80
add	$t0, $t0 ,$sp
lw	$t1, 360($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 364($sp)
lw	$t0, 364($sp)
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
sw	$t0, 372($sp)
lw	$t0, 372($sp)
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
sw	$t0, 376($sp)
li	$t0, 1
sw	$t0, 380($sp)
lw	$t0, 376($sp)
lw	$t1, 380($sp)
seq	$t2, $t0, $t1
sw	$t2, 384($sp)
lw	$t0, 384($sp)
bne	$t0, $0, lable_13
li	$t0, 8
sw	$t0, 388($sp)
la	$t0, 80
add	$t0, $t0 ,$sp
lw	$t1, 388($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 392($sp)
lw	$t0, 392($sp)
sw	$t0, 396($sp)
lw	$a0, 396($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
sw	$t0, 400($sp)
lw	$t0, 400($sp)
subi	$sp, $sp, 56
sw	$t0, 36($sp)
addi	$sp, $sp, 56
lw	$t0, 64($sp)
sw	$t0, 404($sp)
lw	$t0, 404($sp)
subi	$sp, $sp, 56
sw	$t0, 40($sp)
addi	$sp, $sp, 56
jal	fun1
sw	$v0, 408($sp)
lw	$t0, 408($sp)
sw	$t0, 412($sp)
lw	$a0, 412($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
jal	fun5
sw	$v0, 416($sp)
lw	$t0, 64($sp)
sw	$t0, 420($sp)
lw	$t0, 420($sp)
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
sw	$t0, 428($sp)
lw	$t0, 428($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 432($sp)
lw	$t0, 432($sp)
sw	$t0, 436($sp)
lw	$t0, 436($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 440($sp)
lw	$t0, 440($sp)
bne	$t0, $0, lable_17
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
sw	$t0, 444($sp)
lw	$t0, 444($sp)
li	$t1, 43
sub	$t2, $t0, $t1
sw	$t2, 448($sp)
lw	$t0, 448($sp)
bne	$t0, $0, lable_19
li	$t0, 1
sw	$t0, 452($sp)
lw	$t0, 452($sp)
sw	$t0, 64($sp)
lable_20:
lw	$t0, 64($sp)
sw	$t0, 456($sp)
lw	$t0, 456($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 460($sp)
lw	$t0, 460($sp)
sw	$t0, 464($sp)
lw	$a0, 464($sp)
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
sw	$t0, 468($sp)
li	$t0, 4
sw	$t0, 472($sp)
lw	$t0, 468($sp)
lw	$t1, 472($sp)
slt	$t2, $t0, $t1
sw	$t2, 476($sp)
lw	$t0, 476($sp)
bne	$t0, $0, lable_20
j	lable_18
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
j	lable_18
lable_21:
lable_18:
j	lable_14
lable_15:
lw	$t0, 420($sp)
li	$t1, 2
sub	$t2, $t0, $t1
sw	$t2, 484($sp)
lw	$t0, 484($sp)
bne	$t0, $0, lable_22
li	$t0, 9
sw	$t0, 488($sp)
lw	$t0, 488($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 492($sp)
lw	$t0, 492($sp)
sw	$t0, 496($sp)
lw	$a0, 496($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_14
lable_22:
li	$t0, 0
sw	$t0, 500($sp)
lw	$t0, 500($sp)
sw	$t0, 64($sp)
lable_23:
li	$t0, 9
sw	$t0, 504($sp)
lw	$t0, 504($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 508($sp)
lw	$t0, 508($sp)
sw	$t0, 512($sp)
lw	$a0, 512($sp)
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
sw	$t0, 516($sp)
li	$t0, 1
sw	$t0, 520($sp)
lw	$t0, 516($sp)
lw	$t1, 520($sp)
seq	$t2, $t0, $t1
sw	$t2, 524($sp)
lw	$t0, 524($sp)
bne	$t0, $0, lable_23
lable_14:
li	$t0, 0
lw	$t1, 120($sp)
neg	$t2, $t1
sw	$t2, 528($sp)
lw	$t0, 528($sp)
sw	$t0, 64($sp)
lw	$t0, 64($sp)
sw	$t0, 532($sp)
li	$t0, 0
li	$t1, 43
neg	$t2, $t1
sw	$t2, 536($sp)
lw	$t0, 532($sp)
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
j	lable_25
lable_24:
lable_25:
lw	$t0, 64($sp)
sw	$t0, 544($sp)
lw	$t0, 544($sp)
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
j	lable_27
lable_26:
lable_27:
lw	$t0, 64($sp)
sw	$t0, 548($sp)
lw	$t0, 548($sp)
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
j	lable_28
lable_29:
lable_28:
lw	$t0, 120($sp)
sw	$t0, 556($sp)
lw	$t0, 556($sp)
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
j	lable_30
lable_31:
lable_30:
li	$t0, 43
sw	$t0, 564($sp)
lw	$t0, 564($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 568($sp)
lw	$a0, 568($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 45
sw	$t0, 572($sp)
lw	$t0, 572($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 576($sp)
lw	$a0, 576($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 42
sw	$t0, 580($sp)
lw	$t0, 580($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 584($sp)
lw	$a0, 584($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 47
sw	$t0, 588($sp)
lw	$t0, 588($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 592($sp)
lw	$a0, 592($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 95
sw	$t0, 596($sp)
lw	$t0, 596($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 600($sp)
lw	$a0, 600($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 97
sw	$t0, 604($sp)
lw	$t0, 604($sp)
sw	$t0, 64($sp)
lable_32:
lw	$t0, 64($sp)
sw	$t0, 608($sp)
lw	$t0, 608($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 612($sp)
lw	$a0, 612($sp)
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
sw	$t0, 616($sp)
li	$t0, 122
sw	$t0, 620($sp)
lw	$t0, 616($sp)
lw	$t1, 620($sp)
sle	$t2, $t0, $t1
sw	$t2, 624($sp)
lw	$t0, 624($sp)
bne	$t0, $0, lable_32
li	$t0, 65
sw	$t0, 628($sp)
lw	$t0, 628($sp)
sw	$t0, 64($sp)
lable_33:
lw	$t0, 64($sp)
sw	$t0, 632($sp)
lw	$t0, 632($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 636($sp)
lw	$a0, 636($sp)
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
sw	$t0, 640($sp)
li	$t0, 90
sw	$t0, 644($sp)
lw	$t0, 640($sp)
lw	$t1, 644($sp)
sle	$t2, $t0, $t1
sw	$t2, 648($sp)
lw	$t0, 648($sp)
bne	$t0, $0, lable_33
lw	$t0, 172($sp)
sw	$t0, 652($sp)
lw	$t0, 176($sp)
sw	$t0, 656($sp)
lw	$t0, 652($sp)
lw	$t1, 656($sp)
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
j	lable_35
lable_34:
lable_35:
lw	$t0, 176($sp)
sw	$t0, 664($sp)
lw	$t0, 172($sp)
sw	$t0, 668($sp)
lw	$t0, 664($sp)
lw	$t1, 668($sp)
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
j	lable_37
lable_36:
lable_37:
lw	$t0, 180($sp)
sw	$t0, 676($sp)
lw	$t0, 176($sp)
sw	$t0, 680($sp)
lw	$t0, 676($sp)
lw	$t1, 680($sp)
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
j	lable_39
lable_38:
lable_39:
lw	$t0, 176($sp)
sw	$t0, 688($sp)
lw	$t0, 180($sp)
sw	$t0, 692($sp)
lw	$t0, 688($sp)
lw	$t1, 692($sp)
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
j	lable_41
lable_40:
lable_41:
lw	$t0, 180($sp)
sw	$t0, 700($sp)
lw	$t0, 176($sp)
sw	$t0, 704($sp)
lw	$t0, 700($sp)
lw	$t1, 704($sp)
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
j	lable_43
lable_42:
lable_43:
lw	$t0, 176($sp)
sw	$t0, 712($sp)
lw	$t0, 180($sp)
sw	$t0, 716($sp)
lw	$t0, 712($sp)
lw	$t1, 716($sp)
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
j	lable_45
lable_44:
lable_45:
lw	$t0, 176($sp)
sw	$t0, 724($sp)
lw	$t0, 176($sp)
sw	$t0, 728($sp)
lw	$t0, 724($sp)
lw	$t1, 728($sp)
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
j	lable_47
lable_46:
lable_47:
lw	$t0, 176($sp)
sw	$t0, 736($sp)
lw	$t0, 180($sp)
sw	$t0, 740($sp)
lw	$t0, 736($sp)
lw	$t1, 740($sp)
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
j	lable_49
lable_48:
lable_49:
lw	$t0, 180($sp)
sw	$t0, 748($sp)
lw	$t0, 176($sp)
sw	$t0, 752($sp)
lw	$t0, 748($sp)
lw	$t1, 752($sp)
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
j	lable_51
lable_50:
lable_51:
lw	$t0, 180($sp)
sw	$t0, 760($sp)
lw	$t0, 180($sp)
sw	$t0, 764($sp)
lw	$t0, 760($sp)
lw	$t1, 764($sp)
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
j	lable_53
lable_52:
lable_53:
lw	$t0, 172($sp)
sw	$t0, 772($sp)
lw	$t0, 176($sp)
sw	$t0, 776($sp)
lw	$t0, 772($sp)
lw	$t1, 776($sp)
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
j	lable_55
lable_54:
lable_55:
lw	$t0, 188($sp)
sw	$t0, 784($sp)
lw	$t0, 184($sp)
sw	$t0, 788($sp)
lw	$t0, 784($sp)
lw	$t1, 788($sp)
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
j	lable_57
lable_56:
lable_57:
lw	$t0, 188($sp)
sw	$t0, 796($sp)
lw	$t0, 184($sp)
sw	$t0, 800($sp)
lw	$t0, 796($sp)
lw	$t1, 800($sp)
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
j	lable_59
lable_58:
lable_59:
lw	$t0, 172($sp)
sw	$t0, 808($sp)
lw	$t0, 176($sp)
sw	$t0, 812($sp)
lw	$t0, 808($sp)
lw	$t1, 812($sp)
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
j	lable_61
lable_60:
lable_61:
la	$a0, string_25
li	$v0, 4
syscall
jal	testArray
sw	$v0, 820($sp)
lw	$t0, 820($sp)
sw	$t0, 824($sp)
lw	$a0, 824($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 5
syscall
sw	$v0, 64($sp)
lw	$t0, 64($sp)
sw	$t0, 828($sp)
lw	$a0, 828($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 12
syscall
sw	$v0, 120($sp)
lw	$t0, 120($sp)
sw	$t0, 832($sp)
lw	$a0, 832($sp)
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
