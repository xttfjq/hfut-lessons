.model small
.stack 100h

.data
    X   dw  5       ; X = 5
    Y   dw  10      ; Y = 10
    Z   dw  500     ; Z = 500
    V   dw  1000    ; V = 1000

.code
main:
    mov ax, @data
    mov ds, ax
    mov ax, X
    imul Y      
    add ax, Z   
    ADC DX, 0
    sub ax, 720   
    SBB DX, 0
    MOV BX,AX
    MOV CX,DX   ;CX.BX=X*Y+Z-720     
    MOV AX,V
    CWD         ;DX.AX=V
    SUB AX,BX
    SBB DX,CX   ;DX.AX=V-X*Y+Z-720   
    IDIV X      ;AX¥Ê…Ã£¨DX¥Ê”‡ ˝     
    
    
    mov ah, 4Ch
    int 21h

end main
