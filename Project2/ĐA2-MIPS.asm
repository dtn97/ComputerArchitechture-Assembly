main:

.data 
	chuoi: .space 40  
	s0: .asciiz "\n\n\n"
	menu: .asciiz "\n----------Ban hay chon 1 trong cac thao tac duoi day ------\n"
	s1: .asciiz "1. Xuat chuoi TIME theo dinh dang DD/MM/YYYY \n"
	s2: .asciiz "2. Chuyen doi chuoi TIME thanh mot trong cac dinh dang sau và xuat ra: \n"
	s2a: .asciiz "		A. MM/DD/YYYY\n"
	s2b: .asciiz "		B. Month DD, YYYY \n"
	s2c: .asciiz "		C. DD Month, YYYY \n"
	s3: .asciiz "3. Cho biet ngay vua nhap là ngay thu may trong tuan\n"
	s4: .asciiz "4. Kiem tra nam trong chuoi TIME co phai là nam nhuan khong \n"
	s5: .asciiz "5. Cho biet khoang thoi gian giua chuoi TIME_1 va TIME_2 \n"
	s6: .asciiz "6. Cho biet 2 nam nhuan gan nhat voi nam trong chuoi time \n"
	s7: .asciiz "7. Thoat \n"
	choose: .asciiz "Lua chon: "
	res: .asciiz "\nKet qua: "
	chuoi1: .space 40
	chuoi2: .space 40
.text

	la $a0,chuoi	
	jal input			#goi ham input voi vùng nho chuoi
	add $t3,$v0,$0			# l?u kq vào t3
	
MENU:	
	la $a0, s0
	li $v0, 4
	syscall				# xuat chuoi s0. Tuong t? ben duoi

	la $a0, menu
	syscall
 
	la $a0, s1
	syscall
 
	la $a0, s2
	syscall
 
	la $a0, s2a
	syscall
 
	la $a0, s2b
	syscall
 
	la $a0, s2c
	syscall
 
	la $a0, s3
	syscall
 
	la $a0, s4
	syscall
 
	la $a0, s5
	syscall

	la $a0, s6
	syscall

	la $a0, s7
	syscall

	la $a0, choose
	syscall
	
	li $v0,5				# nhap vao integer. luu vao $v0
	syscall

	addi $t0,$0,1				# t0=1
	add $t1,$v0,$0				# t1 = v0 (so vua nhap)

	beq $t0,$t1, S1				# if ( t1 == t0 (1)) -> S1

	addi $t0,$t0,1				#t??ng t? trên
	beq $t0,$t1, S2

	addi $t0,$t0,1
	beq $t0,$t1, S3

	addi $t0,$t0,1
	beq $t0,$t1, S4

	addi $t0,$t0,1
	beq $t0,$t1, S5

	addi $t0,$t0,1
	beq $t0,$t1, S6

	addi $t0,$t0,1
	beq $t0,$t1, EXIT

S1:
	la $a0,res				
	li $v0, 4
	syscall
 
	add $a0,$t3,$0				# gán $a0 = $t3 (bi?n l?u ? ??u bài)
	li $v0, 4				
	syscall					#in chu?i 
	
	addi $a0,$0,1500			#sleep 1.5s
	li $v0,32
	syscall
	j MENU
S2:	
	la $a0, choose
	li $v0,4
	syscall
	
#	la $a0,chuoi
#	jal input
#	add $t3,$v0,$0

	li $v0,12				# nh?p kí t?. l?u vào $v0
	syscall

	add $a1,$0,$v0

	la $a0, res
	li $v0,4
	syscall 

	add $a0,$t3,$0
	
	jal Convert			#423
	add $a0,$v0,$0
	li $v0,4
	syscall 

	addi $a0,$0,1500
	li $v0,32
	syscall
	j MENU

S3:		
	la $a0, res
	li $v0,4
	syscall
	
	add $a0,$t3,$0

	jal Weekday			#line 893

	add $a0,$v0,$0

	li $v0,4
	syscall

	addi $a0,$0,1500
	li $v0,32
	syscall
	j MENU
