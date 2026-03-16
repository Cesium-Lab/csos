.syntax unified
.cpu cortex-m0
.thumb
.fpu softvfp

/* ------------------ GLOBAL SYMBOLS ------------------ */
.global g_pfnVectors
.global Reset_Handler
.global Default_Handler
.global main
.extern main

/* ------------------ VECTOR TABLE ------------------ */
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
    .word _stack_start               /* initial stack pointer */
    .word Reset_Handler         /* Reset handler */
    .word NMI_Handler           /* NMI */
    .word HardFault_Handler     /* HardFault */
    .word 0                     /* Reserved */
    .word 0                     /* Reserved */
    .word 0                     /* Reserved */
    .word 0                     /* Reserved */
    .word 0                     /* Reserved */
    .word 0                     /* Reserved */
    .word 0                     /* Reserved */
    .word SVC_Handler           /* SVC */
    .word 0                     /* Reserved */
    .word 0                     /* Reserved */
    .word PendSV_Handler        /* PendSV */
    .word SysTick_Handler       /* SysTick */

/* IRQ handlers (weak defaults) */
    .word WWDG_IRQHandler
    .word PVD_VDDIO2_IRQHandler
    .word RTC_IRQHandler
    .word FLASH_IRQHandler
    .word RCC_CRS_IRQHandler
    .word EXTI0_1_IRQHandler
    .word EXTI2_3_IRQHandler
    .word EXTI4_15_IRQHandler
    .word TSC_IRQHandler
    .word DMA1_Channel1_IRQHandler
    .word DMA1_Channel2_3_IRQHandler
    .word DMA1_Channel4_5_IRQHandler
    .word ADC1_IRQHandler
    .word TIM1_BRK_UP_TRG_COM_IRQHandler
    .word TIM1_CC_IRQHandler
    .word TIM2_IRQHandler
    .word TIM3_IRQHandler
    .word 0
    .word 0
    .word TIM14_IRQHandler
    .word 0
    .word TIM16_IRQHandler
    .word TIM17_IRQHandler
    .word I2C1_IRQHandler
    .word 0
    .word SPI1_IRQHandler
    .word SPI2_IRQHandler
    .word USART1_IRQHandler
    .word USART2_IRQHandler
    .word 0
    .word CEC_CAN_IRQHandler
    .word USB_IRQHandler

/* ------------------ RESET HANDLER ------------------ */
.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* set stack pointer */
    ldr   r0, =_stack_start
    mov   sp, r0

    /* ------------------ COPY DATA TO SRAM ------------------ */
    ldr   r0, =_sdata       /* start of .data in SRAM */
    ldr   r1, =_edata       /* end of .data in SRAM */
    ldr   r2, =_sidata      /* start of .data in Flash */

CopyDataLoop:
    cmp   r0, r1
    bcs   CopyDataDone
    ldr   r3, [r2]       /* load from flash */
    str   r3, [r0]       /* store to SRAM */
    adds   r0, r0, #4     /* increment SRAM pointer */
    adds   r2, r2, #4     /* increment Flash pointer */
    b     CopyDataLoop
CopyDataDone:

    /* ------------------ ZERO BSS ------------------ */
    ldr   r0, =_sbss
    ldr   r1, =_ebss
    movs  r2, #0

ZeroBSSLoop:
    cmp   r0, r1
    bcs   ZeroBSSDone
    str   r2, [r0]       /* store zero */
    adds   r0, r0, #4     /* increment pointer */
    b     ZeroBSSLoop
ZeroBSSDone:

    /* ------------------ ENABLE GPIO CLOCKS ------------------ */
    /* RCC_AHBENR address: 0x40021014 */
    @ ldr   r0, =0x40021014      /* RCC_AHBENR */
    @ ldr   r1, [r0]
    @ ldr   r2, =(1<<18)         /* IOPBEN (GPIOB) */
    @ orrs  r1, r1, r2
    @ str   r1, [r0]
    /* Optional: Minimal SysTick setup here if needed */

    /* ------------------ CALL MAIN ------------------ */
    bl main

InfiniteLoop:
    b InfiniteLoop

.size Reset_Handler, .-Reset_Handler

/* ------------------ DEFAULT HANDLER ------------------ */
.section .text.Default_Handler,"ax",%progbits
Default_Handler:
    b .

