# suma.s: 	Sumar los elementos de una lista
# 		llamando a función, pasando argumentos mediante registros
# 		comprobar con "./suma; echo $?" o con depurador gdb/ddd

# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
lista: 		.int 0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF			# ejs. binario 0b / hex 0x,-
longlista: 	.int (.-lista)/4 		# . = contador posiciones. Aritm.etiq.
resultado: 	.quad 0

formato: .asciz "media = %ld = 0x%lx hex\n" 	# fmt para printf() libC

# el string "formato" sirve como argumento a la llamada printf opcional
# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as suma.s -o suma.o
# 	ld suma.o -o suma 		1232 B
# 2) as suma.s -o suma.o 		6520 B
# 	ld suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma –no-pie –nostartfiles 6544 B
# 4) gcc suma.s -o suma –no-pie 	8664 B

# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text 				# PROGRAMA PRINCIPAL
#_start: .global _start 		# se puede abreviar de esta forma
main: .global main

	call trabajar 			# subrutina de usuario
	call imprim_C 			# printf() de libC
	# call acabar_L 		# exit() del kernel Linux
	call acabar_C 			# exit() de libC
	ret

trabajar:
	mov $lista, %rbx 		# dirección del array lista
	mov longlista, %ecx 		# número de elementos a sumar
	call suma 			# llamar suma(&lista, longlista);
	mov %eax, resultado 		# salvar resultado
	mov %edx, resultado+4		# salvar acarreo
	ret
	
# SUBRUTINA: 	int suma(int* lista, int longlista);
# entrada: 	1) %rbx = dirección inicio array
# 		2) %ecx = número de elementos a sumar
# salida: 	   %eax = resultado de la suma

suma:
	mov $0, %edx			# poner a 0 para guardar el acarreo
	mov $0, %eax 			# poner a 0 para guardar el elemento
	mov $0, %r8			# poner a 0 acumulador
	mov $0, %r10d			# poner a 0 para guardar el resultado
	mov $0, %r9d 			# poner a 0 para guardar el acarreo
	

bucle:
	mov (%rbx,%r8,4), %eax		# mover el elemento i-ésimo de la lista al registro eax.
	cltd				# extender signo a edx(convert long to double)					
	add (%rbx,%r8,4), %r10d  	# acumular i-ésimo elemento
	adc %edx, %r9d			# sumar acarreo 
	inc %r8				# incrementar indice
	cmp %r8, %rcx 			# ver si hemos llegado al final
	jne bucle
	mov %r10d, %eax			# mover resultado a eax
	mov %r9d, %edx			# mover acarreo
	idiv %ecx	
	cltd
ret
	
imprim_C:
	#si se usa esta subrutina, usar también la línea que define formato
	#se puede linkar con ld –lc –dyn ó gcc –nostartfiles, o usar main
	mov $formato , %rdi 		# traduce resultado a decimal/hex
	mov resultado, %rsi 		# versión libC de syscall __NR_write
	mov resultado, %rdx 		# ventaja: printf() con fmt "%u" / "%x"
	call printf 			# == printf(formato,resultado,resultado)
	ret
	
#acabar_L: # void _exit(int status);
#	mov $60, %rax 			# exit: servicio 60 kernel Linux
#	mov resultado, %edi 		# status: código a retornar (la suma)
#	syscall 			# == _exit(resultado);
#	ret
	
acabar_C: # void exit(int status);
	mov resultado, %edi 		# status: código a retornar (la suma)
	call exit 			# == exit(resultado)
	ret

