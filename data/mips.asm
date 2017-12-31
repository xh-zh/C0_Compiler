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
c_1: .word	0
c_2: .word	0
c_3: .word	0
c_4: .word	1 : 10
.text
j	main
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
subi	$sp, $sp, 1780
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
li	$t0, 1
sw	$t0, 1332($sp)
lw	$t0, 1332($sp)
sw	$t0, 64($sp)
li	$t0, 100
sw	$t0, 1336($sp)
lw	$t0, 1336($sp)
sw	$t0, 68($sp)
li	$t0, 1
sw	$t0, 1340($sp)
lw	$t0, 1340($sp)
sw	$t0, 72($sp)
li	$t0, 2
sw	$t0, 1344($sp)
lw	$t0, 1344($sp)
sw	$t0, 76($sp)
li	$t0, 43
sw	$t0, 1348($sp)
lw	$t0, 1348($sp)
sw	$t0, 120($sp)
li	$t0, 45
sw	$t0, 1352($sp)
lw	$t0, 1352($sp)
sw	$t0, 124($sp)
li	$t0, 42
sw	$t0, 1356($sp)
lw	$t0, 1356($sp)
sw	$t0, 128($sp)
lw	$t0, 64($sp)
sw	$t0, 1360($sp)
li	$t0, 100
sw	$t0, 1364($sp)
lw	$t0, 1360($sp)
lw	$t1, 1364($sp)
seq	$t2, $t0, $t1
sw	$t2, 1368($sp)
lw	$t0, 1368($sp)
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
sw	$t0, 1372($sp)
lw	$t0, 1372($sp)
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
sw	$t0, 1376($sp)
li	$t0, 1
sw	$t0, 1380($sp)
lw	$t0, 1376($sp)
lw	$t1, 1380($sp)
sgt	$t2, $t0, $t1
sw	$t2, 1384($sp)
lw	$t0, 1384($sp)
beq	$t0, $0, lable_6
li	$t0, 0
lw	$t1, 76($sp)
neg	$t2, $t1
sw	$t2, 1388($sp)
lw	$t0, 1388($sp)
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, 1388($sp)
lw	$t0, 1388($sp)
sw	$t0, 76($sp)
lw	$t0, 76($sp)
sw	$t0, 1392($sp)
lw	$a0, 1392($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_7
lable_6:
lable_7:
lw	$t0, 76($sp)
sw	$t0, 1396($sp)
lw	$t0, 36($sp)
sw	$t0, 1400($sp)
lw	$t0, 1396($sp)
lw	$t1, 1400($sp)
seq	$t2, $t0, $t1
xori	$t2, 1
sw	$t2, 1404($sp)
lw	$t0, 1404($sp)
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
sw	$t0, 1408($sp)
lw	$t0, 1408($sp)
sw	$t0, 64($sp)
lable_10:
lw	$t0, 64($sp)
sw	$t0, 1412($sp)
lw	$t0, 64($sp)
sw	$t0, 1416($sp)
li	$t0, 132
add	$t0, $t0, $sp
lw	$t1, 1412($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t1, 1416($sp)
sw	$t1, 0($t0)
lw	$t0, 64($sp)
sw	$t0, 1420($sp)
la	$t0, 132
add	$t0, $t0 ,$sp
lw	$t1, 1420($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 1424($sp)
lw	$t0, 1424($sp)
sw	$t0, 1428($sp)
lw	$a0, 1428($sp)
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
sw	$t0, 1432($sp)
li	$t0, 97
sw	$t0, 1436($sp)
lw	$t0, 1436($sp)
li	$t1, 10
add	$t2, $t0, $t1
sw	$t2, 1436($sp)
lw	$t0, 1432($sp)
lw	$t1, 1436($sp)
slt	$t2, $t0, $t1
sw	$t2, 1440($sp)
lw	$t0, 1440($sp)
bne	$t0, $0, lable_10
la	$a0, string_5
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 0
sw	$t0, 1444($sp)
lw	$t0, 1444($sp)
sw	$t0, 64($sp)
lable_11:
li	$t0, 0
sw	$t0, 1448($sp)
lw	$t0, 1448($sp)
sw	$t0, 72($sp)
lable_12:
lw	$t0, 64($sp)
sw	$t0, 1452($sp)
lw	$t0, 1452($sp)
lw	$t1, 72($sp)
add	$t2, $t0, $t1
sw	$t2, 1452($sp)
lw	$a0, 1452($sp)
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
sw	$t0, 1456($sp)
li	$t0, 3
sw	$t0, 1460($sp)
lw	$t0, 1456($sp)
lw	$t1, 1460($sp)
slt	$t2, $t0, $t1
sw	$t2, 1464($sp)
lw	$t0, 1464($sp)
bne	$t0, $0, lable_12
lw	$t0, 64($sp)
li	$t1, 2
add	$t2, $t0, $t1
sw	$t2, 64($sp)
lw	$t0, 64($sp)
sw	$t0, 1468($sp)
li	$t0, 5
sw	$t0, 1472($sp)
lw	$t0, 1468($sp)
lw	$t1, 1472($sp)
slt	$t2, $t0, $t1
sw	$t2, 1476($sp)
lw	$t0, 1476($sp)
bne	$t0, $0, lable_11
li	$t0, 9
sw	$t0, 1480($sp)
la	$t0, 80
add	$t0, $t0 ,$sp
lw	$t1, 1480($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 1484($sp)
lw	$t0, 1484($sp)
sw	$t0, 1488($sp)
lw	$a0, 1488($sp)
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
sw	$t0, 1492($sp)
lw	$t0, 1492($sp)
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
sw	$t0, 1496($sp)
li	$t0, 1
sw	$t0, 1500($sp)
lw	$t0, 1496($sp)
lw	$t1, 1500($sp)
seq	$t2, $t0, $t1
sw	$t2, 1504($sp)
lw	$t0, 1504($sp)
bne	$t0, $0, lable_13
li	$t0, 8
sw	$t0, 1508($sp)
la	$t0, 80
add	$t0, $t0 ,$sp
lw	$t1, 1508($sp)
sll	$t1, $t1, 2
add	$t0, $t0, $t1
lw	$t0, 0($t0)
sw	$t0, 1512($sp)
lw	$t0, 1512($sp)
sw	$t0, 1516($sp)
lw	$a0, 1516($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
lw	$t0, 64($sp)
sw	$t0, 1520($sp)
lw	$t0, 1520($sp)
subi	$sp, $sp, 56
sw	$t0, 36($sp)
addi	$sp, $sp, 56
lw	$t0, 64($sp)
sw	$t0, 1524($sp)
lw	$t0, 1524($sp)
subi	$sp, $sp, 56
sw	$t0, 40($sp)
addi	$sp, $sp, 56
jal	fun1
sw	$v0, 1528($sp)
lw	$t0, 1528($sp)
sw	$t0, 1532($sp)
lw	$a0, 1532($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
jal	fun5
sw	$v0, 1536($sp)
lw	$t0, 64($sp)
sw	$t0, 1540($sp)
lw	$t0, 1540($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 1544($sp)
lw	$t0, 1544($sp)
bne	$t0, $0, lable_15
lw	$t0, 64($sp)
sw	$t0, 1548($sp)
lw	$t0, 1548($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 1552($sp)
lw	$t0, 1552($sp)
sw	$t0, 1556($sp)
lw	$t0, 1556($sp)
li	$t1, 1
sub	$t2, $t0, $t1
sw	$t2, 1560($sp)
lw	$t0, 1560($sp)
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
sw	$t0, 1564($sp)
lw	$t0, 1564($sp)
li	$t1, 43
sub	$t2, $t0, $t1
sw	$t2, 1568($sp)
lw	$t0, 1568($sp)
bne	$t0, $0, lable_19
li	$t0, 1
sw	$t0, 1572($sp)
lw	$t0, 1572($sp)
sw	$t0, 64($sp)
lable_20:
lw	$t0, 64($sp)
sw	$t0, 1576($sp)
lw	$t0, 1576($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 1580($sp)
lw	$t0, 1580($sp)
sw	$t0, 1584($sp)
lw	$a0, 1584($sp)
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
sw	$t0, 1588($sp)
li	$t0, 4
sw	$t0, 1592($sp)
lw	$t0, 1588($sp)
lw	$t1, 1592($sp)
slt	$t2, $t0, $t1
sw	$t2, 1596($sp)
lw	$t0, 1596($sp)
bne	$t0, $0, lable_20
j	lable_18
lable_19:
lw	$t0, 1564($sp)
li	$t1, 45
sub	$t2, $t0, $t1
sw	$t2, 1600($sp)
lw	$t0, 1600($sp)
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
lw	$t0, 1540($sp)
li	$t1, 2
sub	$t2, $t0, $t1
sw	$t2, 1604($sp)
lw	$t0, 1604($sp)
bne	$t0, $0, lable_22
li	$t0, 9
sw	$t0, 1608($sp)
lw	$t0, 1608($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 1612($sp)
lw	$t0, 1612($sp)
sw	$t0, 1616($sp)
lw	$a0, 1616($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
j	lable_14
lable_22:
li	$t0, 0
sw	$t0, 1620($sp)
lw	$t0, 1620($sp)
sw	$t0, 64($sp)
lable_23:
li	$t0, 9
sw	$t0, 1624($sp)
lw	$t0, 1624($sp)
subi	$sp, $sp, 72
sw	$t0, 36($sp)
addi	$sp, $sp, 72
jal	fun6
sw	$v0, 1628($sp)
lw	$t0, 1628($sp)
sw	$t0, 1632($sp)
lw	$a0, 1632($sp)
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
sw	$t0, 1636($sp)
li	$t0, 1
sw	$t0, 1640($sp)
lw	$t0, 1636($sp)
lw	$t1, 1640($sp)
seq	$t2, $t0, $t1
sw	$t2, 1644($sp)
lw	$t0, 1644($sp)
bne	$t0, $0, lable_23
lable_14:
li	$t0, 0
lw	$t1, 120($sp)
neg	$t2, $t1
sw	$t2, 1648($sp)
lw	$t0, 1648($sp)
sw	$t0, 64($sp)
lw	$t0, 64($sp)
sw	$t0, 1652($sp)
li	$t0, 0
li	$t1, 43
neg	$t2, $t1
sw	$t2, 1656($sp)
lw	$t0, 1652($sp)
lw	$t1, 1656($sp)
seq	$t2, $t0, $t1
sw	$t2, 1660($sp)
lw	$t0, 1660($sp)
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
sw	$t0, 1664($sp)
lw	$t0, 1664($sp)
li	$t1, 43
add	$t2, $t0, $t1
sw	$t2, 1664($sp)
lw	$t0, 1664($sp)
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
sw	$t0, 1668($sp)
lw	$t0, 1668($sp)
li	$t1, -43
sub	$t2, $t0, $t1
sw	$t2, 1672($sp)
lw	$t0, 1672($sp)
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
sw	$t0, 1676($sp)
lw	$t0, 1676($sp)
li	$t1, 43
sub	$t2, $t0, $t1
sw	$t2, 1680($sp)
lw	$t0, 1680($sp)
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
sw	$t0, 1684($sp)
lw	$t0, 1684($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 1688($sp)
lw	$a0, 1688($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 45
sw	$t0, 1692($sp)
lw	$t0, 1692($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 1696($sp)
lw	$a0, 1696($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 42
sw	$t0, 1700($sp)
lw	$t0, 1700($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 1704($sp)
lw	$a0, 1704($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 47
sw	$t0, 1708($sp)
lw	$t0, 1708($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 1712($sp)
lw	$a0, 1712($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 95
sw	$t0, 1716($sp)
lw	$t0, 1716($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 1720($sp)
lw	$a0, 1720($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$t0, 97
sw	$t0, 1724($sp)
lw	$t0, 1724($sp)
sw	$t0, 64($sp)
lable_32:
lw	$t0, 64($sp)
sw	$t0, 1728($sp)
lw	$t0, 1728($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 1732($sp)
lw	$a0, 1732($sp)
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
sw	$t0, 1736($sp)
li	$t0, 122
sw	$t0, 1740($sp)
lw	$t0, 1736($sp)
lw	$t1, 1740($sp)
sle	$t2, $t0, $t1
sw	$t2, 1744($sp)
lw	$t0, 1744($sp)
bne	$t0, $0, lable_32
li	$t0, 65
sw	$t0, 1748($sp)
lw	$t0, 1748($sp)
sw	$t0, 64($sp)
lable_33:
lw	$t0, 64($sp)
sw	$t0, 1752($sp)
lw	$t0, 1752($sp)
sw	$t0, 124($sp)
lw	$t0, 124($sp)
sw	$t0, 1756($sp)
lw	$a0, 1756($sp)
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
sw	$t0, 1760($sp)
li	$t0, 90
sw	$t0, 1764($sp)
lw	$t0, 1760($sp)
lw	$t1, 1764($sp)
sle	$t2, $t0, $t1
sw	$t2, 1768($sp)
lw	$t0, 1768($sp)
bne	$t0, $0, lable_33
li	$v0, 5
syscall
sw	$v0, 64($sp)
lw	$t0, 64($sp)
sw	$t0, 1772($sp)
lw	$a0, 1772($sp)
li	$v0, 1
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 12
syscall
sw	$v0, 120($sp)
lw	$t0, 120($sp)
sw	$t0, 1776($sp)
lw	$a0, 1776($sp)
li	$v0, 11
syscall
la	$a0, string_0
li	$v0, 4
syscall
la	$a0, string_13
li	$v0, 4
syscall
la	$a0, string_0
li	$v0, 4
syscall
li	$v0, 10
syscall
