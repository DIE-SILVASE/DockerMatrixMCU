#include "port_pwm_signal.h"
#include "stm32f4_pwm_signal.h"
#include "stm32f4xx.h" // Cabecera estándar STM32F4
#include <stdint.h> // Para uint32_t

void port_pwm_signal_gpio_setup(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Habilitar reloj de GPIOA
    
    stm32f4_system_gpio_config(PWM_SIGNAL_PORT,PWM_SIGNAL_PIN,STM32F4_GPIO_MODE_AF, STM32F4_GPIO_PUPDR_NOPULL);
    stm32f4_system_gpio_config_exti(PWM_SIGNAL_PORT,PWM_SIGNAL_PIN, PWM_SIGNAL_ALT_FUNC);
    stm32f4_system_gpio_config_alternate(PWM_SIGNAL_PORT,PWM_SIGNAL_PIN, PWM_SIGNAL_ALT_FUNC);
}

void port_pwm_signal_timer_setup(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Habilitar reloj de TIM5

    TIM5->PSC = 8399;  // Prescaler (84MHz / (8399 + 1)) = 10kHz
    TIM5->ARR = 19;    // Auto-reload = 19 → Periodo de 2ms → 500 Hz

    TIM5->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM5->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos); // PWM Mode 1
    TIM5->CCMR1 |= TIM_CCMR1_OC1PE; // Enable preload

    TIM5->CCER |= TIM_CCER_CC1E;    // Enable output for channel 1

    TIM5->CCR1 = 10;                // 50% duty cycle (aproximadamente)

    TIM5->CR1 |= TIM_CR1_ARPE;      // Auto-reload preload enable
}

void port_pwm_signal_start(void)
{
    TIM5->CR1 |= TIM_CR1_CEN; // Enable Timer5
}
