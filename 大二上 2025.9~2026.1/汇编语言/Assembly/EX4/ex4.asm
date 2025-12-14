data segment
    prompt db 'Input string: $'
    yes_msg db 0dh, 0ah, 'Yes$'    
    no_msg db 0dh, 0ah, 'No$'      
    buffer db 50, 0, 50 dup('$')
data ends

code segment
assume cs:code, ds:data
start:
    mov ax, data
    mov ds, ax

    ; 显示提示
    mov dx, offset prompt
    mov ah, 9
    int 21h

    ; 读字符串
    mov dx, offset buffer
    mov ah, 0ah
    int 21h

    ; 查找子串
    mov si, offset buffer+2
search:
    mov al, [si]
    cmp al, 0dh        ; 遇到回车结束
    je not_found
    cmp al, 'a'
    jne next_char
    mov al, [si+1]
    cmp al, 's'
    jne next_char
    mov al, [si+2]
    cmp al, 'm'
    je found
next_char:
    inc si
    jmp search

found:
    mov dx, offset yes_msg
    jmp output

not_found:
    mov dx, offset no_msg

output:
    mov ah, 9
    int 21h

    ; 再输出一个换行使光标到下一行
    mov dl, 0dh
    mov ah, 2
    int 21h
    mov dl, 0ah
    mov ah, 2
    int 21h

    mov ah, 4ch
    int 21h

code ends
end start