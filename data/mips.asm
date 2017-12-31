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
string_13:	.asciiz	"DONE!"
#CONST	INTSY	1	con_i_1
con_i_1: .word	1

#CONST	INTSY	1	con_i_2
con_i_2: .word	1

#CONST	INTSY	2	con_i_3
con_i_3: .word	2

#CONST	CHARSY	43	con_c_1
con_c_1: .word	43

#CONST	CHARSY	45	con_c_2
con_c_2: .word	45

#CONST	CHARSY	42	con_c_3
con_c_3: .word	42

#VAL	INTSY		i_1
i_1: .word	0

#VAL	INTSY		i_2
i_2: .word	0

#VAL	INTSY		i_3
i_3: .word	0

#ARRAY	INTSY	10	i_4
i_4: .word	1 : 10

#VAL	CHARSY		c_1
c_1: .word	0

#VAL	CHARSY		c_2
c_2: .word	0

#VAL	CHARSY		c_3
c_3: .word	0

#ARRAY	CHARSY	10	c_4
c_4: .word	1 : 10

#FUN	BEGIN		
.text
j	main

#FUN	INTSY	fun0	
fun0:
subi	$sp, $sp, 44
sw	$ra, 0($sp)

#PARA	INTSY	a	

#=	a		0_t
lw	$t0, 36($sp)
sw	$t0, 40($sp)

