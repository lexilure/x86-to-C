%include "io64.inc"

section .data
vectorA dq 1.0, 2.0, 3.0, 4.0, 5.0 ; Example vector A of length 5
vectorB dq 5.0, 4.0, 3.0, 2.0, 1.0  ; Example vector B of length 5

section .text
bits 64
default rel 

global dot_product_asm

dot_product_asm:
    mov rbp, rsp               ; For correct debugging  
    mov ecx, r8d               ; Move n into ecx, the loop counter
    xor esi, esi               ; Start index at 0

    ; Initialize result to 0
    xorpd xmm2, xmm2           ; xmm2 = 0.0

loop_start:
    cmp esi, ecx               ; Compare current index with n
    jge loop_end               ; If esi >= n, we're done

    ; Load one element from vectorA into xmm0
    movsd xmm0, [vectorA + esi*8]
    ; Load one element from vectorB into xmm1
    movsd xmm1, [vectorB + esi*8]

    ; Multiply and accumulate
    mulsd xmm0, xmm1           ; xmm0 = xmm0 * xmm1
    addsd xmm2, xmm0           ; xmm2 = xmm2 + xmm0

    inc esi                    ; Move to the next element
    jmp loop_start             ; Continue loop

loop_end:
    ; Return the result
    movq rax, xmm2             ; Move the result to rax
    ret
