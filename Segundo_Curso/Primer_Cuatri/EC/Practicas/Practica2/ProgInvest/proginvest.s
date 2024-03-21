# progivest.s: Sumar una serie de numeros que se pasan como argumentos, en este caso los 
#	       numeros vas a ser introducidos a mano en el codigo ensamblador
#
# retorna: 1.Valor de la suma que se obtiene.
#	   2. COmprobaciones varias

.section .data 

saludo: 
	.ascii "Hello World!\nYou all are motherfuckers!\n"

longsaludo: 
	.quad .-saludo
	
.section .text
.global _start #si pongo esto debo ensamblar y enlazar con as y ld

_start:
	mov $1, %rax 
	mov $1, %rdi
	mov $saludo, %rsi
	mov $longsaludo, %rdx
	syscall
	
	mov $60,%rax
	mov $60,%rdi
	syscall
