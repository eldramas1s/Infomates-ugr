# suma.s anterior, simplificada: 1 solo call, exit del kernel, no libC
# retorna: código retorno 0, comprobar suma en %eax mediante gdb/ddd
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
	lista: .int 1,2,10, 1,2,0b10, 1,2,0x10
	longlista: .int (.-lista)/4
	resultado: .int 0
	formato: .asciz "resultado = %d = 0x%x hex\n" 	# fmt para printf() libC
	
.global lista, longlista, resultado, formato

.section .text
main: .global main
	jmp suma
