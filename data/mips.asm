.data
string_0:	.asciiz	"\n"
string_1:	.asciiz	"m is too big. "
string_2:	.asciiz	"m is too small"
string_3:	.asciiz	"n is too big. "
string_4:	.asciiz	"n is too small. "
string_5:	.asciiz	"n should be no greater than m."
string_6:	.asciiz	"no errors seem found. "
string_7:	.asciiz	"Expression test failed! "
string_8:	.asciiz	"m! = "
string_9:	.asciiz	"repeat m! : "
string_10:	.asciiz	"n! = "
string_11:	.asciiz	"repeat n! : "
string_12:	.asciiz	"C(m, n) = "
MAX_FACTOR: .word	10
MIN_FACTOR: .word	0
SUBSCRIPT: .word	95
m: .word	0
n: .word	0
result: .word	0
.text
j	main
factorial:
subi	$sp, $sp, 40
sw	$ra, 0($sp)
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 8($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 12($sp)
lw	$t0, 8($sp)
lw	$t1, 12($sp)
sle	$t2, $t0, $t1
sw	$t2, 16($sp)
lw	$t0, 16($sp)
beq	$t0, $0, lable_0
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 20($sp)
lw	$v0, 20($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra
j	lable_1
lable_0:
lw	$t0, 4($sp)
sw	$t0, 24($sp)
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 28($sp)
lw	$t0, 28($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 28($sp)
lw	$t0, 28($sp)
subi	$sp, $sp, 40
sw	$t0, 4($sp)
addi	$sp, $sp, 40
jal	factorial
sw	$v0, 32($sp)
lw	$t0, 24($sp)
lw	$t1, 32($sp)
mult	$t0, $t1
mflo	$t2
sw	$t2, 24($sp)
li	$t0, 0
lw	$t1, 24($sp)
add	$t2, $t0, $t1
sw	$t2, 36($sp)
lw	$v0, 36($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra
lable_1:
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra
display_error:
subi	$sp, $sp, 32
sw	$ra, 0($sp)
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 8($sp)
lw	$t0, 8($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 12($sp)
lw	$t0, 12($sp)
bne	$t0, $0, lable_3
la	$a0, string_1
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_2
lable_3:
lw	$t0, 8($sp)
li	$t1, 2
sub	$t2, $t0, $t1
sw	$t2, 16($sp)
lw	$t0, 16($sp)
bne	$t0, $0, lable_4
la	$a0, string_2
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_2
lable_4:
lw	$t0, 8($sp)
li	$t1, 3
sub	$t2, $t0, $t1
sw	$t2, 20($sp)
lw	$t0, 20($sp)
bne	$t0, $0, lable_5
la	$a0, string_3
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_2
lable_5:
lw	$t0, 8($sp)
li	$t1, 4
sub	$t2, $t0, $t1
sw	$t2, 24($sp)
lw	$t0, 24($sp)
bne	$t0, $0, lable_6
la	$a0, string_4
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_2
lable_6:
lw	$t0, 8($sp)
li	$t1, 5
sub	$t2, $t0, $t1
sw	$t2, 28($sp)
lw	$t0, 28($sp)
bne	$t0, $0, lable_7
la	$a0, string_5
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_2
lable_7:
la	$a0, string_6
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
lable_2:
lw	$ra, 0($sp)
addi	$sp, $sp, 32
jr	$ra
expression_test:
subi	$sp, $sp, 88
sw	$ra, 0($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 8($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 12($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 16($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 20($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 24($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 28($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 32($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 36($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 40($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 44($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 48($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 52($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 56($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 60($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 68($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 72($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 76($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 80($sp)
lw	$t0, 76($sp)
lw	$t1, 80($sp)
sub	$t2, $t0, $t1
sw	$t2, 76($sp)
lw	$t0, 72($sp)
lw	$t1, 76($sp)
sub	$t2, $t0, $t1
sw	$t2, 72($sp)
lw	$t0, 68($sp)
lw	$t1, 72($sp)
sub	$t2, $t0, $t1
sw	$t2, 68($sp)
lw	$t0, 64($sp)
lw	$t1, 68($sp)
sub	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 60($sp)
lw	$t1, 64($sp)
sub	$t2, $t0, $t1
sw	$t2, 60($sp)
lw	$t0, 56($sp)
lw	$t1, 60($sp)
sub	$t2, $t0, $t1
sw	$t2, 56($sp)
lw	$t0, 52($sp)
lw	$t1, 56($sp)
sub	$t2, $t0, $t1
sw	$t2, 52($sp)
lw	$t0, 48($sp)
lw	$t1, 52($sp)
sub	$t2, $t0, $t1
sw	$t2, 48($sp)
lw	$t0, 44($sp)
lw	$t1, 48($sp)
sub	$t2, $t0, $t1
sw	$t2, 44($sp)
lw	$t0, 40($sp)
lw	$t1, 44($sp)
sub	$t2, $t0, $t1
sw	$t2, 40($sp)
lw	$t0, 36($sp)
lw	$t1, 40($sp)
sub	$t2, $t0, $t1
sw	$t2, 36($sp)
lw	$t0, 32($sp)
lw	$t1, 36($sp)
sub	$t2, $t0, $t1
sw	$t2, 32($sp)
lw	$t0, 28($sp)
lw	$t1, 32($sp)
sub	$t2, $t0, $t1
sw	$t2, 28($sp)
lw	$t0, 24($sp)
lw	$t1, 28($sp)
sub	$t2, $t0, $t1
sw	$t2, 24($sp)
lw	$t0, 20($sp)
lw	$t1, 24($sp)
sub	$t2, $t0, $t1
sw	$t2, 20($sp)
lw	$t0, 16($sp)
lw	$t1, 20($sp)
sub	$t2, $t0, $t1
sw	$t2, 16($sp)
lw	$t0, 12($sp)
lw	$t1, 16($sp)
sub	$t2, $t0, $t1
sw	$t2, 12($sp)
lw	$t0, 8($sp)
lw	$t1, 12($sp)
sub	$t2, $t0, $t1
sw	$t2, 8($sp)
lw	$t0, 8($sp)
sw	$t0, 4($sp)
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 84($sp)
lw	$v0, 84($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 88
jr	$ra
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 88
jr	$ra
for_factorial:
subi	$sp, $sp, 36
sw	$ra, 0($sp)
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 12($sp)
lw	$t0, 12($sp)
sw	$t0, 8($sp)
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 16($sp)
lw	$t0, 16($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 16($sp)
lw	$t0, 16($sp)
sw	$t0, 4($sp)
lable_8:
lw	$t0, 8($sp)
sw	$t0, 20($sp)
lw	$t0, 20($sp)
lw	$t1, 4($sp)
mult	$t0, $t1
mflo	$t2
sw	$t2, 20($sp)
li	$t0, 0
lw	$t1, 20($sp)
add	$t2, $t0, $t1
sw	$t2, 24($sp)
lw	$t0, 24($sp)
sw	$t0, 8($sp)
lw	$t0, 4($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 4($sp)
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 28($sp)
lw	$t0, 28($sp)
bne	$t0, $0, lable_8
li	$t0, 0
lw	$t1, 8($sp)
add	$t2, $t0, $t1
sw	$t2, 32($sp)
lw	$v0, 32($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 36
jr	$ra
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 36
jr	$ra
main:
subi	$sp, $sp, 216
sw	$ra, 0($sp)
li	$t0, 0
li	$t1, 0
add	$t2, $t0, $t1
sw	$t2, 20($sp)
lw	$t0, 20($sp)
sw	$t0, 4($sp)
li	$v0, 5
syscall
sw	$v0, m
li	$v0, 5
syscall
sw	$v0, n
jal	expression_test
sw	$v0, 24($sp)
li	$t0, 0
lw	$t1, 24($sp)
add	$t2, $t0, $t1
sw	$t2, 28($sp)
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 32($sp)
lw	$t0, 28($sp)
lw	$t1, 32($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 36($sp)
lw	$t0, 36($sp)
beq	$t0, $0, lable_9
la	$a0, string_7
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_10
lable_9:
lable_10:
li	$t0, 0
lw	$t1, m
add	$t2, $t0, $t1
sw	$t2, 40($sp)
li	$t0, 0
lw	$t1, MAX_FACTOR
add	$t2, $t0, $t1
sw	$t2, 44($sp)
lw	$t0, 40($sp)
lw	$t1, 44($sp)
sgt	$t2, $t0, $t1
sw	$t2, 48($sp)
lw	$t0, 48($sp)
beq	$t0, $0, lable_11
li	$t0, 0
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 52($sp)
lw	$t0, 52($sp)
sw	$t0, 4($sp)
j	lable_12
lable_11:
lable_12:
li	$t0, 0
lw	$t1, m
add	$t2, $t0, $t1
sw	$t2, 56($sp)
li	$t0, 0
lw	$t1, MIN_FACTOR
add	$t2, $t0, $t1
sw	$t2, 60($sp)
lw	$t0, 56($sp)
lw	$t1, 60($sp)
slt	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
beq	$t0, $0, lable_13
li	$t0, 0
li	$t1, 2
add	$t2, $t0, $t1
sw	$t2, 68($sp)
lw	$t0, 68($sp)
sw	$t0, 4($sp)
j	lable_14
lable_13:
lable_14:
li	$t0, 0
lw	$t1, n
add	$t2, $t0, $t1
sw	$t2, 72($sp)
li	$t0, 0
lw	$t1, MAX_FACTOR
add	$t2, $t0, $t1
sw	$t2, 76($sp)
lw	$t0, 72($sp)
lw	$t1, 76($sp)
sgt	$t2, $t0, $t1
sw	$t2, 80($sp)
lw	$t0, 80($sp)
beq	$t0, $0, lable_15
li	$t0, 0
li	$t1, 3
add	$t2, $t0, $t1
sw	$t2, 84($sp)
lw	$t0, 84($sp)
sw	$t0, 4($sp)
j	lable_16
lable_15:
lable_16:
li	$t0, 0
lw	$t1, n
add	$t2, $t0, $t1
sw	$t2, 88($sp)
li	$t0, 0
lw	$t1, MIN_FACTOR
add	$t2, $t0, $t1
sw	$t2, 92($sp)
lw	$t0, 88($sp)
lw	$t1, 92($sp)
slt	$t2, $t0, $t1
sw	$t2, 96($sp)
lw	$t0, 96($sp)
beq	$t0, $0, lable_17
li	$t0, 0
li	$t1, 4
add	$t2, $t0, $t1
sw	$t2, 100($sp)
lw	$t0, 100($sp)
sw	$t0, 4($sp)
j	lable_18
lable_17:
lable_18:
li	$t0, 0
lw	$t1, m
add	$t2, $t0, $t1
sw	$t2, 104($sp)
lw	$t0, 104($sp)
lw	$t1, n
sub	$t2, $t0, $t1
sw	$t2, 104($sp)
li	$t0, 0
li	$t1, 0
add	$t2, $t0, $t1
sw	$t2, 108($sp)
lw	$t0, 104($sp)
lw	$t1, 108($sp)
slt	$t2, $t0, $t1
sw	$t2, 112($sp)
lw	$t0, 112($sp)
beq	$t0, $0, lable_19
li	$t0, 0
li	$t1, 5
add	$t2, $t0, $t1
sw	$t2, 116($sp)
lw	$t0, 116($sp)
sw	$t0, 4($sp)
j	lable_20
lable_19:
lable_20:
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 120($sp)
lw	$t0, 120($sp)
subi	$sp, $sp, 32
sw	$t0, 4($sp)
addi	$sp, $sp, 32
jal	display_error
sw	$v0, 124($sp)
li	$t0, 0
lw	$t1, 4($sp)
add	$t2, $t0, $t1
sw	$t2, 128($sp)
li	$t0, 0
li	$t1, 0
add	$t2, $t0, $t1
sw	$t2, 132($sp)
lw	$t0, 128($sp)
lw	$t1, 132($sp)
seq	$t2, $t0, $t1
sw	$t2, 136($sp)
lw	$t0, 136($sp)
beq	$t0, $0, lable_21
li	$t0, 0
lw	$t1, m
add	$t2, $t0, $t1
sw	$t2, 140($sp)
lw	$t0, 140($sp)
subi	$sp, $sp, 40
sw	$t0, 4($sp)
addi	$sp, $sp, 40
jal	factorial
sw	$v0, 144($sp)
li	$t0, 0
lw	$t1, 144($sp)
add	$t2, $t0, $t1
sw	$t2, 148($sp)
lw	$t0, 148($sp)
sw	$t0, 8($sp)
li	$t0, 0
lw	$t1, n
add	$t2, $t0, $t1
sw	$t2, 152($sp)
lw	$t0, 152($sp)
subi	$sp, $sp, 40
sw	$t0, 4($sp)
addi	$sp, $sp, 40
jal	factorial
sw	$v0, 156($sp)
li	$t0, 0
lw	$t1, 156($sp)
add	$t2, $t0, $t1
sw	$t2, 160($sp)
lw	$t0, 160($sp)
sw	$t0, 12($sp)
li	$t0, 0
lw	$t1, m
add	$t2, $t0, $t1
sw	$t2, 164($sp)
lw	$t0, 164($sp)
lw	$t1, n
sub	$t2, $t0, $t1
sw	$t2, 164($sp)
lw	$t0, 164($sp)
subi	$sp, $sp, 40
sw	$t0, 4($sp)
addi	$sp, $sp, 40
jal	factorial
sw	$v0, 168($sp)
li	$t0, 0
lw	$t1, 168($sp)
add	$t2, $t0, $t1
sw	$t2, 172($sp)
lw	$t0, 172($sp)
sw	$t0, 16($sp)
la	$a0, string_8
li	$v0, 4
syscall
li	$t0, 0
lw	$t1, 8($sp)
add	$t2, $t0, $t1
sw	$t2, 176($sp)
lw	$a0, 176($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
la	$a0, string_9
li	$v0, 4
syscall
li	$t0, 0
lw	$t1, m
add	$t2, $t0, $t1
sw	$t2, 180($sp)
lw	$t0, 180($sp)
subi	$sp, $sp, 36
sw	$t0, 4($sp)
addi	$sp, $sp, 36
jal	for_factorial
sw	$v0, 184($sp)
li	$t0, 0
lw	$t1, 184($sp)
add	$t2, $t0, $t1
sw	$t2, 188($sp)
lw	$a0, 188($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
la	$a0, string_10
li	$v0, 4
syscall
li	$t0, 0
lw	$t1, 12($sp)
add	$t2, $t0, $t1
sw	$t2, 192($sp)
lw	$a0, 192($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
la	$a0, string_11
li	$v0, 4
syscall
li	$t0, 0
lw	$t1, n
add	$t2, $t0, $t1
sw	$t2, 196($sp)
lw	$t0, 196($sp)
subi	$sp, $sp, 36
sw	$t0, 4($sp)
addi	$sp, $sp, 36
jal	for_factorial
sw	$v0, 200($sp)
li	$t0, 0
lw	$t1, 200($sp)
add	$t2, $t0, $t1
sw	$t2, 204($sp)
lw	$a0, 204($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
la	$a0, string_12
li	$v0, 4
syscall
lw	$t0, 8($sp)
sw	$t0, 208($sp)
lw	$t0, 208($sp)
lw	$t1, 12($sp)
div	$t0, $t1
mflo	$t2
sw	$t2, 208($sp)
lw	$t0, 208($sp)
lw	$t1, 16($sp)
div	$t0, $t1
mflo	$t2
sw	$t2, 208($sp)
li	$t0, 0
lw	$t1, 208($sp)
add	$t2, $t0, $t1
sw	$t2, 212($sp)
lw	$a0, 212($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_22
lable_21:
lable_22:
li	$v0, 10
syscall