S4:	
	la $a0, res
	li $v0,4
	syscall

	add $a0,$t3,$0
	
	jal LeapYear			#line 1059

	.data 
	leap: .asciiz "Nam nhuan\n"
	nleap:.asciiz "Nam khong nhuan\n"
	.text 
	
	beq $v0, $0, NLEAP		
	la $a0 leap
	j next

NLEAP:  la $a0,nleap
next:	li $v0,4
	syscall
	
	addi $a0,$0,1500
	li $v0,32
	syscall
	j MENU

S5:
	la $a0,chuoi1
	jal input			#line 229
	add $a1,$v0,$0

	la $a0,chuoi2
	jal input			#line 229
	add $a0,$v0,$0

	jal GetTime			#line 1076

	add $t2,$v0,$0
	la $a0, res
	li $v0,4
	syscall

	add $a0,$t2,$0
	li $v0,1
	syscall 

	addi $a0,$0,1500
	li $v0,32
	syscall

	j MENU
	
S6:		
	la $a0, res
	li $v0,4
	syscall
	
	add $a0, $t3,$0
	
	jal TwoNextLeapYear      #line 370

	add $a0, $v0, $0
	li $v0,1
	syscall

	.data 
	Tab: .asciiz "\t"
	.text 
	la $a0,Tab
	li $v0,4
	syscall

	add $a0, $v1, $0
	li $v0,1
	syscall

	addi $a0,$0,1500
	li $v0,32
	syscall
	j MENU
	
EXIT:
	addi $a0,$0,1500
	li $v0,32
	syscall
	
	li $v0,10 
	syscall


#############################################################
#	char* input(char*)
#input: $a0 address
#output: $v0 DD/MM/YYYY

input:
	.data
	Nhaplai : .asciiz "Nhap sai vui long nhap lai!\n"
	NhapNgay : .asciiz "\nNhap ngay (DAY): "
	NhapThang : .asciiz "Nhap thang (MONTH): "
	NhapNam : .asciiz "Nhap nam (YEAR): "
	temp : .space 40
	.text
	addi $sp, $sp, -44
	sw $t5, 40($sp)
	sw $t4, 36($sp)
	sw $t3, 32($sp)
	sw $t2, 28($sp)
	sw $t1, 24($sp)
	sw $t0, 20($sp)
	sw $a3, 16($sp)
	sw $a0, 12($sp)
	sw $a1, 8($sp)
	sw $a2, 4($sp)
	sw $ra, ($sp)
#Ngay
inputNgay :
	la $a0, NhapNgay
	li $v0, 4
	syscall
	la $a0, temp
	li $a1, 10
	li $v0, 8
	syscall
	add $t2, $a0, $0
forInNgay :
	lb $t0, ($a0)
	add $t3, $0, 10
	beq $t0, $t3, outforInNgay
	slti $t1, $t0, 48
	bne $t1, $0, ErrorInNgay				#if (t0 < 48) != 0 -> false
	slti $t1, $t0, 58
	beq $t1, $0, ErrorInNgay				#if (t0 < 58) == 0 -> false
	addi $a0, $a0, 1
	j forInNgay
ErrorInNgay :
	la $a0, Nhaplai
	li $v0, 4
	syscall
	j inputNgay
outforInNgay :
	add $a0, $t2, $0
	jal atoi
	add $t4, $v0, $0

#Thang
inputThang :
	la $a0, NhapThang
	li $v0, 4
	syscall
	la $a0, temp
	li $a1, 10
	li $v0, 8
	syscall
	add $t2, $a0, $0
forInThang :
	lb $t0, ($a0)
	addi $t3, $0, 10
	beq $t0, $t3, outforInThang
	slti $t1, $t0, 48
	bne $t1, $0, ErrorInThang			#if (t0 < 48) != 0 -> false
	slti $t1, $t0, 58
	beq $t1, $0, ErrorInThang				#if (t0 < 58) == 0 -> false
	addi $a0, $a0, 1
	j forInThang
ErrorInThang :
	la $a0, Nhaplai
	li $v0, 4
	syscall
	j inputThang
outforInThang :
	add $a0, $t2, $0
	jal atoi
	add $t5, $v0, $0
