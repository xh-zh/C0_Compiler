.data
string_0:	.asciiz	"\n"
string_1:	.asciiz	"The mode is illegal."
string_2:	.asciiz	"The number is too large."
string_3:	.asciiz	"The number should not be negative or zero."
string_4:	.asciiz	"mode:"
string_5:	.asciiz	"result:"
#~CONST	!INTSY	32768	M
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
M: .word	32768

#~CONST	!INTSY	2	a
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
a: .word	2

#~CONST	!CHARSY	102	MODE
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
MODE: .word	102

#~VAL	!INTSY		pra
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
pra: .word	0

#~ARRAY	!INTSY	10	factors
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
factors: .word	1 : 10

#~VAL	!INTSY		number
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
number: .word	0

#~VAL	!CHARSY		mode
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
mode: .word	0

#~FUN	~BEGIN		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
.text
j	main

#~FUN	!VOID	init	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
init:
subi	$sp, $sp, 72
sw	$ra, 0($sp)

#~VAL	!INTSY		i
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#=	0		pra
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$t0, 0

#=	$97		mode
# $t0	pra	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$t1, 97

#-	1024	1	i
# $t0	pra	
# $t1	mode	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a2, 1024
li	$a3, 1
sub	$t2, $a2, $a3

#~LABLE	lable_0		
# $t0	pra	
# $t1	mode	
# $t2	i	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, pra
sw	$t1, mode
sw	$t2, 36($sp)
lable_0:

#[]=	i	0	factors
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a2, factors
lw	$t0, 36($sp)
sll	$a3, $t0, 2
add	$a2, $a2, $a3
li	$a3, 0
sw	$a3, 0($a2)

#-	i	1	i
# $t0	i	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 1
sub	$t0, $t0, $a3

#>=	i	0	7_t
# $t0	i	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 0
sge	$t1, $t0, $a3

#~BNZ	7_t	lable_0	
# $t0	i	
# $t1	7_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 36($sp)
sw	$t1, 68($sp)
lw	$a3, 68($sp)
bne	$a3, $0, lable_0

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra

#~END	init		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra

#~FUN	!VOID	getmode	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
getmode:
subi	$sp, $sp, 36
sw	$ra, 0($sp)

#~SCANF	!CHARSY	mode	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 12
syscall
move	$t0, $v0

#~RETURN	~NONE		
# $t0	mode	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, mode
lw	$ra, 0($sp)
addi	$sp, $sp, 36
jr	$ra

#~END	getmode		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 36
jr	$ra

#~FUN	!VOID	getnumber	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
getnumber:
subi	$sp, $sp, 36
sw	$ra, 0($sp)

#~SCANF	!INTSY	number	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 5
syscall
move	$t0, $v0

#~RETURN	~NONE		
# $t0	number	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, number
lw	$ra, 0($sp)
addi	$sp, $sp, 36
jr	$ra

#~END	getnumber		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 36
jr	$ra

#~FUN	!INTSY	getResult	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
getResult:
subi	$sp, $sp, 80
sw	$ra, 0($sp)

#~PARA	!INTSY	i	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#~PARA	!INTSY	r	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#+	number	-1	9_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, number
li	$a3, -1
add	$t1, $t0, $a3

#<	i	9_t	10_t
# $t0	number	
# $t1	9_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t2, 36($sp)
slt	$t3, $t2, $t1

#~BZ	10_t	lable_1	
# $t0	number	
# $t1	9_t	
# $t2	i	
# $t3	10_t	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t1, 48($sp)
sw	$t3, 52($sp)
lw	$a3, 52($sp)
beq	$a3, $0, lable_1

#=	i		11_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 36($sp)

#+	i	1	12_t
# $t0	i	11_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 1
add	$t1, $t0, $a3

#~PUSH	12_t	i	getResult
# $t0	i	11_t	
# $t1	12_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
subi	$sp, $sp, 80
sw	$t1, 36($sp)
addi	$sp, $sp, 80

#~PUSH	r	r	getResult
# $t0	i	11_t	
# $t1	12_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t2, 40($sp)
subi	$sp, $sp, 80
sw	$t2, 40($sp)
addi	$sp, $sp, 80

#~CALL	getResult		
# $t0	i	11_t	
# $t1	12_t	
# $t2	r	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 56($sp)
sw	$t1, 60($sp)
jal	getResult

#*	11_t	$v0	r
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 56($sp)
mul	$t1, $t0, $v0

