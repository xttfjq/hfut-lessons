DATA SEGMENT
    SCORES DB 85, 92, 78, 64, 88, 95, 72, 81, 90, 67
           DB 83, 79, 91, 86, 74, 89, 76, 82, 94, 68
           DB 87, 93, 77, 84, 71, 96, 69, 80, 75, 98
           DB 65, 73, 97, 70, 99, 66, 99, 63, 89, 82
           DB 78, 91, 84, 76, 87, 92, 79, 84, 90, 73   ; 50个成绩
    
    COUNT DB 50         ; 学生人数
    MAX DB ?           ; 最大值
    MIN DB ?           ; 最小值  
    AVERAGE DB ?       ; 平均值
    
    MSG_MAX DB 'Max: $'
    MSG_MIN DB 'Min: $'
    MSG_AVG DB 'Average: $'
    NEWLINE DB 0DH, 0AH, '$'  ; 换行
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX
    
    ; 初始化
    MOV SI, OFFSET SCORES  ; SI指向成绩数组
    MOV CL, COUNT          ; 循环计数器
    MOV AL, [SI]           ; 初始化最大值和最小值为第一个成绩
    MOV MAX, AL
    MOV MIN, AL
    XOR AX, AX             ; 清空AX用于累加和
    XOR BX, BX             ; 清空BX
    
CALC_LOOP:
    MOV BL, [SI]           ; 读取当前成绩
    
    ; 累加总分
    ADD AL, BL
    ADC AH, 0              ; 处理进位
    
    ; 比较最大值
    CMP BL, MAX
    JLE CHECK_MIN
    MOV MAX, BL
    
CHECK_MIN:
    ; 比较最小值  
    CMP BL, MIN
    JGE NEXT_SCORE
    MOV MIN, BL
    
NEXT_SCORE:
    INC SI                 ; 指向下一个成绩
    DEC CL                 ; 计数器减1
    JNZ CALC_LOOP          ; 继续循环
    
    ; 计算平均值
    MOV BL, COUNT
    DIV BL                 ; AX / BL，商在AL，余数在AH
    MOV AVERAGE, AL
    
    ; 显示结果
    CALL DISPLAY_RESULTS
    
    ; 退出程序
    MOV AH, 4CH
    INT 21H

; 显示结果的子程序
DISPLAY_RESULTS PROC
    ; 显示最大值
    MOV AH, 09H
    LEA DX, MSG_MAX
    INT 21H
    
    MOV AL, MAX
    CALL DISPLAY_NUMBER
    CALL NEW_LINE
    
    ; 显示最小值
    MOV AH, 09H
    LEA DX, MSG_MIN
    INT 21H
    
    MOV AL, MIN
    CALL DISPLAY_NUMBER
    CALL NEW_LINE
    
    ; 显示平均值
    MOV AH, 09H
    LEA DX, MSG_AVG
    INT 21H
    
    MOV AL, AVERAGE
    CALL DISPLAY_NUMBER
    CALL NEW_LINE
    
    RET
DISPLAY_RESULTS ENDP

; 显示两位数字的子程序
DISPLAY_NUMBER PROC
    MOV AH, 0
    MOV BL, 10
    DIV BL          ; AL = 十位, AH = 个位
    
    MOV BL, AH      ; 保存个位
    
    ; 显示十位
    MOV DL, AL
    ADD DL, '0'
    MOV AH, 02H
    INT 21H
    
    ; 显示个位
    MOV DL, BL
    ADD DL, '0'
    MOV AH, 02H
    INT 21H
    
    RET
DISPLAY_NUMBER ENDP

; 换行子程序
NEW_LINE PROC
    MOV AH, 09H
    LEA DX, NEWLINE
    INT 21H
    RET
NEW_LINE ENDP

CODE ENDS
END START