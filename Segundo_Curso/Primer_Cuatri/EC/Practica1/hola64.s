.section .data
msg:    .string "¡hola, mundo!\n"
tam:    .quad . - msg

.section .text

main: .global main
        call  write       # llamada a función
	call write2     # llamada a funcion
	call write3     # llamada a funcion
        call  exit2        # llamada a función
	ret
write:  mov   $1,   %rax  # write
        mov   $1,   %rdi  # stdout
        mov   $msg, %rsi  # texto
        mov   tam,  %rdx  # tamaño
        syscall           # llamada a write
        ret
write2:  mov   $1,   %rax  # write
        mov   $1,   %rdi  # stdout
        mov   $msg, %rsi  # texto
        mov   $5,  %rdx  # tamaño
        syscall           # llamada a write
        ret

write3: mov   $1,   %rax  # write
        mov   $1,   %rdi  # stdout
        mov   $msg,  %rsi   # texto
        mov   tam,  %rdx  # tamaño
	add    $3, %rdx 
        syscall           # llamada a write
        ret

exit2:   mov   $60,  %rax  # exit
        xor   %rdi, %rdi  # 0
        syscall           # llamada a exit
        ret