#=	r		11_t
# $t0	11_t	
# $t1	r	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#~GOTO	lable_2		
# $t0	
# $t1	r	11_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t1, 40($sp)
sw	$t1, 56($sp)
j	lable_2

#~LABLE	lable_1		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_1:

#~LABLE	lable_2		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_2:

#~RETURN	!INTSY	r	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$v0, 40($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 80
jr	$ra

#~END	getResult		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 80
jr	$ra

#~FUN	!VOID	error	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
error:
subi	$sp, $sp, 56
sw	$ra, 0($sp)

#~PARA	!INTSY	num	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#=	num		17_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 36($sp)

#-	num	1	18_t
# $t0	num	17_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 1
sub	$t1, $t0, $a3

#~BNZ	18_t	lable_4	
# $t0	num	17_t	
# $t1	18_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 40($sp)
sw	$t1, 44($sp)
lw	$a3, 44($sp)
bne	$a3, $0, lable_4

#~PRINT	!STRING	string_1	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_1
li	$v0, 4
syscall

#~PRINT	!STRING	string_0	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_0
li	$v0, 4
syscall

#~GOTO	lable_3		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_3

#~LABLE	lable_4		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_4:

#-	17_t	2	19_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 40($sp)
li	$a3, 2
sub	$t1, $t0, $a3

#~BNZ	19_t	lable_5	
# $t0	17_t	
# $t1	19_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t1, 48($sp)
lw	$a3, 48($sp)
bne	$a3, $0, lable_5

#~PRINT	!STRING	string_2	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_2
li	$v0, 4
syscall

#~PRINT	!STRING	string_0	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_0
li	$v0, 4
syscall

#~GOTO	lable_3		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_3

#~LABLE	lable_5		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_5:

#-	17_t	3	20_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 40($sp)
li	$a3, 3
sub	$t1, $t0, $a3

#~BNZ	20_t	lable_6	
# $t0	17_t	
# $t1	20_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t1, 52($sp)
lw	$a3, 52($sp)
bne	$a3, $0, lable_6

#~PRINT	!STRING	string_3	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_3
li	$v0, 4
syscall

#~PRINT	!STRING	string_0	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_0
li	$v0, 4
syscall

#~GOTO	lable_3		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_3

#~LABLE	lable_6		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_6:

#~LABLE	lable_3		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_3:

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 56
jr	$ra

#~END	error		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 56
jr	$ra

#~FUN	!CHARSY	check	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
check:
subi	$sp, $sp, 64
sw	$ra, 0($sp)

#~PARA	!INTSY	preFactor	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#/	number	preFactor	21_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, number
lw	$t1, 36($sp)
div	$t0, $t1
mflo	$t2

#*	21_t	preFactor	21_t
# $t0	number	
# $t1	preFactor	
# $t2	21_t	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
mul	$t2, $t2, $t1

#!=	21_t	number	24_t
# $t0	number	
# $t1	preFactor	
# $t2	21_t	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
seq	$t3, $t2, $t0
xori	$t3, 1

#~BZ	24_t	lable_7	
# $t0	number	
# $t1	preFactor	
# $t2	21_t	
# $t3	24_t	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t2, 40($sp)
sw	$t3, 52($sp)
lw	$a3, 52($sp)
beq	$a3, $0, lable_7

#~RETURN	!CHARSY	$110	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 110
lw	$ra, 0($sp)
addi	$sp, $sp, 64
jr	$ra

#~GOTO	lable_8		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_8

#~LABLE	lable_7		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_7:

#~RETURN	!CHARSY	$121	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 121
lw	$ra, 0($sp)
addi	$sp, $sp, 64
jr	$ra

#~LABLE	lable_8		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_8:

#~END	check		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 64
jr	$ra

#~FUN	!VOID	getFactors	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
getFactors:
subi	$sp, $sp, 96
sw	$ra, 0($sp)

#~VAL	!INTSY		i
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#~VAL	!CHARSY		isFactor
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#=	1		i
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$t0, 1

#~LABLE	lable_9		
# $t0	i	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 36($sp)
lable_9:

#~PUSH	i	preFactor	check
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 36($sp)
subi	$sp, $sp, 64
sw	$t0, 36($sp)
addi	$sp, $sp, 64

#~CALL	check		
# $t0	i	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	check

#==	$v0	$121	33_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 121
seq	$t0, $v0, $a3

#~BZ	33_t	lable_10	
# $t0	33_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 68($sp)
lw	$a3, 68($sp)
beq	$a3, $0, lable_10