#Nam
inputNam :
	la $a0, NhapNam
	li $v0, 4
	syscall
	la $a0, temp
	li $a1, 10
	li $v0, 8
	syscall
	add $t2, $a0, $0
forInNam :
	lb $t0, ($a0)
	addi $t3, $0, 10
	beq $t0, $t3, outforInNam
	slti $t1, $t0, 48
	bne $t1, $0, ErrorInNam				#if (t0 < 48) != 0 -> false
	slti $t1, $t0, 58
	beq $t1, $0, ErrorInNam				#if (t0 < 58) == 0 -> false
	addi $a0, $a0, 1
	j forInNam
ErrorInNam :
	la $a0, Nhaplai
	li $v0, 4
	syscall
	j inputNam

outforInNam :
	add $a0, $t2, $0
	jal atoi

	.data 
	string: .space 20
	.text 
	lw $a3, 12($sp)
	add $a0, $t4, $0
	add $a1, $t5, $0
	add $a2, $v0, $0

	jal CheckDate

	beq $v0, $0, ErrorInNgay

	jal Date
	
	lw $ra, ($sp)
	lw $a2, 4($sp)
	lw $a1, 8($sp)
	lw $a0, 12($sp)
	lw $t0, 20($sp)
	lw $t1, 24($sp)
	lw $t2, 28($sp)
	lw $t3, 32($sp)
	lw $t4, 36($sp)
	lw $t5, 40($sp)
	addi $sp, $sp, 44

	jr $ra

#############################################################
#	int int TwoNextLeapYear(char*)
#input: $a0 DD/MM/YYYY
#output: $v0 $v1 two next leapyear

TwoNextLeapYear:
	addi $sp,$sp,-24
	sw $a3,20($sp)
	sw $a2,16($sp)
	sw $a1,12($sp)
	sw $a0, 8($sp)					#store
	sw $ra, 4($sp)
	sw $t0,	0($sp)
.data 
	tempyear: .space 40
.text 
	jal Year
	addi $a2, $v0,1
	addi $a0,$0,1
	addi $a1,$0,1
	la $a3,tempyear
	
forTNLY:
	jal Date
	add $a0,$v0,$0
	jal LeapYear
	bne $v0,$0,outforTNLY
	addi $a2,$a2,1
	addi $a0,$0,1
	j forTNLY

outforTNLY:
	add $t0,$a2,$0
	addi $a2,$a2,4
	jal Date
	add $a0,$v0,$0
	jal LeapYear
	bne $v0,$0, exitTNLY
	addi $a2,$a2,4
exitTNLY:
	add $v0,$t0,$0
	add $v1,$a2,$0

	lw $t0, 0($sp)					#restore
	lw $ra, 4($sp)	
	lw $a0, 8($sp)
	lw $a1,12($sp)
	lw $a2,16($sp)
	lw $a3,20($sp)
	addi $sp,$sp,24
	
	jr $ra

#############################################################
#	char*  Convert(char*,char)
#input: $a0 DD/MM/YYYY $a1 A, B, C
#output: MM/DD/YYYY if A
#	Month DD, YYYY if B
#	DD Month, YYYY if C

Convert:
	addi $sp,$sp,-24
	sw $t3, 20($sp)
	sw $a0, 16($sp)
	sw $t2, 12($sp)					#store
	sw $ra, 8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)

	addi $t0,$0,65
	beq $a1,$t0,A
	
	addi $t0,$0,66
	beq $a1,$t0,B

	addi $t0,$0,67
	beq $a1,$t0,C
A:
	.data 
	ADATE:	.space  30
	.text
	la $v0,ADATE
 
	lb $t1,3($a0)
	sb $t1, ($v0)

	lb $t1,4($a0)
	sb $t1,1($v0)

	lb $t1,2($a0)
	sb $t1,2($v0)

	lb $t1,0($a0)
	sb $t1,3($v0)

	lb $t1,1($a0)
	sb $t1,4($v0)

	lb $t1,5($a0)
	sb $t1,5($v0)

	add $t2,$v0,$0
	addi $a0,$a0,6
	addi $v0,$v0,6
	
	j getYear
