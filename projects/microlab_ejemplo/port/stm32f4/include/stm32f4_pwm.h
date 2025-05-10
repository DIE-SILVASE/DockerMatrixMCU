#ifndef STM32F4_PWM_H_
#define STM32F4_PWM_H_

/* HW dependent includes */
#include "stm32f4xx.h"
#include "stm32f4_system.h"

/* Defines -------------------------------------------------------------------*/
#define PWM_PIN 5           /*!< GPIO pin of the LED2 in the Nucleo board */
#define PWM_GPIO_PORT GPIOA /*!< GPIO port of the LED2 in the Nucleo board */
#define PWM_TIM TIM2

#define PWM_MODER_MASK (GPIO_MODER_MODE0 << PWM_PIN * 2) /*!< Mask for the LED2 in the MODE Register */
#define PUPDR5_MASK (GPIO_PUPDR_PUPD0 << PWM_PIN * 2) /*!< Mask for the LED2 in the PUPD Register */


#define PWM_MODER_AS_ALTERNATE (STM32F4_GPIO_MODE_AF << PWM_PIN * 2) /*!< Output mode for the LED2 in the MODE Register */
#define PWM_PUPDR_AS_NOPUPD (STM32F4_GPIO_PUPDR_NOPULL << PWM_PIN * 2) /*!< No push/pull configuration for the LED2 in the MODE Register */

#define IDR5_MASK (GPIO_IDR_ID0 << PWM_PIN) /*!< Mask for the LED2 in the Input Data Register */
#define ODR5_MASK (GPIO_ODR_OD0 << PWM_PIN) /*!< Mask for the LED2 in the Output Data Register */


#define BASE_ALT_MASK 0x0F /* En binario : 0 b1111 (4 bits ) */
#define PWM_AFR_INDEX (PWM_PIN / 8)
#define PWM_AFR_MASK ( 0x0F << 4* (PWM_PIN % 8))

#define PWM_ALT_FUNC 0x1

#define TIM_AS_PWM1_MASK 0x0060


#endif // STM32F4_PWM_H_