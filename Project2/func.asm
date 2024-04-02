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

    ; Load one element from vectorA into xmm0
    movsd xmm0, [rcx + rsi*8]
    ; Load one element from vectorB into xmm1
    movsd xmm1, [rcx + rsi*8]

    ; Multiply and accumulate
    mulsd xmm0, xmm1           ; xmm0 = xmm0 * xmm1
    addsd xmm2, xmm0           ; xmm2 = xmm2 + xmm0

    inc rsi                    ; Move to the next element
    jmp loop_start             ; Continue loop

loop_end:
    ; Return the result
    movq xmm1, xmm0 ; Move the result to rax
    ret