#RETURN	INTSY	0_t	
lw	$v0, 40($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 44
jr	$ra

#END	fun0		
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 44
jr	$ra

#FUN	INTSY	fun1	
fun1:
subi	$sp, $sp, 56
sw	$ra, 0($sp)

#PARA	INTSY	a	

#PARA	INTSY	b	

#VAL	INTSY		fun

#=	a		1_t
lw	$t0, 36($sp)
sw	$t0, 48($sp)

#+	1_t	b	1_t
lw	$t0, 48($sp)
lw	$t1, 40($sp)
add	$t2, $t0, $t1
sw	$t2, 48($sp)

#=	1_t		fun
lw	$t0, 48($sp)
sw	$t0, 44($sp)

#=	fun		2_t
lw	$t0, 44($sp)
sw	$t0, 52($sp)

#RETURN	INTSY	2_t	
lw	$v0, 52($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 56
jr	$ra

#END	fun1		
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 56
jr	$ra

#FUN	CHARSY	fun2	
fun2:
subi	$sp, $sp, 40
sw	$ra, 0($sp)

#=	$65		3_t
li	$t0, 65
sw	$t0, 36($sp)

#RETURN	CHARSY	3_t	
lw	$v0, 36($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra

#END	fun2		
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra

#FUN	VOID	fun3	
fun3:
subi	$sp, $sp, 40
sw	$ra, 0($sp)

#PARA	INTSY	a	

#RETURN	NONE		
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra

#END	fun3		
lw	$ra, 0($sp)
addi	$sp, $sp, 40
jr	$ra

#FUN	VOID	fun4	
fun4:
subi	$sp, $sp, 52
sw	$ra, 0($sp)

#PARA	INTSY	a	

#PARA	CHARSY	b	

#=	a		4_t
lw	$t0, 36($sp)
sw	$t0, 44($sp)

#PRINT	INTSY	4_t	
lw	$a0, 44($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	b		5_t
lw	$t0, 40($sp)
sw	$t0, 48($sp)

#PRINT	CHARSY	5_t	
lw	$a0, 48($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#END	fun4		
lw	$ra, 0($sp)
addi	$sp, $sp, 52
jr	$ra

#FUN	VOID	fun5	
fun5:
subi	$sp, $sp, 36
sw	$ra, 0($sp)

#PRINT	STRING	string_1	
la	$a0, string_1
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#END	fun5		
lw	$ra, 0($sp)
addi	$sp, $sp, 36
jr	$ra

#FUN	INTSY	fun6	
fun6:
subi	$sp, $sp, 72
sw	$ra, 0($sp)

#PARA	INTSY	n	

#=	n		6_t
lw	$t0, 36($sp)
sw	$t0, 40($sp)

#=	1		7_t
li	$t0, 1
sw	$t0, 44($sp)

#==	6_t	7_t	8_t
lw	$t0, 40($sp)
lw	$t1, 44($sp)
seq	$t2, $t0, $t1
sw	$t2, 48($sp)

#BZ	8_t	lable_0	
lw	$t0, 48($sp)
beq	$t0, $0, lable_0

#=	1		9_t
li	$t0, 1
sw	$t0, 52($sp)

#RETURN	INTSY	9_t	
lw	$v0, 52($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra

#GOTO	lable_1		
j	lable_1

#LABLE	lable_0		
lable_0:

#=	n		10_t
lw	$t0, 36($sp)
sw	$t0, 56($sp)

#=	n		11_t
lw	$t0, 36($sp)
sw	$t0, 60($sp)

#-	11_t	1	11_t
lw	$t0, 60($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 60($sp)

#PUSH	11_t	n	fun6
lw	$t0, 60($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72

#CALL	fun6		
jal	fun6

#LOAD_RETURN_VALUE			12_t
sw	$v0, 64($sp)

#*	10_t	12_t	10_t
lw	$t0, 56($sp)
lw	$t1, 64($sp)
mul	$t2, $t0, $t1
sw	$t2, 56($sp)

#=	10_t		13_t
lw	$t0, 56($sp)
sw	$t0, 68($sp)

#RETURN	INTSY	13_t	
lw	$v0, 68($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra

#LABLE	lable_1		
lable_1:

#END	fun6		
lw	$v0, 0($sp)
lw	$ra, 0($sp)
addi	$sp, $sp, 72
jr	$ra

#FUN	VOID	main	
main:
subi	$sp, $sp, 1780
sw	$ra, 0($sp)

#CONST	INTSY	1	m_con_i_1
li	$t0, 1
sw	$t0, 36($sp)

#CONST	INTSY	100	M_con_i_1
li	$t0, 100
sw	$t0, 40($sp)

#CONST	INTSY	1	m_con_i_2
li	$t0, 1
sw	$t0, 44($sp)

#CONST	INTSY	2	m_con_i_3
li	$t0, 2
sw	$t0, 48($sp)

#CONST	CHARSY	43	m_con_c_1
li	$t0, 43
sw	$t0, 52($sp)

#CONST	CHARSY	45	m_con_c_2
li	$t0, 45
sw	$t0, 56($sp)

#CONST	CHARSY	42	m_con_c_3
li	$t0, 42
sw	$t0, 60($sp)

#VAL	INTSY		m_i_1

#VAL	INTSY		M_i_1

#VAL	INTSY		m_i_2

#VAL	INTSY		m_i_3

#ARRAY	INTSY	10	m_i_4

#VAL	CHARSY		m_c_1

#VAL	CHARSY		m_c_2

#VAL	CHARSY		m_c_3

#ARRAY	CHARSY	300	m_c_4

#=	1		14_t
li	$t0, 1
sw	$t0, 1332($sp)

#=	14_t		m_i_1
lw	$t0, 1332($sp)
sw	$t0, 64($sp)

#=	100		15_t
li	$t0, 100
sw	$t0, 1336($sp)

#=	15_t		M_i_1
lw	$t0, 1336($sp)
sw	$t0, 68($sp)

#=	1		16_t
li	$t0, 1
sw	$t0, 1340($sp)

#=	16_t		m_i_2
lw	$t0, 1340($sp)
sw	$t0, 72($sp)

#=	2		17_t
li	$t0, 2
sw	$t0, 1344($sp)

#=	17_t		m_i_3
lw	$t0, 1344($sp)
sw	$t0, 76($sp)

#=	$43		18_t
li	$t0, 43
sw	$t0, 1348($sp)

#=	18_t		m_c_1
lw	$t0, 1348($sp)
sw	$t0, 120($sp)

#=	$45		19_t
li	$t0, 45
sw	$t0, 1352($sp)

#=	19_t		m_c_2
lw	$t0, 1352($sp)
sw	$t0, 124($sp)

#=	$42		20_t
li	$t0, 42
sw	$t0, 1356($sp)

#=	20_t		m_c_3
lw	$t0, 1356($sp)
sw	$t0, 128($sp)

#=	m_i_1		21_t
lw	$t0, 64($sp)
sw	$t0, 1360($sp)

#=	100		22_t
li	$t0, 100
sw	$t0, 1364($sp)

#==	21_t	22_t	23_t
lw	$t0, 1360($sp)
lw	$t1, 1364($sp)
seq	$t2, $t0, $t1
sw	$t2, 1368($sp)

#BZ	23_t	lable_2	
lw	$t0, 1368($sp)
beq	$t0, $0, lable_2

#PRINT	STRING	string_2	
la	$a0, string_2
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_2		

#LABLE	lable_2		
lable_2:

#NOP	lable_3		

#=	0		24_t
li	$t0, 0
sw	$t0, 1372($sp)

#BZ	24_t	lable_4	
lw	$t0, 1372($sp)
beq	$t0, $0, lable_4

#PRINT	STRING	string_2	
la	$a0, string_2
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_4		

#LABLE	lable_4		
lable_4:

#NOP	lable_5		

#=	m_i_3		25_t
lw	$t0, 76($sp)
sw	$t0, 1376($sp)

#=	1		26_t
li	$t0, 1
sw	$t0, 1380($sp)

#>	25_t	26_t	27_t
lw	$t0, 1376($sp)
lw	$t1, 1380($sp)
sgt	$t2, $t0, $t1
sw	$t2, 1384($sp)

#BZ	27_t	lable_6	
lw	$t0, 1384($sp)
beq	$t0, $0, lable_6

#-	0	m_i_3	28_t
li	$t0, 0
lw	$t1, 76($sp)
sub	$t2, $t0, $t1
sw	$t2, 1388($sp)

#+	28_t	1	28_t
lw	$t0, 1388($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 1388($sp)

#=	28_t		m_i_3
lw	$t0, 1388($sp)
sw	$t0, 76($sp)

#=	m_i_3		29_t
lw	$t0, 76($sp)
sw	$t0, 1392($sp)

#PRINT	INTSY	29_t	
lw	$a0, 1392($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_6		

#LABLE	lable_6		
lable_6:

#NOP	lable_7		

#=	m_i_3		30_t
lw	$t0, 76($sp)
sw	$t0, 1396($sp)

#=	m_con_i_1		31_t
lw	$t0, 36($sp)
sw	$t0, 1400($sp)

#!=	30_t	31_t	32_t
lw	$t0, 1396($sp)
lw	$t1, 1400($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 1404($sp)

#BZ	32_t	lable_8	
lw	$t0, 1404($sp)
beq	$t0, $0, lable_8

#PRINT	STRING	string_3	
la	$a0, string_3
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#GOTO	lable_9		
j	lable_9

#LABLE	lable_8		
lable_8:

#PRINT	STRING	string_4	
la	$a0, string_4
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#LABLE	lable_9		
lable_9:

#=	$97		33_t
li	$t0, 97
sw	$t0, 1408($sp)

#=	33_t		m_i_1
lw	$t0, 1408($sp)
sw	$t0, 64($sp)

#LABLE	lable_10		
lable_10:

#=	m_i_1		34_t
lw	$t0, 64($sp)
sw	$t0, 1412($sp)

#=	m_i_1		35_t
lw	$t0, 64($sp)
sw	$t0, 1416($sp)

#[]=	34_t	35_t	m_c_4
li	$t0, 132
add	$t0, $t0, $sp
lw	$t1, 1412($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 1416($sp)
sw	$t1, 0($t0)

#=	m_i_1		36_t
lw	$t0, 64($sp)
sw	$t0, 1420($sp)

#=[]	m_c_4	36_t	37_t
la	$t0, 132
add	$t0, $t0 ,$sp
lw	$t1, 1420($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 1424($sp)

#=	37_t		38_t
lw	$t0, 1424($sp)
sw	$t0, 1428($sp)

#PRINT	CHARSY	38_t	
lw	$a0, 1428($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#+	m_i_1	1	m_i_1
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)

#=	m_i_1		39_t
lw	$t0, 64($sp)
sw	$t0, 1432($sp)

#=	$97		40_t
li	$t0, 97
sw	$t0, 1436($sp)

#+	40_t	10	40_t
lw	$t0, 1436($sp)
li	$t1, 10
add	$t2, $t0, $t1
sw	$t2, 1436($sp)

#<	39_t	40_t	41_t
lw	$t0, 1432($sp)
lw	$t1, 1436($sp)
slt	$t2, $t0, $t1
sw	$t2, 1440($sp)

#BNZ	41_t	lable_10	
lw	$t0, 1440($sp)
bne	$t0, $0, lable_10

#PRINT	STRING	string_5	
la	$a0, string_5
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	0		42_t
li	$t0, 0
sw	$t0, 1444($sp)

#=	42_t		m_i_1
lw	$t0, 1444($sp)
sw	$t0, 64($sp)

#LABLE	lable_11		
lable_11:

#=	0		43_t
li	$t0, 0
sw	$t0, 1448($sp)

#=	43_t		m_i_2
lw	$t0, 1448($sp)
sw	$t0, 72($sp)

#LABLE	lable_12		
lable_12:

#=	m_i_1		44_t
lw	$t0, 64($sp)
sw	$t0, 1452($sp)

#+	44_t	m_i_2	44_t
lw	$t0, 1452($sp)
lw	$t1, 72($sp)
add	$t2, $t0, $t1
sw	$t2, 1452($sp)

#PRINT	INTSY	44_t	
lw	$a0, 1452($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#+	m_i_2	1	m_i_2
lw	$t0, 72($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 72($sp)

#=	m_i_2		45_t
lw	$t0, 72($sp)
sw	$t0, 1456($sp)

#=	3		46_t
li	$t0, 3
sw	$t0, 1460($sp)

#<	45_t	46_t	47_t
lw	$t0, 1456($sp)
lw	$t1, 1460($sp)
slt	$t2, $t0, $t1
sw	$t2, 1464($sp)

#BNZ	47_t	lable_12	
lw	$t0, 1464($sp)
bne	$t0, $0, lable_12

#+	m_i_1	2	m_i_1
lw	$t0, 64($sp)
li	$t1, 2
add	$t2, $t0, $t1
sw	$t2, 64($sp)

#=	m_i_1		48_t
lw	$t0, 64($sp)
sw	$t0, 1468($sp)

#=	5		49_t
li	$t0, 5
sw	$t0, 1472($sp)

#<	48_t	49_t	50_t
lw	$t0, 1468($sp)
lw	$t1, 1472($sp)
slt	$t2, $t0, $t1
sw	$t2, 1476($sp)

#BNZ	50_t	lable_11	
lw	$t0, 1476($sp)
bne	$t0, $0, lable_11

#=	9		51_t
li	$t0, 9
sw	$t0, 1480($sp)

#=[]	m_i_4	51_t	52_t
la	$t0, 80
add	$t0, $t0 ,$sp
lw	$t1, 1480($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 1484($sp)

#=	52_t		53_t
lw	$t0, 1484($sp)
sw	$t0, 1488($sp)

#PRINT	INTSY	53_t	
lw	$a0, 1488($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#PRINT	STRING	string_6	
la	$a0, string_6
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	0		54_t
li	$t0, 0
sw	$t0, 1492($sp)

#=	54_t		m_i_1
lw	$t0, 1492($sp)
sw	$t0, 64($sp)

#LABLE	lable_13		
lable_13:

#PRINT	STRING	string_7	
la	$a0, string_7
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#+	m_i_1	1	m_i_1
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)

#=	m_i_1		55_t
lw	$t0, 64($sp)
sw	$t0, 1496($sp)

#=	1		56_t
li	$t0, 1
sw	$t0, 1500($sp)

#==	55_t	56_t	57_t
lw	$t0, 1496($sp)
lw	$t1, 1500($sp)
seq	$t2, $t0, $t1
sw	$t2, 1504($sp)

#BNZ	57_t	lable_13	
lw	$t0, 1504($sp)
bne	$t0, $0, lable_13

#=	8		58_t
li	$t0, 8
sw	$t0, 1508($sp)

#=[]	m_i_4	58_t	59_t
la	$t0, 80
add	$t0, $t0 ,$sp
lw	$t1, 1508($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 1512($sp)

#=	59_t		60_t
lw	$t0, 1512($sp)
sw	$t0, 1516($sp)

#PRINT	INTSY	60_t	
lw	$a0, 1516($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	m_i_1		61_t
lw	$t0, 64($sp)
sw	$t0, 1520($sp)

#PUSH	61_t	a	fun1
lw	$t0, 1520($sp)
subi	$sp, $sp, 56
sw	$t0, 36($sp)
addi	$sp, $sp, 56

#=	m_i_1		62_t
lw	$t0, 64($sp)
sw	$t0, 1524($sp)

#PUSH	62_t	b	fun1
lw	$t0, 1524($sp)
subi	$sp, $sp, 56
sw	$t0, 40($sp)
addi	$sp, $sp, 56

#CALL	fun1		
jal	fun1

#LOAD_RETURN_VALUE			63_t
sw	$v0, 1528($sp)

#=	63_t		64_t
lw	$t0, 1528($sp)
sw	$t0, 1532($sp)

#PRINT	INTSY	64_t	
lw	$a0, 1532($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#CALL	fun5		
jal	fun5

#LOAD_RETURN_VALUE			65_t
sw	$v0, 1536($sp)

#=	m_i_1		66_t
lw	$t0, 64($sp)
sw	$t0, 1540($sp)

#-	66_t	1	67_t
lw	$t0, 1540($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 1544($sp)

#BNZ	67_t	lable_15	
lw	$t0, 1544($sp)
bne	$t0, $0, lable_15

#=	m_i_1		68_t
lw	$t0, 64($sp)
sw	$t0, 1548($sp)

#PUSH	68_t	n	fun6
lw	$t0, 1548($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72

#CALL	fun6		
jal	fun6

#LOAD_RETURN_VALUE			69_t
sw	$v0, 1552($sp)

#=	69_t		70_t
lw	$t0, 1552($sp)
sw	$t0, 1556($sp)

#-	70_t	1	71_t
lw	$t0, 1556($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 1560($sp)

#BNZ	71_t	lable_17	
lw	$t0, 1560($sp)
bne	$t0, $0, lable_17

#PRINT	STRING	string_8	
la	$a0, string_8
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_17		

#LABLE	lable_17		
lable_17:

#NOP	lable_16		

#=	m_c_1		72_t
lw	$t0, 120($sp)
sw	$t0, 1564($sp)

#-	72_t	43	73_t
lw	$t0, 1564($sp)
li	$t1, 43
sub	$t2, $t0, $t1
sw	$t2, 1568($sp)

#BNZ	73_t	lable_19	
lw	$t0, 1568($sp)
bne	$t0, $0, lable_19

#=	1		74_t
li	$t0, 1
sw	$t0, 1572($sp)

#=	74_t		m_i_1
lw	$t0, 1572($sp)
sw	$t0, 64($sp)

#LABLE	lable_20		
lable_20:

#=	m_i_1		75_t
lw	$t0, 64($sp)
sw	$t0, 1576($sp)

#PUSH	75_t	n	fun6
lw	$t0, 1576($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72

#CALL	fun6		
jal	fun6

#LOAD_RETURN_VALUE			76_t
sw	$v0, 1580($sp)

#=	76_t		77_t
lw	$t0, 1580($sp)
sw	$t0, 1584($sp)

#PRINT	INTSY	77_t	
lw	$a0, 1584($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#+	m_i_1	1	m_i_1
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)

#=	m_i_1		78_t
lw	$t0, 64($sp)
sw	$t0, 1588($sp)

#=	4		79_t
li	$t0, 4
sw	$t0, 1592($sp)

#<	78_t	79_t	80_t
lw	$t0, 1588($sp)
lw	$t1, 1592($sp)
slt	$t2, $t0, $t1
sw	$t2, 1596($sp)

#BNZ	80_t	lable_20	
lw	$t0, 1596($sp)
bne	$t0, $0, lable_20

#GOTO	lable_21		
j	lable_21

#LABLE	lable_19		
lable_19:

#-	72_t	45	81_t
lw	$t0, 1564($sp)
li	$t1, 45
sub	$t2, $t0, $t1
sw	$t2, 1600($sp)

#BNZ	81_t	lable_21	
lw	$t0, 1600($sp)
bne	$t0, $0, lable_21

#PRINT	STRING	string_2	
la	$a0, string_2
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_21		

#LABLE	lable_21		
lable_21:

#NOP	lable_18		

#GOTO	lable_14		
j	lable_14

#LABLE	lable_15		
lable_15:

#-	66_t	2	82_t
lw	$t0, 1540($sp)
li	$t1, 2
sub	$t2, $t0, $t1
sw	$t2, 1604($sp)

#BNZ	82_t	lable_22	
lw	$t0, 1604($sp)
bne	$t0, $0, lable_22

#=	9		83_t
li	$t0, 9
sw	$t0, 1608($sp)

#PUSH	83_t	n	fun6
lw	$t0, 1608($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72

#CALL	fun6		
jal	fun6

#LOAD_RETURN_VALUE			84_t
sw	$v0, 1612($sp)

#=	84_t		85_t
lw	$t0, 1612($sp)
sw	$t0, 1616($sp)

#PRINT	INTSY	85_t	
lw	$a0, 1616($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#GOTO	lable_14		
j	lable_14

#LABLE	lable_22		
lable_22:

#=	0		86_t
li	$t0, 0
sw	$t0, 1620($sp)

#=	86_t		m_i_1
lw	$t0, 1620($sp)
sw	$t0, 64($sp)

#LABLE	lable_23		
lable_23:

#=	9		87_t
li	$t0, 9
sw	$t0, 1624($sp)

#PUSH	87_t	n	fun6
lw	$t0, 1624($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72

#CALL	fun6		
jal	fun6

#LOAD_RETURN_VALUE			88_t
sw	$v0, 1628($sp)

#=	88_t		89_t
lw	$t0, 1628($sp)
sw	$t0, 1632($sp)

#PRINT	INTSY	89_t	
lw	$a0, 1632($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#+	m_i_1	1	m_i_1
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)

#=	m_i_1		90_t
lw	$t0, 64($sp)
sw	$t0, 1636($sp)

#=	1		91_t
li	$t0, 1
sw	$t0, 1640($sp)

#==	90_t	91_t	92_t
lw	$t0, 1636($sp)
lw	$t1, 1640($sp)
seq	$t2, $t0, $t1
sw	$t2, 1644($sp)

#BNZ	92_t	lable_23	
lw	$t0, 1644($sp)
bne	$t0, $0, lable_23

#LABLE	lable_14		
lable_14:

#-	0	m_c_1	93_t
li	$t0, 0
lw	$t1, 120($sp)
sub	$t2, $t0, $t1
sw	$t2, 1648($sp)

#=	93_t		m_i_1
lw	$t0, 1648($sp)
sw	$t0, 64($sp)

#=	m_i_1		94_t
lw	$t0, 64($sp)
sw	$t0, 1652($sp)

#-	0	43	95_t
li	$t0, 0
li	$t1, 43
sub	$t2, $t0, $t1
sw	$t2, 1656($sp)

#==	94_t	95_t	96_t
lw	$t0, 1652($sp)
lw	$t1, 1656($sp)
seq	$t2, $t0, $t1
sw	$t2, 1660($sp)

#BZ	96_t	lable_24	
lw	$t0, 1660($sp)
beq	$t0, $0, lable_24

#PRINT	STRING	string_9	
la	$a0, string_9
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_24		

#LABLE	lable_24		
lable_24:

#NOP	lable_25		

#=	m_i_1		97_t
lw	$t0, 64($sp)
sw	$t0, 1664($sp)

#+	97_t	43	97_t
lw	$t0, 1664($sp)
li	$t1, 43
add	$t2, $t0, $t1
sw	$t2, 1664($sp)

#BZ	97_t	lable_26	
lw	$t0, 1664($sp)
beq	$t0, $0, lable_26

#PRINT	STRING	string_10	
la	$a0, string_10
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_26		

#LABLE	lable_26		
lable_26:

#NOP	lable_27		

#=	m_i_1		98_t
lw	$t0, 64($sp)
sw	$t0, 1668($sp)

#-	98_t	-43	99_t
lw	$t0, 1668($sp)
li	$t1, -43
sub	$t2, $t0, $t1
sw	$t2, 1672($sp)

#BNZ	99_t	lable_29	
lw	$t0, 1672($sp)
bne	$t0, $0, lable_29

#PRINT	STRING	string_11	
la	$a0, string_11
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_29		

#LABLE	lable_29		
lable_29:

#NOP	lable_28		

#=	m_c_1		100_t
lw	$t0, 120($sp)
sw	$t0, 1676($sp)

#-	100_t	43	101_t
lw	$t0, 1676($sp)
li	$t1, 43
sub	$t2, $t0, $t1
sw	$t2, 1680($sp)

#BNZ	101_t	lable_31	
lw	$t0, 1680($sp)
bne	$t0, $0, lable_31

#PRINT	STRING	string_12	
la	$a0, string_12
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#NOP	lable_31		

#LABLE	lable_31		
lable_31:

#NOP	lable_30		

#=	$43		102_t
li	$t0, 43
sw	$t0, 1684($sp)

#=	102_t		m_c_2
lw	$t0, 1684($sp)
sw	$t0, 124($sp)

#=	m_c_2		103_t
lw	$t0, 124($sp)
sw	$t0, 1688($sp)

#PRINT	CHARSY	103_t	
lw	$a0, 1688($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	$45		104_t
li	$t0, 45
sw	$t0, 1692($sp)

#=	104_t		m_c_2
lw	$t0, 1692($sp)
sw	$t0, 124($sp)

#=	m_c_2		105_t
lw	$t0, 124($sp)
sw	$t0, 1696($sp)

#PRINT	CHARSY	105_t	
lw	$a0, 1696($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	$42		106_t
li	$t0, 42
sw	$t0, 1700($sp)

#=	106_t		m_c_2
lw	$t0, 1700($sp)
sw	$t0, 124($sp)

#=	m_c_2		107_t
lw	$t0, 124($sp)
sw	$t0, 1704($sp)

#PRINT	CHARSY	107_t	
lw	$a0, 1704($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	$47		108_t
li	$t0, 47
sw	$t0, 1708($sp)

#=	108_t		m_c_2
lw	$t0, 1708($sp)
sw	$t0, 124($sp)

#=	m_c_2		109_t
lw	$t0, 124($sp)
sw	$t0, 1712($sp)

#PRINT	CHARSY	109_t	
lw	$a0, 1712($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	$95		110_t
li	$t0, 95
sw	$t0, 1716($sp)

#=	110_t		m_c_2
lw	$t0, 1716($sp)
sw	$t0, 124($sp)

#=	m_c_2		111_t
lw	$t0, 124($sp)
sw	$t0, 1720($sp)

#PRINT	CHARSY	111_t	
lw	$a0, 1720($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#=	$97		112_t
li	$t0, 97
sw	$t0, 1724($sp)

#=	112_t		m_i_1
lw	$t0, 1724($sp)
sw	$t0, 64($sp)

#LABLE	lable_32		
lable_32:

#=	m_i_1		113_t
lw	$t0, 64($sp)
sw	$t0, 1728($sp)

#=	113_t		m_c_2
lw	$t0, 1728($sp)
sw	$t0, 124($sp)

#=	m_c_2		114_t
lw	$t0, 124($sp)
sw	$t0, 1732($sp)

#PRINT	CHARSY	114_t	
lw	$a0, 1732($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#+	m_i_1	1	m_i_1
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)

#=	m_i_1		115_t
lw	$t0, 64($sp)
sw	$t0, 1736($sp)

#=	$122		116_t
li	$t0, 122
sw	$t0, 1740($sp)

#<=	115_t	116_t	117_t
lw	$t0, 1736($sp)
lw	$t1, 1740($sp)
sle	$t2, $t0, $t1
sw	$t2, 1744($sp)

#BNZ	117_t	lable_32	
lw	$t0, 1744($sp)
bne	$t0, $0, lable_32

#=	$65		118_t
li	$t0, 65
sw	$t0, 1748($sp)

#=	118_t		m_i_1
lw	$t0, 1748($sp)
sw	$t0, 64($sp)

#LABLE	lable_33		
lable_33:

#=	m_i_1		119_t
lw	$t0, 64($sp)
sw	$t0, 1752($sp)

#=	119_t		m_c_2
lw	$t0, 1752($sp)
sw	$t0, 124($sp)

#=	m_c_2		120_t
lw	$t0, 124($sp)
sw	$t0, 1756($sp)

#PRINT	CHARSY	120_t	
lw	$a0, 1756($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#+	m_i_1	1	m_i_1
lw	$t0, 64($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 64($sp)

#=	m_i_1		121_t
lw	$t0, 64($sp)
sw	$t0, 1760($sp)

#=	$90		122_t
li	$t0, 90
sw	$t0, 1764($sp)

#<=	121_t	122_t	123_t
lw	$t0, 1760($sp)
lw	$t1, 1764($sp)
sle	$t2, $t0, $t1
sw	$t2, 1768($sp)

#BNZ	123_t	lable_33	
lw	$t0, 1768($sp)
bne	$t0, $0, lable_33

#SCANF	INTSY	m_i_1	
li	$v0, 5
syscall
sw	$v0, 64($sp)

#=	m_i_1		124_t
lw	$t0, 64($sp)
sw	$t0, 1772($sp)

#PRINT	INTSY	124_t	
lw	$a0, 1772($sp)
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#SCANF	CHARSY	m_c_1	
li	$v0, 12
syscall
sw	$v0, 120($sp)

#=	m_c_1		125_t
lw	$t0, 120($sp)
sw	$t0, 1776($sp)

#PRINT	CHARSY	125_t	
lw	$a0, 1776($sp)
li	$v0, 11
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#PRINT	STRING	string_13	
la	$a0, string_13
li	$v0, 4
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#TERMINATE			
li	$v0, 10
syscall

