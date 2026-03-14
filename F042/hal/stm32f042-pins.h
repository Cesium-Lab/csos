#ifndef __STM32F042_PINS_H__
#define __STM32F042_PINS_H__

#include <stdint.h>

/*

Reference:
    RM0091 — STM32F0x1/x2/x8 reference manual:
        https://www.st.com/resource/en/reference_manual/rm0091-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
    DocID025832 - STM32F042x4/x6 Datasheet
        https://www.st.com/resource/en/datasheet/stm32f042c4.pdf

*/



// ****************************************************************************************************
//                      GPIO (AHB2)
// ****************************************************************************************************

// For making function writing easier
#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTF 5

// RM p.40 
#define GPIOA_BASE      0x48000000
#define GPIOB_BASE      0x48000400
#define GPIOF_BASE      0x48001C00   // Port F (only PF0 and PF1 available on QFP32)
#define GPIO_PORT_STRIDE 0x400          // Each GPIO port offset

#define GPIO_PIN_MODE_INPUT     0b00
#define GPIO_PIN_MODE_OUTPUT    0b01
#define GPIO_PIN_MODE_ALT       0b10
#define GPIO_PIN_MODE_ANALOG    0b11

// **************************************************
//      Registers
// **************************************************

// RM 140-141
#define MODER_OFFSET   0x00   // GPIO Port mode
#define OTYPER_OFFSET  0x04   // GPIO Output type
#define OSPEEDR_OFFSET 0x08   // GPIO Output speed
#define PUPDR_OFFSET   0x0C   // GPIO Pull-up/pull-down
#define IDR_OFFSET     0x10   // GPIO Input data
#define ODR_OFFSET     0x14   // GPIO Output data
#define BSRR_OFFSET    0x18   // GPIO Bit set/reset
#define AFRL_OFFSET    0x20   // GPIO Alternate Function High
#define AFTH_OFFSET    0x24   // GPIO Alternate Function Low

// **************************************************
//      Port A Registers
// **************************************************

#define GPIOA_MODER    (GPIOA_BASE + MODER_OFFSET)
#define GPIOA_OTYPER   (GPIOA_BASE + OTYPER_OFFSET)
#define GPIOA_OSPEEDR  (GPIOA_BASE + OSPEEDR_OFFSET)
#define GPIOA_PUPDR    (GPIOA_BASE + PUPDR_OFFSET)
#define GPIOA_IDR      (GPIOA_BASE + IDR_OFFSET)
#define GPIOA_ODR      (GPIOA_BASE + ODR_OFFSET)
#define GPIOA_BSRR     (GPIOA_BASE + BSRR_OFFSET)
#define GPIOA_AFRL     (GPIOA_BASE + AFLR_OFFSET)
#define GPIOA_AFRH     (GPIOA_BASE + AFLH_OFFSET)

// **************************************************
//      Port B Registers
// **************************************************

#define GPIOB_MODER    (GPIOB_BASE + MODER_OFFSET)
#define GPIOB_OTYPER   (GPIOB_BASE + OTYPER_OFFSET)
#define GPIOB_OSPEEDR  (GPIOB_BASE + OSPEEDR_OFFSET)
#define GPIOB_PUPDR    (GPIOB_BASE + PUPDR_OFFSET)
#define GPIOB_IDR      (GPIOB_BASE + IDR_OFFSET)
#define GPIOB_ODR      (GPIOB_BASE + ODR_OFFSET)
#define GPIOB_BSRR     (GPIOB_BASE + BSRR_OFFSET)
#define GPIOB_AFRL     (GPIOB_BASE + AFLR_OFFSET)
#define GPIOB_AFRH     (GPIOB_BASE + AFLH_OFFSET)

// **************************************************
//      Port F Registers
// **************************************************

