.section .data
lista: .quad 0x00000001,0x00000001,0x00000001,0x00000001,0x00000001,0x00000001,0x00000001,
longlista: .int (.-lista)/8
resultado_m: .quad 0x00000000
resultado_v: .quad 0x00000000
formato_a: .asciz "media = %lu = 0x%x hex\n"
formato_b: .asciz "varianza = %lu = 0x%x hex\n" 

.section .text

main: .global main

	mov $lista, %rdi				# Colocar la lista como primer argumento
	mov $longlista, %rsi				# Colocar la longitud de la lista como segundo argumento
	push %rdx					# salvar rdx por se salva-invocante
	push %rcx					# salvar rcx por se salva-invocante
	call media					# calcular la media
	mov %rax, %rdx					# salvar el resultado de la media
	mov %rdx, resultado_m				# guardar la media en su variable
	call varianza					# calcular la varianza
	mov %rax, resultado_v				# salvar el resultado de calcular la varianza
	pop %rcx					# recuperar rcx de la pila
	pop %rdx					# recuperar rdx de la pila
	call imprimir_printf				# imprimir por pantalla
	ret
	
	media:
		push %rbx	
		call suma 
		mov %rsi, %rbx
		cltd 
		div %rax
		pop %rbx
		ret
	
	
		suma:							
			push %rbx					
			mov $0, %rbx					
			mov $0, %rcx					
			
			bucle:
				add (%rdi,%rcx,8) , %rbx		
				inc %rcx				
				cmp %rcx, %rsi				
				jne bucle				
				
			mov %rbx, %rax					
			pop %rbx						
	ret						
	
	varianza: # (rdi=lista, rsi=longlista, rdx = media)
				
		push %r14							# salvar r14, es salva-invocado
		push %r13							# salvar r13, es salva-invocado
		push %r12							# salvar r12, es salva-invocado
		mov $0, %r12							# poner a 0 el acumulador de denominador
		mov $0, %r13							# poner a 0 el contador
		sumandos: #( r12=numerador, r13=contador, r14=media_copia)	# bucle de obtencion del numerador
			mov %rdx, %r14						# hacemos copia de la media por cada iteracion
			sub (%rdi,%rcx,8) , %r14				# restamos cada posicion del array con la media
			imulq %r14, %r14					# multipilamos el resultado anterior por sí mismo para obtener el cuadrado
			add %r14, %r12						# hacemos la sumatoria sobre r12
			inc %r13						# incrementamos el contador
			cmp %rsi, %r13						# comparamos si es la longitud
			jne sumandos						# si no lo es, repetimos la iteracion
		mov %r12,%rax							# colocamos los registros para dividir sin signo por pereza
		cltd								# ampliamos a rdx (perdemos el valor de la media)
		push %rbx							# salvamos rbx, es salva-invocado
		mov %rsi, %rbx							# colocamos el divisor
		div %rax							# realizamos la divisionguardando el resultado sobre rax
		pop %rbx							# recuperamos rbx
		pop %r12							# recuperamos r12
		pop %r13							# recuperamos r13
		pop %r14							# resuperamos r14
	ret
	
	imprimir_printf:#formato dato dato
		ret

			
