section .text
global dot_product_asm
bits 64

dot_product_asm:
    xor rsi, rsi             
    xorpd xmm0, xmm0         

loop_start:
    cmp rsi, r8           
    jge loop_end           

    ; Multiply vectors element-wise and accumulate
    movsd xmm1, [rcx + rsi*8] 
    movsd xmm2, [rdx + rsi*8] 
    mulsd xmm1, xmm2      
    addsd xmm0, xmm1       

    inc rsi                  
    jmp loop_start            

loop_end:
    movsd xmm1, xmm0      
    ret