#define GPIOF_MODER    (GPIOF_BASE + MODER_OFFSET)
#define GPIOF_OTYPER   (GPIOF_BASE + OTYPER_OFFSET)
#define GPIOF_OSPEEDR  (GPIOF_BASE + OSPEEDR_OFFSET)
#define GPIOF_PUPDR    (GPIOF_BASE + PUPDR_OFFSET)
#define GPIOF_IDR      (GPIOF_BASE + IDR_OFFSET)
#define GPIOF_ODR      (GPIOF_BASE + ODR_OFFSET)
#define GPIOF_BSRR     (GPIOF_BASE + BSRR_OFFSET)
#define GPIOF_AFRL     (GPIOF_BASE + AFLR_OFFSET)
#define GPIOF_AFRH     (GPIOF_BASE + AFLH_OFFSET)

// ****************************************************************************************************
//                      RCC (Reset and Clock Control) (AHB1) - RM Section 7
// ****************************************************************************************************

// RM Section 7, p.123-124
#define RCC_BASE       0x40021000
#define RCC_CR         (RCC_BASE + 0x00)  // Clock control register
#define RCC_CFGR       (RCC_BASE + 0x04)  // Clock configuration register
#define RCC_CIR        (RCC_BASE + 0x08)  // Clock interrupt register
#define RCC_APB2RSTR   (RCC_BASE + 0x0C)  // APB2 peripheral reset register
#define RCC_APB1RSTR   (RCC_BASE + 0x10)  // APB1 peripheral reset register
#define RCC_AHBENR     (RCC_BASE + 0x14)  // AHB peripheral clock enable register
#define RCC_APB2ENR    (RCC_BASE + 0x18)  // APB2 peripheral clock enable register
#define RCC_APB1ENR    (RCC_BASE + 0x1C)  // APB1 peripheral clock enable register
#define RCC_BDCR       (RCC_BASE + 0x20)  // Backup domain control register
#define RCC_CSR        (RCC_BASE + 0x24)  // Control/status register

// **************************************************
//  AHBENR — AHB Peripheral Clock Enable Bits
//  Only necessary for QFP32 pins, timers, DMA, etc.
// **************************************************
// RM Section 7.4.6, p.110-111
#define RCC_AHB_A_EN  (1u << 17)  // GPIOA clock enable
#define RCC_AHB_B_EN  (1u << 18)  // GPIOB clock enable
#define RCC_AHB_F_EN  (1u << 22)  // GPIOF clock enable (PF0, PF1 only)
#define RCC_AHB_CRC_EN   (1u << 6)   // CRC clock enable (optional for data integrity)

// **************************************************
//  APB1ENR — APB1 Peripheral Clock Enable Bits
//  Needed for timers, UART, I2C, etc.
// **************************************************
// RM Section 7.4.8, p.113-114
#define RCC_APB1_TIM3_EN   (1u << 1)  // Timer 3 clock enable
#define RCC_APB1_USART2_EN (1u << 17) // USART2 clock enable
#define RCC_APB1_I2C1_EN   (1u << 21) // I2C1 clock enable
#define RCC_APB1_I2C2_EN   (1u << 22) // I2C2 clock enable (optional)
#define RCC_APB1_PWR_EN    (1u << 28) // Power interface clock enable (optional)

// **************************************************
//  APB2ENR — APB2 Peripheral Clock Enable Bits
//  Needed for USART1, SYSCFG, ADC, etc.
// **************************************************
// RM Section 7.4.7, p.111-113
#define RCC_APB2_SYSCFG_EN  (1u << 0)  // SYSCFG clock enable
#define RCC_APB2_USART1_EN  (1u << 14) // USART1 clock enable (optional)
#define RCC_APB2_ADC1_EN    (1u << 9)  // ADC1 clock enable (if using ADC)
#define RCC_APB2_TIM1_EN    (1u << 11) // Timer 1 clock enable
#define RCC_APB2_SPI1_EN    (1u << 12) // SPI clock enable

// ****************************************************************************************************
//  GPIO Pin Numbers
//  (Useful for assembly or bit-shifts)
// ****************************************************************************************************
#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7
#define PA8 8
#define PA9 9
#define PA10 10
#define PA11 11
#define PA12 12
#define PA13 13
#define PA14 14
#define PA15 15

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7
#define PB8 8
#define PB9 9
#define PB10 10
#define PB11 11
#define PB12 12
#define PB13 13
#define PB14 14
#define PB15 15

#define PF0 0
#define PF1 1

#endif