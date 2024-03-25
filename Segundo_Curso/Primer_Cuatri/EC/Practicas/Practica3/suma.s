# suma.s anterior, simplificada: 1 solo call, exit del kernel, no libC
# retorna: código retorno 0, comprobar suma en %eax mediante gdb/ddd
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
	lista: .int 1,2,10, 1,2,0b10, 1,2,0x10
	longlista: .int (.-lista)/4
	resultado: .int 0
# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text
_start: .global _start # PROGRAMA PRINCIPAL
	mov $lista, %rbx
	mov longlista, %ecx
	call suma
	mov %eax, resultado # res = suma(&lista, longlista);
	mov $60, %rax
	mov $0, %edi
	syscall # _exit(int status);

# SUBRUTINA: int suma(int* lista, int longlista);
# entrada: 1) %rbx = dirección inicio array
# 2) %ecx = número de elementos a sumar
# salida: %eax = resultado de la suma
suma:
	push %rdx # preservar %rdx (índice)
	mov $0, %eax # acumulador
	mov $0, %rdx # índice
	
	bucle:
		add (%rbx,%rdx,4), %eax
		inc %edx
		cmp %edx,%ecx
		jne bucle
	pop %rdx # restaurar %rdx
ret