#[]=	pra	i	factors
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a2, factors
lw	$t0, pra
sll	$a3, $t0, 2
add	$a2, $a2, $a3
lw	$t1, 36($sp)
sw	$t1, 0($a2)

#+	pra	1	pra
# $t0	pra	
# $t1	i	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 1
add	$t0, $t0, $a3

#~GOTO	lable_11		
# $t0	pra	
# $t1	i	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, pra
j	lable_11

#~LABLE	lable_10		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_10:

#~LABLE	lable_11		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_11:

#+	i	1	i
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 36($sp)
li	$a3, 1
add	$t0, $t0, $a3

#<=	i	number	39_t
# $t0	i	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t1, number
sle	$t2, $t0, $t1

#~BNZ	39_t	lable_9	
# $t0	i	
# $t1	number	
# $t2	39_t	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 36($sp)
sw	$t2, 92($sp)
lw	$a3, 92($sp)
bne	$a3, $0, lable_9

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 96
jr	$ra

#~END	getFactors		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 96
jr	$ra

#~FUN	!VOID	output	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
output:
subi	$sp, $sp, 96
sw	$ra, 0($sp)

#~PARA	!CHARSY	mode	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#~PARA	!INTSY	result	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#~VAL	!INTSY		i
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#=	mode		40_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 36($sp)

#~PRINT	!STRING	string_4	
# $t0	mode	40_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_4
li	$v0, 4
syscall

#~PRINT	!CHARSY	40_t	
# $t0	mode	40_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
move	$a0, $t0
li	$v0, 11
syscall

#~PRINT	!STRING	string_0	
# $t0	mode	40_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_0
li	$v0, 4
syscall

#~PRINT	!STRING	string_5	
# $t0	mode	40_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_5
li	$v0, 4
syscall

#~PRINT	!STRING	string_0	
# $t0	mode	40_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_0
li	$v0, 4
syscall

#=	mode		41_t
# $t0	mode	40_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#-	mode	102	42_t
# $t0	mode	40_t	41_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 102
sub	$t1, $t0, $a3

#~BNZ	42_t	lable_13	
# $t0	mode	40_t	41_t	
# $t1	42_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 48($sp)
sw	$t0, 52($sp)
sw	$t1, 56($sp)
lw	$a3, 56($sp)
bne	$a3, $0, lable_13

#=	0		i
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$t0, 0

#~LABLE	lable_14		
# $t0	i	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 44($sp)
lable_14:

#=[]	factors	i	46_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a2, factors
lw	$t0, 44($sp)
sll	$a3, $t0, 2
add	$a2, $a2, $a3
lw	$t1, 0($a2)

#~PRINT	!INTSY	46_t	
# $t0	i	
# $t1	46_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
move	$a0, $t1
li	$v0, 1
syscall

#~PRINT	!STRING	string_0	
# $t0	i	
# $t1	46_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_0
li	$v0, 4
syscall

#+	i	1	i
# $t0	i	
# $t1	46_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 1
add	$t0, $t0, $a3

#<	i	pra	49_t
# $t0	i	
# $t1	46_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t2, pra
slt	$t3, $t0, $t2

#~BNZ	49_t	lable_14	
# $t0	i	
# $t1	46_t	
# $t2	pra	
# $t3	49_t	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 44($sp)
sw	$t1, 72($sp)
sw	$t3, 84($sp)
lw	$a3, 84($sp)
bne	$a3, $0, lable_14

#~GOTO	lable_12		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_12

#~LABLE	lable_13		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_13:

#-	41_t	115	50_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 52($sp)
li	$a3, 115
sub	$t1, $t0, $a3

#~BNZ	50_t	lable_15	
# $t0	41_t	
# $t1	50_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t1, 88($sp)
lw	$a3, 88($sp)
bne	$a3, $0, lable_15

#~PRINT	!INTSY	result	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 40($sp)
move	$a0, $t0
li	$v0, 1
syscall

#~PRINT	!STRING	string_0	
# $t0	result	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
la	$a0, string_0
li	$v0, 4
syscall

#~GOTO	lable_12		
# $t0	result	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_12

#~LABLE	lable_15		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_15:

#~LABLE	lable_12		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_12:

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 96
jr	$ra

#~END	output		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$ra, 0($sp)
addi	$sp, $sp, 96
jr	$ra

#~FUN	!VOID	main	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
main:
subi	$sp, $sp, 164
sw	$ra, 0($sp)