# **************************
B:
	jal Month
	add $a0,$v0,$0

	.data 
	BDATE:	.space  30
	.text

	jal TextMonth
	add $t3,$v0,$0
	
	la $v0,BDATE
	add $t2,$v0,$0
	
forB:	lb $t0, ($t3)
	beq $t0, $0, outforB
	sb $t0, ($v0)
	addi $v0,$v0,1
	addi $t3,$t3,1
	j forB

outforB:
	lw $a0, 16($sp)
	addi $t1,$0,32
	sb $t1,($v0)

	addi $v0,$v0,1
	lb $t1,($a0)
	sb $t1,($v0)

	addi $v0,$v0,1
	lb $t1,1($a0)
	sb $t1,($v0)
	
	addi $v0,$v0,1
	addi $t1,$0,44
	sb $t1,($v0)

	addi $v0,$v0,1
	addi $t1,$0,32
	sb $t1,($v0)
	
	addi $v0,$v0,1
	addi $a0,$a0,6

	j getYear

#********************************

C:
	jal Month
	add $a0,$v0,$0

	jal TextMonth
	add $t0,$v0,$0
	lw $a0, 16($sp)
	
	.data 
	CDATE:	.space  30
	.text
	la $v0,CDATE
	add $t2,$v0,$0
 
	lb $t1,3($a0)
	sb $t1, ($v0)

	lb $t1,4($a0)
	sb $t1,1($v0)

	addi $t1,$0,32
	sb $t1,2($v0)
	
	addi $v0,$v0,3
forC:
	lb $t1,($t0)
	beq $t1,$0,outforC
	sb $t1,($v0)
	addi $v0,$v0,1
	addi $t0,$t0,1
	j forC
outforC:
	addi $t1, $0, 44
	sb $t1,($v0)
	addi $v0,$v0,1
	addi $t1, $0, 32
	sb $t1,($v0)
	addi $v0,$v0,1
	addi $a0,$a0,6
getYear:
	lb $t1,($a0)
	beq $t1,$0,exit
	sb $t1,($v0)
	addi $a0,$a0,1
	addi $v0,$v0,1
	j getYear

exit:
	lb $0,($v0)
	add $v0, $t2 $0

	lw $t1,0($sp)					#restore
	lw $t0,4($sp)
	lw $ra,8($sp)
	lw $t2, 12($sp)	
	lw $a0, 16($sp)
	lw $t3, 20($sp)
	addi $sp,$sp,24
	
	jr $ra


#############################################################
#	int CheckDate(int,int,int)
#input: $a0 day. $a1 month. $a2 year
#output: 1 if valid date else 0

CheckDate:
	addi $sp,$sp,-16
	sw $a0, 12($sp)					#store
	sw $ra, 8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)

	slt $t0,$0,$a0
	beq $t0,$0,falseDate				# if (0 < day) == 0 -> false

	slt $t0,$0,$a1
	beq $t0,$0,falseDate				# if (0 < month) == 0 -> false

	slti $t0,$a1,13
	beq $t0,$0,falseDate				# if (month < 13) == 0 -> false

	add $t1,$a0,$0					# t1 = day
	add $a0,$0,$a2					# a0 = a3 (month)
	jal DayOfMonth
	slt $t0,$v0,$t1
	bne $t0,$0,falseDate				# if (DOM < day) != 0 -> false

	addi $v0,$0,1
	j end_check

falseDate:
	addi $v0,$0,0

end_check:
	lw $t1,0($sp)					#restore
	lw $t0,4($sp)
	lw $ra,8($sp)
	lw $a0, 12($sp)	
	addi $sp,$sp,16
	
	jr $ra
	

#############################################################
#	int DayOfMouth(int,int)
#input: $a0 YYYY $a1 MM
#output: $v0 count day of month

