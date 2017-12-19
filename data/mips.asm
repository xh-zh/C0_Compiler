.data
string_0:	.asciiz	"\n"
#FUN	BEGIN		
.text
j	main

#FUN	VOID	main	
main:
subi	$sp, $sp, 80
sw	$ra, 0($sp)

#VAL	INTSY		m_i_1

#VAL	INTSY		m_i_2

#+	0	0	0_t
add	$s0, $0, $0

#=	0_t		m_i_1
move	$s3, $s0

#LABLE	lable_0		
lable_0:

#+	0	0	1_t
add	$s4, $0, $0

#=	1_t		m_i_2
move	$s7, $s4

#LABLE	lable_1		
lable_1:

#+	0	m_i_1	2_t
sw	$s0, 44($sp)
add	$s0, $0, $s3

#+	2_t	m_i_2	2_t
add	$s0, $s0, $s7

#PRINT	INTSY	2_t	
move	$a0, $s0
li	$v0, 1
syscall

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall

#+	m_i_2	1	m_i_2
li	$s1, 1
add	$s7, $s7, $s1

#+	0	m_i_2	3_t
add	$s2, $0, $s7

#+	0	5	4_t
sw	$s3, 36($sp)
li	$s3, 5
sw	$s4, 48($sp)
add	$s4, $0, $s3

#<	3_t	4_t	5_t
slt	$s5, $s2, $s4

#BNZ	5_t	lable_1	
bne	$s5, $0, lable_1

#+	m_i_1	1	m_i_1
sw	$s7, 40($sp)
lw	$s7, 36($sp)
add	$s7, $s7, $s1

#+	0	m_i_1	6_t
sw	$s0, 52($sp)
add	$s0, $0, $s7

#+	0	5	7_t
add	$s1, $0, $s3

#<	6_t	7_t	8_t
sw	$s2, 56($sp)
slt	$s2, $s0, $s1

#BNZ	8_t	lable_0	
bne	$s2, $0, lable_0

#TERMINATE			
li	$v0, 10
syscall

