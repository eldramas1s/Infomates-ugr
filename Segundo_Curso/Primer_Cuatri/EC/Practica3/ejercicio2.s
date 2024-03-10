#Reprogramar suma.s (Figura 1) conforme a SystemV. Ensamblar, enlazar, depurar, y comprobar que
#sigue calculando el resultado correcto. En la Figura 2 se muestran resaltados los cambios a realizar.
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
	mov $formato, %rdi
	mov resultado, %esi # podría haber sido %eax
	mov resultado, %edx
	mov $0, %eax
	call printf # printf(formato, resultado, resultado);
	
	mov $0, %edi
	call exit # exit(status);

# SUBRUTINA: int suma(int* lista, int longlista);
# entrada: 1) %rbx = dirección inicio array
# 2) %ecx = número de elementos a sumar
# salida: %eax = resultado de la suma

suma:

	# push %rdx 			# preservar %rdx (índice) Segun SystemV no tengo por qué salvarlo puesto que es entrada de argumentos
	mov $0, %eax 			# acumulador
	mov $0, %rdx 			# índice
	
	bucle:
		add (%rdi,%rdx,4), %eax
		inc %edx
		jne bucle
	# pop %rdx 			# restaurar %rdx Como no tengo que salvarlo no tengo que recuperarlo puesto que no estaria en pila y tomaría un valor que no 
					# conozco
	ret