DayOfMonth:
	addi $sp,$sp,-8
	sw $ra,4($sp)
	sw $t0,	($sp)

	addi $t0,$0,1
	beq $a1,$t0, Day31

	addi $t0,$0,2
	beq $a1,$t0, Orther

	addi $t0,$0,3
	beq $a1,$t0, Day31

	addi $t0,$0,4
	beq $a1,$t0, Day30

	addi $t0,$0,5
	beq $a1,$t0, Day31

	addi $t0,$0,6
	beq $a1,$t0, Day30

	addi $t0,$0,7
	beq $a1,$t0, Day31

	addi $t0,$0,8
	beq $a1,$t0, Day31

	addi $t0,$0,9
	beq $a1,$t0, Day30

	addi $t0,$0,10
	beq $a1,$t0, Day31

	addi $t0,$0,11
	beq $a1,$t0, Day30

	addi $t0,$0,12
	beq $a1,$t0, Day31

Day31:
	addi $v0,$0,31
	j end_DOM
Day30:
	addi $v0,$0,30
	j end_DOM

Orther:
	jal isLeap
	addi $v0,$v0,28

end_DOM:
	lw $t0,($sp)
	lw $ra,4($sp)
	addi $sp,$sp,8

	jr $ra

#############################################################
#	char* TextMonth(int)
#input:$a0 num from 1 to 12
#output: $v0 English of this mouth

TextMonth:
	addi $sp,$sp,-4
	sw $t0,	($sp)
	
	addi $t0,$0,1
	beq $a0,$t0,M1

	addi $t0,$t0,1
	beq $a0,$t0,M2

	addi $t0,$t0,1
	beq $a0,$t0,M3

	addi $t0,$t0,1
	beq $a0,$t0,M4

	addi $t0,$t0,1
	beq $a0,$t0,M5

	addi $t0,$t0,1
	beq $a0,$t0,M6

	addi $t0,$t0,1
	beq $a0,$t0,M7

	addi $t0,$t0,1
	beq $a0,$t0,M8

	addi $t0,$t0,1
	beq $a0,$t0,M9

	addi $t0,$t0,1
	beq $a0,$t0,M10

	addi $t0,$t0,1
	beq $a0,$t0,M11

	addi $t0,$t0,1
	beq $a0,$t0,M12

M1:
	.data 
	Jan: .asciiz "Jannuary"
	.text 
	la $v0,Jan
	j TextMonth_exit

M2:
	.data 
	Feb: .asciiz "February"
	.text 
	la $v0,Feb
	j TextMonth_exit

M3:
	.data 
	Mar: .asciiz "March"
	.text 
	la $v0,Mar
	j TextMonth_exit

M4:
	.data 
	Apr: .asciiz "April"
	.text 
	la $v0,Apr
	j TextMonth_exit

M5:
	.data 
	May: .asciiz "May"
	.text 
	la $v0,May
	j TextMonth_exit

M6:
	.data 
	Jun: .asciiz "June"
	.text 
	la $v0,Jun
	j TextMonth_exit

M7:
	.data 
	Jul: .asciiz "July"
	.text 
	la $v0,Jul
	j TextMonth_exit

M8:
	.data 
	Aug: .asciiz "August"
	.text 
	la $v0,Aug
	j TextMonth_exit

M9:
	.data 
	Sep: .asciiz "September"
	.text 
	la $v0,Sep
	j TextMonth_exit

M10:
	.data 
	Oct: .asciiz "October"
	.text 
	la $v0,Oct
	j TextMonth_exit

M11:
	.data 
	Nov: .asciiz "November"
	.text 
	la $v0,Oct
	j TextMonth_exit

M12:
	.data 
	Dec: .asciiz "December"
	.text 
	la $v0,Oct

TextMonth_exit:

	lw $t0,	($sp)
	addi $sp,$sp,4
	
	jr $ra

#############################################################
#	char* Date(int,int,int,char*)
#input: $a0 day, $a1 month, $a2 year, $a3 address
#output: $v0 DD/MM/YYYY or "\0" if not is date
Date:
	addi $sp,$sp,-24
	sw $a1, 20($sp)
	sw $a0, 16($sp)		#store
	sw $t2, 12($sp)
	sw $ra, 8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)

	addi $t0,$0,10
	addi $t2,$0,47

	div $a0,$t0
	mflo $t1
	addi $t1,$t1,48
	sb $t1,($a3)
	mfhi $t1
	addi $t1,$t1,48
	sb $t1,1($a3)
	sb $t2,2($a3)

	div $a1,$t0
	mflo $t1
	addi $t1,$t1,48
	sb $t1,3($a3)
	mfhi $t1
	addi $t1,$t1,48
	sb $t1,4($a3)
	sb $t2,5($a3)

	add $t0,$a3,$0
	addi $a3,$a3,6

	.data
	Temp: .space 10
	.text 
	la $a0,Temp
	add $a1,$0,$a2

	jal itoa