/* ------------------ WEAK HANDLER ALIASES ------------------ */
.weak NMI_Handler
.thumb_set NMI_Handler, Default_Handler
.weak HardFault_Handler
.thumb_set HardFault_Handler, Default_Handler
.weak SVC_Handler
.thumb_set SVC_Handler, Default_Handler
.weak PendSV_Handler
.thumb_set PendSV_Handler, Default_Handler
.weak SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler
.weak WWDG_IRQHandler
.thumb_set WWDG_IRQHandler, Default_Handler
.weak PVD_VDDIO2_IRQHandler
.thumb_set PVD_VDDIO2_IRQHandler, Default_Handler
.weak RTC_IRQHandler
.thumb_set RTC_IRQHandler, Default_Handler
.weak FLASH_IRQHandler
.thumb_set FLASH_IRQHandler, Default_Handler
.weak RCC_CRS_IRQHandler
.thumb_set RCC_CRS_IRQHandler, Default_Handler
.weak EXTI0_1_IRQHandler
.thumb_set EXTI0_1_IRQHandler, Default_Handler
.weak EXTI2_3_IRQHandler
.thumb_set EXTI2_3_IRQHandler, Default_Handler
.weak EXTI4_15_IRQHandler
.thumb_set EXTI4_15_IRQHandler, Default_Handler
.weak TSC_IRQHandler
.thumb_set TSC_IRQHandler, Default_Handler
.weak DMA1_Channel1_IRQHandler
.thumb_set DMA1_Channel1_IRQHandler, Default_Handler
.weak DMA1_Channel2_3_IRQHandler
.thumb_set DMA1_Channel2_3_IRQHandler, Default_Handler
.weak DMA1_Channel4_5_IRQHandler
.thumb_set DMA1_Channel4_5_IRQHandler, Default_Handler
.weak ADC1_IRQHandler
.thumb_set ADC1_IRQHandler, Default_Handler
.weak TIM1_BRK_UP_TRG_COM_IRQHandler
.thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler, Default_Handler
.weak TIM1_CC_IRQHandler
.thumb_set TIM1_CC_IRQHandler, Default_Handler
.weak TIM2_IRQHandler
.thumb_set TIM2_IRQHandler, Default_Handler
.weak TIM3_IRQHandler
.thumb_set TIM3_IRQHandler, Default_Handler
.weak TIM14_IRQHandler
.thumb_set TIM14_IRQHandler, Default_Handler
.weak TIM16_IRQHandler
.thumb_set TIM16_IRQHandler, Default_Handler
.weak TIM17_IRQHandler
.thumb_set TIM17_IRQHandler, Default_Handler
.weak I2C1_IRQHandler
.thumb_set I2C1_IRQHandler, Default_Handler
.weak SPI1_IRQHandler
.thumb_set SPI1_IRQHandler, Default_Handler
.weak SPI2_IRQHandler
.thumb_set SPI2_IRQHandler, Default_Handler
.weak USART1_IRQHandler
.thumb_set USART1_IRQHandler, Default_Handler
.weak USART2_IRQHandler
.thumb_set USART2_IRQHandler, Default_Handler
.weak CEC_CAN_IRQHandler
.thumb_set CEC_CAN_IRQHandler, Default_Handler
.weak USB_IRQHandler
.thumb_set USB_IRQHandler, Default_Handler


// ****************************************************************************************************
//                  Lowest level (reg.s)
// ****************************************************************************************************


@
@ put32(addr,val).  c-code equivalant:
@   - put32(addr, val) { *(uint32_t*)addr = val; }
@
@ store value <val> (passed in second argument register r1) 
@ into memory address <addr> (passed in first argument 
@ register, r0).
@
.global PUT32
.type PUT32, %function
.thumb_func
put32:
PUT32:
    str r1,[r0]     @ store r1 into address held in r0
    bx lr           @ return

@ get32(addr)
@
@ c-code equivalent: 
@   - get32(addr) { return *(uint32_t*)addr; }
@
@ load value of <addr> passed in first argument register (r0).
@
.global GET32
.type GET32, %function
.thumb_func
get32:
GET32:
    ldr r0,[r0]     @ load address held in r0 into r0
    bx lr           @ return


@ .global PUT32CHK
@ .type PUT32CHK, %function
@ .thumb_func
@ put32chk
@ PUT32CHK:
@     ldr r0,[r0]     @ load address held in r0 into r0
@     bx lr           @ return
