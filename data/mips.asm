.data
string_0:	.asciiz	"\n"
string_1:	.asciiz	"fun_1"
.text
j	main
fun:
subi	$sp, $sp, 44
sw	$ra, 0($sp)
la	$a0, string_1
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 10
sw	$t0, 40($sp)
lw	$t0, 40($sp)
lw	$t1, 36($sp)
add	$t2, $t0, $t1
sw	$t2, 40($sp)
lw	$v0, 40($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 44
jr	$ra
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 44
jr	$ra
main:
subi	$sp, $sp, 56
sw	$ra, 0($sp)
li	$t0, 3
sw	$t0, 36($sp)
lw	$t0, 36($sp)
subi	$sp, $sp, 44
sw	$t0, 36($sp)
addi	$sp, $sp, 44
jal	fun
sw	$v0, 40($sp)
lw	$t0, 40($sp)
sw	$t0, 44($sp)
lw	$t0, 44($sp)
subi	$sp, $sp, 44
sw	$t0, 36($sp)
addi	$sp, $sp, 44
jal	fun
sw	$v0, 48($sp)
lw	$t0, 48($sp)
sw	$t0, 52($sp)
lw	$a0, 52($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 10
syscall
