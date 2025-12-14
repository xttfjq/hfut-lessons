assume cs:code,ds:data
data segment
oldisr dw ?,?
timer db 0
count db 0
new db 0dh,0ah,"$"
data ends
code segment
start:mov ax,data
    mov ds,ax
    mov ax,0
    mov es,ax
    mov ax,es:[1ch*4]
    mov oldisr[0],ax
    mov ax,es:[1ch*4+2]
    mov oldisr[2],ax    ;保存原中断
    mov word ptr es:[1ch*4],offset isr
    mov word ptr es:[1ch*4+2],seg isr     ;设置新中断
again:cmp timer, 89
    ja exit
    jmp again
exit:mov ax,oldisr[0]
    mov es:[1ch*4],ax
    mov ax,oldisr[2]
    mov es:[1ch*4+2],ax
    mov ah,4ch
    int 21h
isr proc far
    push ax
    push bx
    push cx
    push dx
    sti
    inc count
    cmp count,1000/55
    jb s
    inc timer   
    mov count,0
    mov al,timer
    mov ah,0
    mov bh,10
    div bh
    mov dh,ah
    mov dl,al
    add dl,30h
    mov ah,2
    int 21h
    mov dl,dh
    add dl,30h
    mov ah,2
    int 21h
    lea dx,new
    mov ah,9
    int 21h
s:pushf
    call dword ptr oldisr
    pop dx
    pop cx
    pop bx
    pop ax  
    iret

isr endp
code ends
end start
