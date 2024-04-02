section .text
bits 64
default rel 

global dot_product_asm

dot_product_asm:              
    xor rsi, rsi               ; Start index at 0
    ; Initialize result to 0
    xorpd xmm0, xmm0           ; xmm0 = 0.0 , accumulator for the sdot result

loop_start:
    cmp rsi, r8             ; Compare current index with n
    jge loop_end               ; If rsi >= n, we're done

    ; Multiply vectors element-wise and accumulate
    movsd xmm1, [rcx + rsi*8] 
    movsd xmm2, [rdx + rsi*8] 
    mulsd xmm1, xmm2         
    addsd xmm0, xmm1          

    inc rsi                
    jmp loop_start           


loop_end:
    ; Return the result
    movq xmm1, xmm0 ; Move the result to rax
    ret
