/**
 * @file stm32f4_button.h
 * @brief Header for stm32f4_button.c file.
 * @author Román Cárdenas, Alberto Boscá, Josué Pagán (r.cardenas@upm.es, j.pagan@upm.es, alberto.bosca@upm.es)
 * @date 2024-01-01
 */
#ifndef STM32F4_INPUT_H_
#define STM32F4_INPUT_H_


/* HW dependent includes */
#include "stm32f4xx.h"
#include "stm32f4_system.h"

/* Defines -------------------------------------------------------------------*/
#include <stdint.h>

/* Macros configurables -----------------------------------------------------*/

// 💥 Aquí puedes cambiar el pin/puerto/timer fácilmente
#define INPUT_CAPTURE_PORT         GPIOA
#define INPUT_CAPTURE_PIN          5
#define INPUT_CAPTURE_AF            1   // Alternate Function número (AF1 para TIM2)
#define INPUT_CAPTURE_TIMER         TIM2
#define INPUT_CAPTURE_TIMER_EN_BIT  RCC_APB1ENR_TIM2EN
#define INPUT_CAPTURE_CHANNEL       1   // Canal 1
#define INPUT_CAPTURE_CCR           (INPUT_CAPTURE_TIMER->CCR1) // CCR1


#endif // STM32F4_INPUT_H_
