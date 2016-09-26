#ifndef __HARDWARE_H_
#define __HARDWARE_H_


#define CONTEXT_SAVE() \
    asm("push R31	; store R31 on stack");   \
    asm("IN R31,0x3F	; save SREG in R31");\
    asm("push r26");\
    asm("push r27");\
    asm("push R28");\
    asm("push R29");\
    asm("ldi r28, lo8(context)");\
    asm("ldi r29, hi8(context)");\
    asm("ld r26, Y+");\
    asm("ld r27, Y+");\
    asm("pop r29");\
    asm("pop r28");\
    asm("ST X+, R0");\
    asm("ST X+, R1");\
    asm("ST X+, R2");\
    asm("ST X+, R3");\
    asm("ST X+, R4");\
    asm("ST X+, R5");\
    asm("ST X+, R6");\
    asm("ST X+, R7");\
    asm("ST X+, R8");\
    asm("ST X+, R9");\
    asm("ST X+, R10");\
    asm("ST X+, R11");\
    asm("ST X+, R12");\
    asm("ST X+, R13");\
    asm("ST X+, R14");\
    asm("ST X+, R15");\
    asm("ST X+, R16");\
    asm("ST X+, R17");\
    asm("ST X+, R18");\
    asm("ST X+, R19");\
    asm("ST X+, R20");\
    asm("ST X+, R21");\
    asm("ST X+, R22");\
    asm("ST X+, R23");\
    asm("ST X+, R24");\
    asm("ST X+, R25");\
    asm("POP R25");\
    asm("POP R24"); \
    asm("ST X+, R24");\
    asm("ST X+, R25"); \
    asm("ST X+, R28");\
    asm("ST X+, R29");\
    asm("ST X+, R30");\
    asm("POP R0");\
    asm("ST X+, R0");\
    asm("ST X+, R31");\
    asm("IN R0,0x3D");\
    asm("IN R1,0x3E");\
    asm("ST X+, R0");\
    asm("ST X+, R1");

#define CONTEXT_RESTROE() \
    asm("ldi r26, lo8(context)");\
    asm("ldi r27, hi8(context)");\
    asm("ld r28, X+");\
    asm("ld r29, X+");\
    asm("LDD R16, Y+32");\
    asm("OUT 0x3F, R16");\
    asm("LDD R16, Y+33");\
    asm("LDD R17, Y+34");\
    asm("OUT 0x3D, R16");\
    asm("OUT 0x3E, R17");\
    asm("LD R0,  Y+");\
    asm("LD R1,  Y+");\
    asm("LD R2,  Y+");\
    asm("LD R3,  Y+");\
    asm("LD R4,  Y+");\
    asm("LD R5,  Y+");\
    asm("LD R6,  Y+");\
    asm("LD R7,  Y+");\
    asm("LD R8,  Y+");\
    asm("LD R9,  Y+");\
    asm("LD R10, Y+");\
    asm("LD R11, Y+");\
    asm("LD R12, Y+");\
    asm("LD R13, Y+");\
    asm("LD R14, Y+");\
    asm("LD R15, Y+");\
    asm("LD R16, Y+");\
    asm("LD R17, Y+");\
    asm("LD R18, Y+");\
    asm("LD R19, Y+");\
    asm("LD R20, Y+");\
    asm("LD R21, Y+");\
    asm("LD R22, Y+");\
    asm("LD R23, Y+");\
    asm("LD R24, Y+");\
    asm("LD R25, Y+");\
    asm("LD R26, Y+");\
    asm("LD R27, Y+");\
    asm("LD R30, Y+");\
    asm("LD R31, Y+");\
    asm("PUSH R30");\
    asm("PUSH R31");\
    asm("LD R30, Y+");\
    asm("LD R31, Y+");\
    asm("POP R29");\
    asm("POP R28");


#define CONTEXT_RETURN() asm("reti")


#endif
