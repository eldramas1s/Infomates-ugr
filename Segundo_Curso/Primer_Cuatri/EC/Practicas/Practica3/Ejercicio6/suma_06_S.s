.section .text
suma: .global suma
	mov $0, %eax
	mov $0, %edx			# poner a 0 para guardar el elemento
	mov $0, %r8			# poner a 0 acumulador
	mov $0, %r10d			# poner a 0 para guardar el resultado
	mov $0, %r9d 			# poner a 0 para guardar el acarreo
	

bucle:
	mov (%rdi,%r8,4), %eax		# mover el elemento i-ésimo de la lista al registro eax.
	cltd				# extender signo a edx(convert long to double)					
	add (%rdi,%r8,4), %r10d  	# acumular i-ésimo elemento
	adc %edx, %r9d			# sumar acarreo 
	inc %r8				# incrementar indice
	cmp %r8, %rsi 			# ver si hemos llegado al final
	jne bucle
	mov %r10d, %eax			# mover resultado a eax
	mov %r9d, %edx			# mover acarreo	
	cltd
ret