forDate:
	lb $t1,($v0)
	beq $t1,$0,outfor
	sb $t1,($a3)
	addi $v0,$v0,1
	addi $a3,$a3,1
	j forDate
outfor:	
	sb $0, ($a3)
	add $v0,$t0,$0

exit_Date:
	lw $t1,0($sp)				#restore
	lw $t0,4($sp)
	lw $ra,8($sp)
	lw $t2,12($sp)
	lw $a0, 16($sp)
	lw $a1, 20($sp)	
	addi $sp,$sp,24
	
	jr $ra

#############################################################
#	char* Weekday(char*)
# input: $a0 DD/MM/YYYY
# output: $v0 day of week
Weekday:
	addi $sp,$sp,-20		#store
	sw $t3, 16($sp)
	sw $t2, 12($sp)
	sw $ra, 8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)

	jal Day
	add $t0,$v0,$0			#t0 = get_day

	jal Month
	add $t1,$v0,$0			#t1 = get_mounth

	jal Year
	add $t2,$v0,$0			#t2 = get_year

	slti $t3,$t1,3
	beq $t3,$0,LoopWeek		# if (t1<3)
	addi $t1,$t1,12			# t1+=12
	addi $t2,$t2,-1			# t2--

LoopWeek:
	add $t0,$t0,$t1
	add $t0,$t0,$t1			# t0 = 2*t1 + t0
	
	addi $t1,$t1,1
	add $t3,$0,$t1
	add $t3,$t3,$t1
	add $t3,$t3,$t1			# t3 = 3*t1 + 3

	addi $t1,$0,5
	div $t3,$t1
	mflo $t3			# t3 = t3 / 5

	add $t0,$t0,$t3			# t0 = t0 + t3
	add $t0,$t0,$t2			# t0 = t0 + t2

	addi $t1,$0,4
	div $t2,$t1
	mflo $t2 			# t2 = t2 / 4

	add $t0,$t0,$t2			# t0 = t0 + t2


# t0 = ( t0 + 2*t1 + (3*t1 + 3)/5 + t2 + t2/4)

	addi $t1,$0,7
	div $t0,$t1
	mfhi $t0			# t0 = t0 % 7
	
	addi $t1,$0,0			#case switch
	beq $t0,$t1, mod0

	addi $t1,$t1,1
	beq $t0,$t1, mod1

	addi $t1,$t1,1
	beq $t0,$t1, mod2

	addi $t1,$t1,1
	beq $t0,$t1, mod3
	
	addi $t1,$t1,1
	beq $t0,$t1, mod4

	addi $t1,$t1,1
	beq $t0,$t1, mod5

	addi $t1,$t1,1
	beq $t0,$t1, mod6

mod0:
	.data 
	sunday: .asciiz "Sunday"
	.text  
	la $v0,sunday
	j end_Weekday

mod2:
	.data 
	tuesday: .asciiz "Tuesday"
	.text  
	la $v0,tuesday
	j end_Weekday

mod3:
	.data 
	wednesday: .asciiz "Wednesday"
	.text  
	la $v0,wednesday
	j end_Weekday

mod1:
	.data 
	monday: .asciiz "Monday"
	.text  
	la $v0,monday
	j end_Weekday

mod4:
	.data 
	thursday: .asciiz "Thursday"
	.text  
	la $v0,thursday
	j end_Weekday

mod5:
	.data 
	friday: .asciiz "Friday"
	.text  
	la $v0,friday
	j end_Weekday

mod6:
	.data 
	saturday: .asciiz "Saturday"
	.text  
	la $v0,saturday
	
