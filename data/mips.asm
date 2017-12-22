.data
string_0:	.asciiz	"\n"
#FUN	BEGIN		
.text
j	main
#Reg: $0	
#Reg: $1	
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#FUN	VOID	main	
main:
subi	$sp, $sp, 160
sw	$ra, 0($sp)
#Reg: $0	
#Reg: $1	
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#VAL	INTSY		m_i_1
#Reg: $0	
#Reg: $1	
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#VAL	INTSY		m_i_2
#Reg: $0	
#Reg: $1	
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#ARRAY	CHARSY	10	m_c_4
#Reg: $0	
#Reg: $1	
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#=	1		0_t
li	$s0, 1
#Reg: $0	0_t
#Reg: $1	
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#=	0_t		m_i_1
sw	$s0, 36($sp)
#Reg: $0	0_t
#Reg: $1	
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#=	$97		1_t
li	$s1, 97
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#=	1_t		m_i_1
sw	$s1, 36($sp)
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#LABLE	lable_0		
lable_0:
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#=	m_i_1		2_t
lw	$s2, 36($sp)
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#=	m_i_1		3_t
lw	$s3, 36($sp)
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#[]=	2_t	3_t	m_c_4
lw	$s2, 92($sp)
lw	$s3, 96($sp)
li	$t0, 44
add	$t0, $t0, $sp
sll	$t1, $s2, 2
add	$t0, $t0, $t1
sw	$s3, 0($t0)
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	
#Reg: $5	
#Reg: $6	
#Reg: $7	

#=	m_i_1		4_t
lw	$s4, 36($sp)
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	
#Reg: $6	
#Reg: $7	

#=[]	m_c_4	4_t	5_t
lw	$s4, 100($sp)
la	$t0, 44
add	$t0, $t0 ,$sp
sll	$t1, $s4, 2
add	$t0, $t0, $t1
lw	$s5, 0($t0)
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	
#Reg: $7	

#=	5_t		6_t
move	$s6, $s6
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	

#PRINT	CHARSY	6_t	
move	$a0, $s6
li	$v0, 11
syscall
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	

#+	m_i_1	1	m_i_1
lw	$t0, 36($sp)
li	$t1, 1
add	$t2, $t0, $t1
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	

#=	m_i_1		7_t
lw	$s7, 36($sp)
#Reg: $0	0_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#=	$97		8_t
sw	$s0, 84($sp)
li	$s0, 97
#Reg: $0	8_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#+	8_t	10	8_t
lw	$s0, 116($sp)
li	$t1, 10
add	$s0, $s0, $t1
sw	$s0, 116($sp)
#Reg: $0	8_t
#Reg: $1	1_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#<	7_t	8_t	9_t
lw	$s7, 112($sp)
lw	$s0, 116($sp)
sw	$s1, 88($sp)
slt	$s1, $s7, $s0
sw	$s1, 120($sp)
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#BNZ	9_t	lable_0	
lw	$s1, 120($sp)
beq $s1, $0, lable_3
sw	$s0, 116($sp)
sw	$s1, 120($sp)
sw	$s2, 92($sp)
sw	$s3, 96($sp)
sw	$s4, 100($sp)
sw	$s5, 104($sp)
sw	$s6, 108($sp)
sw	$s7, 112($sp)
lable_3:
bne	$s1, $0, lable_0
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	2_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#=	0		10_t
sw	$s2, 92($sp)
li	$s2, 0
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#=	10_t		m_i_1
sw	$s2, 36($sp)
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#LABLE	lable_1		
lable_1:
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	3_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#=	0		11_t
sw	$s3, 96($sp)
li	$s3, 0
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#=	11_t		m_i_2
sw	$s3, 40($sp)
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#LABLE	lable_2		
lable_2:
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	4_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#=	m_i_1		12_t
sw	$s4, 100($sp)
lw	$s4, 36($sp)
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#+	12_t	m_i_2	12_t
lw	$s4, 132($sp)
lw	$t1, 40($sp)
add	$s4, $s4, $t1
sw	$s4, 132($sp)
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#PRINT	INTSY	12_t	
move	$a0, $s4
li	$v0, 1
syscall
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#PRINT	STRING	string_0	
la	$a0, string_0
li	$v0, 4
syscall
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#+	m_i_2	1	m_i_2
lw	$t0, 40($sp)
li	$t1, 1
add	$t2, $t0, $t1
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	5_t
#Reg: $6	6_t
#Reg: $7	7_t

#=	m_i_2		13_t
sw	$s5, 104($sp)
lw	$s5, 40($sp)
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	6_t
#Reg: $7	7_t

#=	3		14_t
sw	$s6, 108($sp)
li	$s6, 3
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	7_t

#<	13_t	14_t	15_t
lw	$s5, 136($sp)
lw	$s6, 140($sp)
sw	$s7, 112($sp)
slt	$s7, $s5, $s6
sw	$s7, 144($sp)
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	15_t

#BNZ	15_t	lable_2	
lw	$s7, 144($sp)
beq $s7, $0, lable_4
sw	$s0, 116($sp)
sw	$s1, 120($sp)
sw	$s2, 124($sp)
sw	$s3, 128($sp)
sw	$s4, 132($sp)
sw	$s5, 136($sp)
sw	$s6, 140($sp)
sw	$s7, 144($sp)
lable_4:
bne	$s7, $0, lable_2
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	15_t

#+	m_i_1	1	m_i_1
lw	$t0, 36($sp)
li	$t1, 1
add	$t2, $t0, $t1
#Reg: $0	8_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	15_t

#=	m_i_1		16_t
sw	$s0, 116($sp)
lw	$s0, 36($sp)
#Reg: $0	16_t
#Reg: $1	9_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	15_t

#=	5		17_t
sw	$s1, 120($sp)
li	$s1, 5
#Reg: $0	16_t
#Reg: $1	17_t
#Reg: $2	10_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	15_t

#<	16_t	17_t	18_t
lw	$s0, 148($sp)
lw	$s1, 152($sp)
sw	$s2, 124($sp)
slt	$s2, $s0, $s1
sw	$s2, 156($sp)
#Reg: $0	16_t
#Reg: $1	17_t
#Reg: $2	18_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	15_t

#BNZ	18_t	lable_1	
lw	$s2, 156($sp)
beq $s2, $0, lable_5
sw	$s0, 148($sp)
sw	$s1, 152($sp)
sw	$s2, 156($sp)
sw	$s3, 128($sp)
sw	$s4, 132($sp)
sw	$s5, 136($sp)
sw	$s6, 140($sp)
sw	$s7, 144($sp)
lable_5:
bne	$s2, $0, lable_1
#Reg: $0	16_t
#Reg: $1	17_t
#Reg: $2	18_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	15_t

#TERMINATE			
li	$v0, 10
syscall
#Reg: $0	16_t
#Reg: $1	17_t
#Reg: $2	18_t
#Reg: $3	11_t
#Reg: $4	12_t
#Reg: $5	13_t
#Reg: $6	14_t
#Reg: $7	15_t

