data segment
    x dw 5
    y dw 3
    buffer db 6 dup('$')
data ends

code segment
assume cs:code, ds:data
start:
    mov ax, data
    mov ds, ax

    push x
    push y
    call func
    add sp, 4

    ; AX 中为结果，输出十进制
    call print_decimal

    mov ah, 4ch
    int 21h

func proc
    push bp
    mov bp, sp
    mov ax, [bp+6]  ; x
    mov bx, [bp+4]  ; y
    imul bx         ; dx:ax = x*y
    add ax, [bp+6]  ; +x
    sub ax, bx      ; -y
    pop bp
    ret
func endp

print_decimal proc
    ; 输入 AX = 有符号数
    mov bx, 10
    mov cx, 0
    test ax, ax
    jns positive
    neg ax
    push ax
    mov dl, '-'
    mov ah, 2
    int 21h
    pop ax
positive:
    xor dx, dx
    div bx
    push dx
    inc cx
    cmp ax, 0
    jnz positive
print_loop:
    pop dx
    add dl, '0'
    mov ah, 2
    int 21h
    loop print_loop
    ret
print_decimal endp

code ends
end start