#~VAL	!INTSY		result
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	

#~CALL	init		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	init

#~CALL	getmode		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	getmode

#~CALL	getnumber		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	getnumber

#~SCANF	!INTSY	result	
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 5
syscall
move	$t0, $v0

#<=	number	0	57_t
# $t0	result	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t1, number
li	$a3, 0
sle	$t2, $t1, $a3

#~BZ	57_t	lable_16	
# $t0	result	
# $t1	number	
# $t2	57_t	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 36($sp)
sw	$t2, 60($sp)
lw	$a3, 60($sp)
beq	$a3, $0, lable_16

#~PUSH	3	num	error
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 3
subi	$sp, $sp, 56
sw	$a3, 36($sp)
addi	$sp, $sp, 56

#~CALL	error		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	error

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 10
syscall

#~GOTO	lable_17		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_17

#~LABLE	lable_16		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_16:

#~LABLE	lable_17		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_17:

#=	mode		60_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, mode

#-	mode	102	61_t
# $t0	mode	60_t	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 102
sub	$t1, $t0, $a3

#~BNZ	61_t	lable_19	
# $t0	mode	60_t	
# $t1	61_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 72($sp)
sw	$t1, 76($sp)
lw	$a3, 76($sp)
bne	$a3, $0, lable_19

#>	number	M	64_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, number
lw	$t1, M
sgt	$t2, $t0, $t1

#~BZ	64_t	lable_20	
# $t0	number	
# $t1	M	
# $t2	64_t	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t2, 88($sp)
lw	$a3, 88($sp)
beq	$a3, $0, lable_20

#~PUSH	2	num	error
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 2
subi	$sp, $sp, 56
sw	$a3, 36($sp)
addi	$sp, $sp, 56

#~CALL	error		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	error

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 10
syscall

#~GOTO	lable_21		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_21

#~LABLE	lable_20		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_20:

#~CALL	getFactors		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	getFactors

#~LABLE	lable_21		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_21:

#~GOTO	lable_18		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_18

#~LABLE	lable_19		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_19:

#-	60_t	115	68_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, 72($sp)
li	$a3, 115
sub	$t1, $t0, $a3

#~BNZ	68_t	lable_22	
# $t0	60_t	
# $t1	68_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t1, 104($sp)
lw	$a3, 104($sp)
bne	$a3, $0, lable_22

#>	number	32	71_t
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, number
li	$a3, 32
sgt	$t1, $t0, $a3

#~BZ	71_t	lable_23	
# $t0	number	
# $t1	71_t	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t1, 116($sp)
lw	$a3, 116($sp)
beq	$a3, $0, lable_23

#~PUSH	2	num	error
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 2
subi	$sp, $sp, 56
sw	$a3, 36($sp)
addi	$sp, $sp, 56

#~CALL	error		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	error

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 10
syscall

#~GOTO	lable_24		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_24

#~LABLE	lable_23		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_23:

#~PUSH	1	i	getResult
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 1
subi	$sp, $sp, 80
sw	$a3, 36($sp)
addi	$sp, $sp, 80

#~PUSH	1	r	getResult
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 1
subi	$sp, $sp, 80
sw	$a3, 40($sp)
addi	$sp, $sp, 80

#~CALL	getResult		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	getResult

#=	$v0		result
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
move	$t0, $v0

#~LABLE	lable_24		
# $t0	result	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
sw	$t0, 36($sp)
lable_24:

#~GOTO	lable_18		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
j	lable_18

#~LABLE	lable_22		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_22:

#~PUSH	1	num	error
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$a3, 1
subi	$sp, $sp, 56
sw	$a3, 36($sp)
addi	$sp, $sp, 56

#~CALL	error		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	error

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 10
syscall

#~LABLE	lable_18		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lable_18:

#~PUSH	mode	mode	output
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t0, mode
subi	$sp, $sp, 96
sw	$t0, 36($sp)
addi	$sp, $sp, 96

#~PUSH	result	result	output
# $t0	mode	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
lw	$t1, 36($sp)
subi	$sp, $sp, 96
sw	$t1, 40($sp)
addi	$sp, $sp, 96

#~CALL	output		
# $t0	mode	
# $t1	result	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
jal	output

#~RETURN	~NONE		
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 10
syscall

#~TERMINATE			
# $t0	
# $t1	
# $t2	
# $t3	
# $t4	
# $t5	
# $t6	
# $t7	
# $t8	
# $t9	
li	$v0, 10
syscall

