.section .data
lista:		.int 1,2,10, 1,2,0b10, 1,2,0x10
longlista: 	.int (.-lista)/4
resultado: .int 0

.section .text
_start: .global _start
#main: .global main

	call trabajar
	#call imprimir_C
	call acabar_L
	#call acabar_C
	ret

trabajar:
	mov $lista, %rbx
	mov $longlista, %ecx
	call suma
	mov %eax, resultado
	ret
	
suma:
	push %rdx
	mov $0, %eax
	mov $0, %rdx
bucle:
	add (%rbx,%rdx,4), %eax
	inc %rdx
	cmp %rdx, %rcx
	jl bucle
	
#	imulq $(1/%rcx),%eax
	pop %rdx
	ret
#imprimir_C:
#	mov $formato, %rdi
#	mov resultado, %esi
#	mov resultado, %edx
#	mov $0, %eax
#	call printf
#	ret 

acabar_L:
	mov $60, %rax 
	mov resultado, %edi
	syscall
	ret

#acabar_C:
#	mov resultado,%edi
#	call exit
#	ret	
	 
	
	
