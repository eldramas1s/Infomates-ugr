# Modularizar sumar
# suma.s anterior, simplificada: 1 solo call, exit del kernel, no libC
# retorna: código retorno 0, comprobar suma en %eax mediante gdb/ddd
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
	lista: .int 1,2,10, 1,2,0b10, 1,2,0x10
	longlista: .int (.-lista)/4
	resultado: .int 0
	formato: .asciz "resultado = %d = 0x%x hex\n" 	# fmt para printf() libC
	
# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)

.section .text

_start: .global _start # PROGRAMA PRINCIPAL

	mov $lista, %rdi
	mov longlista, %esi
	call suma
	mov %eax, resultado # res = suma(&lista, longlista);	
	call imprim_C
	mov $0, %edi
	ret

# SUBRUTINA: int suma(int* lista, int longlista);
# entrada: 1) %rbx = dirección inicio array
# 2) %ecx = número de elementos a sumar
# salida: %eax = resultado de la suma

imprim_C:

	# si se usa esta subrutina, usar también la línea que define formato
	# se puede linkar con ld –lc –dyn ó gcc –nostartfiles, o usar main
	mov $formato , %rdi 		# traduce resultado a decimal/hex
	mov resultado, %rsi 		# versión libC de syscall __NR_write
	mov resultado, %rdx 		# ventaja: printf() con fmt "%u" / "%x"
	mov $0, %eax 			# varargin sin xmm
	call printf 			# == printf(formato,resultado,resultado)
	ret
