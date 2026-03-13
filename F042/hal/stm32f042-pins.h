#ifndef __STM32_F024_PINS_H__
#define __STM32_F024_PINS_H__

/*

Reference:
    https://www.st.com/resource/en/reference_manual/rm0360-stm32f030x4x6x8xc-and-stm32f070x6xb-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

*/
// ****************************************************************************************************
//                  GPIO
// ****************************************************************************************************

enum {
    // 2.2.2 p. RM.40
    GPIOA_BASE = 0x48000000UL,  // Port A base (2.2.2 p. RM.40)
    GPIOB_BASE = 0x48000400UL,  // Port B base
    GPIOC_BASE = 0x48000800UL,  // Port C base
    GPIO_PORT_STRIDE = 0x400,

    GPIO_PORTA = 0,
    GPIO_PORTB = 1,
    GPIO_PORTF = 5,

    // GPIO register offsets (8.4 p. RM.140-141)
    MODER_OFFSET   = 0x00, // Port mode
    OTYPER_OFFSET  = 0x04, // Output type
    OSPEEDR_OFFSET = 0x08, // Output speed
    PUPDR_OFFSET   = 0x0C, // Pull-up/pull-down
    IDR_OFFSET     = 0x10, // Input data
    ODR_OFFSET     = 0x14, // Output data
    BSRR_OFFSET    = 0x18, // Bit set/reset

    // GPIO Port A
    GPIOA_MODER = GPIOA_BASE + MODER_OFFSET,
    GPIOA_OTYPER = GPIOA_BASE + OTYPER_OFFSET,
    GPIOA_OSPEEDR = GPIOA_BASE + OSPEEDR_OFFSET,
    GPIOA_PUPDR = GPIOA_BASE + PUPDR_OFFSET,
    GPIOA_IDR = GPIOA_BASE + IDR_OFFSET,
    GPIOA_ODR = GPIOA_BASE + ODR_OFFSET,
    GPIOA_BSRR = GPIOA_BASE + BSRR_OFFSET,

    // GPIO Port B
    GPIOB_MODER = GPIOB_BASE + MODER_OFFSET,
    GPIOB_OTYPER = GPIOB_BASE + OTYPER_OFFSET,
    GPIOB_OSPEEDR = GPIOB_BASE + OSPEEDR_OFFSET,
    GPIOB_PUPDR = GPIOB_BASE + PUPDR_OFFSET,
    GPIOB_IDR = GPIOB_BASE + IDR_OFFSET,
    GPIOB_ODR = GPIOB_BASE + ODR_OFFSET,
    GPIOB_BSRR = GPIOB_BASE + BSRR_OFFSET,

    // GPIO Port C
    GPIOC_MODER = GPIOC_BASE + MODER_OFFSET,
    GPIOC_OTYPER = GPIOC_BASE + OTYPER_OFFSET,
    GPIOC_OSPEEDR = GPIOC_BASE + OSPEEDR_OFFSET,
    GPIOC_PUPDR = GPIOC_BASE + PUPDR_OFFSET,
    GPIOC_IDR = GPIOC_BASE + IDR_OFFSET,
    GPIOC_ODR = GPIOC_BASE + ODR_OFFSET,
    GPIOC_BSRR = GPIOC_BASE + BSRR_OFFSET,
};

enum {

    // 7.4.13 p. RM.123-124
    RCC_BASE    = 0x40021000,
    RCC_AHBENR  = RCC_BASE + 0x14,     // AHB peripheral clock enable register

    RCC_AHBENR_IOPAEN = (1u << 17),
    RCC_AHBENR_IOPBEN = (1u << 18),
    RCC_AHBENR_IOPCEN = (1u << 19),
};

#endif