end_Weekday:
	lw $t1,0($sp)				#restore
	lw $t0,4($sp)
	lw $ra,8($sp)
	lw $t2,12($sp)
	lw $t3,16($sp)
	addi $sp,$sp,20
	
	jr $ra
#############################################################
#	int isLeap(int)
#input: YYYY
#output: 1 if leapyear else 0
isLeap:
	addi $sp,$sp,-12
	sw $a0,8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)
	
	addi $t0,$0,400
	div $a0,$t0
	mfhi $t1
	beq $t1,$0,true

	addi $t0,$0,4
	div $a0,$t0
	mfhi $t1
	bne $t1,$0,false

	addi $t0,$0,100
	div $a0,$t0
	mfhi $t1
	beq $t1,$0,false
true:
	addi $v0,$0,1
	j end_isLeap
false:
	addi $v0,$0,0

end_isLeap:
	lw $t1,0($sp)
	lw $t0,4($sp)
	lw $a0,8($sp)
	addi $sp,$sp,12

	jr $ra
########################################################
#	int 	LeapYear(char*)
#input: DD/MM/YYYY
#output: 1 if leapyear else 0
LeapYear:
	addi $sp,$sp,-8
	sw $ra, 4($sp)
	sw $a0, 0($sp)

	jal Year
	add $a0,$v0,$0
	
	jal isLeap

	lw $ra,4($sp)
	lw $a0,($sp)
	addi $sp,$sp,8
	jr $ra
#############################################################
#	int GetTime(char*,char*)
#input: DD/MM/YYYY dd/mm/yyyy
#output: abs(YYYY-yyyy)
GetTime:
	addi $sp,$sp,-16
	sw $a0, 12($sp)
	sw $ra, 8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)	

	jal Year

	add $t0,$v0,$0	
	add $a0,$a1,$0

	jal Year
	
	slt $t1,$t0,$v0
	beq $t1,$0,if_GetTime
	sub $v0,$v0,$t0

	j end_GetTime	
if_GetTime:
	sub $v0,$t0,$v0

end_GetTime:
	lw $t1,0($sp)
	lw $t0,4($sp)
	lw $ra,8($sp)
	lw $a0,12($sp)

	addi $sp,$sp,16

	jr $ra
#############################################################
#	int Day(char*)
#input: DD/MM/YYYY
#output: DD
Day:
	.data 
	day: .space 10	
	.text 
	addi $sp,$sp,-16
	sw $a0, 12($sp)
	sw $ra, 8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)

	add $t0, $a0,$0

	la $v0,day

	lb $t1,($t0)
	sb $t1,($v0)

	lb $t1,1($t0)
	sb $t1,1($v0)

	add $a0,$v0,$0

	jal atoi

	lw $t1,0($sp)
	lw $t0,4($sp)
	lw $ra,8($sp)
	lw $a0,12($sp)
	addi $sp,$sp,16
	jr $ra
#################################################################
#	int Month(char*)
#input: DD/MM/YYYY
#output: MM
Month:
	.data 
	month: .space 10	
	.text 
	addi $sp,$sp,-16                      
	sw $a0, 12($sp)
	sw $ra, 8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)

	add $t0, $a0,$0

	la $v0,month

	lb $t1,3($t0)
	sb $t1,($v0)

	lb $t1,4($t0)
	sb $t1,1($v0)

	add $a0,$v0,$0

	jal atoi

	lw $t1,0($sp)                            
	lw $t0,4($sp)
	lw $ra,8($sp)
	lw $a0,12($sp)
	addi $sp,$sp,16
	jr $ra
####################################################################
#	int Year(char*)
#input: DD/MM/YYYY
#output: YY
Year:
	.data 
	year: .space 10
	
	.text 
	addi $sp,$sp,-24
	sw $t3, 20($sp)
	sw $t2, 16($sp)
	sw $a0, 12($sp)
	sw $ra, 8($sp)
	sw $t0,	4($sp)
	sw $t1, 0($sp)

	add $t2, $a0,$0

	la $a0,year

	add $t0, $a0,$0

	addi $t3,$0,10

	addi $t2, $t2,6
