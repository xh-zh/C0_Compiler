.data
string_0:	.asciiz	"\n"
string_1:	.asciiz	"Error!"
string_2:	.asciiz	"Test_1"
string_3:	.asciiz	"Test_2"
string_4:	.asciiz	"Test_3"
string_5:	.asciiz	"Test_4"
string_6:	.asciiz	"Test_5"
string_7:	.asciiz	"Test_1_Error"
string_8:	.asciiz	"Test_1_Correct"
string_9:	.asciiz	"Test_2_Error"
string_10:	.asciiz	"Test_2_Correct"
string_11:	.asciiz	"Test_3_Error"
string_12:	.asciiz	"Test_3_Correct"
string_13:	.asciiz	"Test_4_Error"
string_14:	.asciiz	"Test_4_Correct"
string_15:	.asciiz	"Test_5_Error"
string_16:	.asciiz	"Test_5_Correct"
string_17:	.asciiz	"Test_6_Error"
string_18:	.asciiz	"Test_6_Correct"
string_19:	.asciiz	"DONE!"
#~FUN	~BEGIN		
.text
j	main

#~FUN	!VOID	main	
main:
subi	$sp, $sp, 664
sw	$ra, 0($sp)

#~CONST	!INTSY	1	m_con_i_1
li	$t0, 1
sw	$t0, 36($sp)

#~CONST	!INTSY	100	M_con_i_1
li	$t0, 100
sw	$t0, 40($sp)

#~CONST	!INTSY	1	m_con_i_2
li	$t0, 1
sw	$t0, 44($sp)

#~CONST	!INTSY	2	m_con_i_3
li	$t0, 2
sw	$t0, 48($sp)

#~CONST	!CHARSY	43	m_con_c_1
li	$t0, 43
sw	$t0, 52($sp)

#~CONST	!CHARSY	45	m_con_c_2
li	$t0, 45
sw	$t0, 56($sp)

#~CONST	!CHARSY	42	m_con_c_3
li	$t0, 42
sw	$t0, 60($sp)

#~VAL	!INTSY		m_i_1

#~VAL	!INTSY		M_i_1

#~VAL	!INTSY		m_i_2

#~VAL	!INTSY		m_i_3

#~ARRAY	!INTSY	10	m_i_4

#~VAL	!CHARSY		m_c_1

#~VAL	!CHARSY		m_c_2

#~VAL	!CHARSY		m_c_3

#~ARRAY	!CHARSY	10	m_c_4

#~VAL	!INTSY		i

#~VAL	!INTSY		j

#~VAL	!INTSY		k

#~VAL	!INTSY		m

#~VAL	!CHARSY		c

#=	$97		0_t
li	$a3, 97
move	$t0, $a3

