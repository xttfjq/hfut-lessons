data segment
    msg0 db 'The 0 Bit is 1$'
    msg1 db 'The 1 Bit is 1$'
    msg2 db 'The 2 Bit is 1$'
    msg3 db 'The 3 Bit is 1$'
    msg4 db 'The 4 Bit is 1$'
    msg5 db 'The 5 Bit is 1$'
    msg6 db 'The 6 Bit is 1$'
    msg7 db 'The 7 Bit is 1$'
    jmp_table dw offset m0, offset m1, offset m2, offset m3
              dw offset m4, offset m5, offset m6, offset m7
data ends

code segment
assume cs:code, ds:data
start:
    mov ax, data
    mov ds, ax

    mov bl, 00000100b  ; 测试值：bit 2 为 1，可修改测试其他位

    mov bh, 0
    mov cx, 8
find_bit:
    shr bl, 1
    jc found
    inc bh
    loop find_bit
    jmp exit

found:
    mov al, bh
    mov ah, 0
    shl ax, 1          ; 乘2（因为表项是字）
    mov si, ax
    jmp jmp_table[si]

m0: mov dx, offset msg0
    jmp print
m1: mov dx, offset msg1
    jmp print
m2: mov dx, offset msg2
    jmp print
m3: mov dx, offset msg3
    jmp print
m4: mov dx, offset msg4
    jmp print
m5: mov dx, offset msg5
    jmp print
m6: mov dx, offset msg6
    jmp print
m7: mov dx, offset msg7

print:
    mov ah, 9
    int 21h

exit:
    mov ah, 4ch
    int 21h

code ends
end start