forYEAR:
	lb $t1,($t2)
	beq $t1,$0,outforYEAR
	beq $t1,$t3,outforYEAR
	sb $t1,($a0)
	addi $t2, $t2,1
	addi $a0, $a0,1
	j forYEAR
outforYEAR:
	sb $0,($a0)
	add $a0,$t0,$0	
	jal atoi

	lw $t1,0($sp)
	lw $t0,4($sp)
	lw $ra,8($sp)
	lw $a0,12($sp)
	lw $t2,16($sp)
	lw $t3, 20($sp)
	addi $sp,$sp,24

	jr $ra
#################################################################
#	int atoi(char*)
#input: $a0 chu?i mu?n chuy?n
#output: $v0 giá tr? int c?a chu?i s?
atoi:
	# Backup to stack
	addiu $sp, $sp, -12
	sw $t0, 0($sp)
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	li $v0, 0				# result = 0
	ori $t0, $a0, 0				# it = num
	lb $t1, 0($t0)				# c = *it
atoi_forloop:
	slti $t3, $t1, 48			# if (c < 48)
	bne $t3, $0, atoi_endfunc		#	jump to atoi_error
	slti $t3, $t1, 58			# if (c >= 58)
	beq $t3, $0, atoi_endfunc		#	jump to atoi_error
	addi $t1, $t1, -48
	ori $t3, $0, 10				# temp = 10
	mult $v0, $t3				# result = ...
	mflo $v0				# 	result * temp
	add $v0, $v0, $t1			# result += 1
	addi $t0, $t0, 1			# ++it
	lb $t1, 0($t0)				# c = *it
	j atoi_forloop
atoi_endfunc:
	# Restore the stack
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	addiu $sp, $sp, 12
	# Jump back to where it was called
	jr $ra
################################################################
#	char*	itoa(char*,int)
itoa:
	# Backup to stack
	addi $sp, $sp, -12
	sw $t0, 0($sp)
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	ori $t0, $a0, 0			# it = num
itoa_loop:
	beq $a1, $0, itoa_endloop	# val == 0 => endloop
	ori $t1, $0, 10			#	tmp = 10
	div $a1, $t1			#	lo = val/10, hi = val%10
	mfhi $t1			#	
	addi $t1, $t1, 48		#	tmp = hi+48 = (val%10)+48
	sb $t1, 0($t0)			#	*it = tmp
	mflo $a1			#	val = lo = val/10
	addi $t0, $t0, 1		#	++it
	j itoa_loop
itoa_endloop:
	# Call reverse
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	# reverse still use $a0 as first parameter, so don't need to backup them
	jal reverse
	lw $ra, 0($sp)
	addi $sp, $sp, 4
itoa_endfunc:
	# Restore the stack
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	addi $sp, $sp, 12
	# Jump back where it was called
	jr $ra

reverse:
	# Backup to stack
	addi $sp, $sp, -20
	sw $t0, 0($sp)
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	sw $t3, 12($sp)
	sw $t4, 16($sp)	
	ori $t0, $a0, 0				# it = s
	lb $t2, 0($t0)				# *it
reverse_loop_1:
	beq $t2, $0, reverse_endloop_1		#  (*it == '\0') => endloop
	addi $t0, $t0, 1			# 	++it
	lb $t2, 0($t0)				# 	*it
	j reverse_loop_1
reverse_endloop_1:
	addi $t0, $t0, -1			# --it
	ori $t1, $a0, 0				# jt = s
reverse_loop_2:
	slt $t4, $t1, $t0			# jt >= it => endloop
	beq $t4, $0, reverse_endloop_2		#	
	lb $t2, 0($t0)				# temp1 = *it
	lb $t3, 0($t1)				# temp2 = *jt
	sb $t3, 0($t0)				# *jt = temp1
	sb $t2, 0($t1)				# *it = temp2
	addi $t0, $t0, -1			# --it
	addi $t1, $t1, 1			# ++jt
	j reverse_loop_2
reverse_endloop_2:
reverse_endfunc:
	# Return s
	ori $v0, $a0, 0
	# Restore the stack
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t3, 12($sp)
	lw $t4, 16($sp)
	addi $sp, $sp, 20	
	# Jump back where it was called
	jr $ra
