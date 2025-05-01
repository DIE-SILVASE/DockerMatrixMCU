#include "stm32f4_input.h"
#include "stm32f4xx.h" 
#include "port_input.h"


void port_input_gpio_setup(void)
{
    // Habilitar reloj GPIO (automáticamente detectando el puerto)
    if (INPUT_CAPTURE_PORT == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (INPUT_CAPTURE_PORT == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (INPUT_CAPTURE_PORT == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    
    stm32f4_system_gpio_config(INPUT_CAPTURE_PORT, INPUT_CAPTURE_PIN, STM32F4_GPIO_MODE_AF, STM32F4_GPIO_PUPDR_NOPULL);
    stm32f4_system_gpio_config_exti(INPUT_CAPTURE_PORT, INPUT_CAPTURE_PIN, INPUT_CAPTURE_AF);
    stm32f4_system_gpio_config_alternate(INPUT_CAPTURE_PORT, INPUT_CAPTURE_PIN, INPUT_CAPTURE_AF);

}

void port_input_timer_setup(void)
{
    // Habilitar reloj del Timer
    RCC->APB1ENR |= INPUT_CAPTURE_TIMER_EN_BIT;

    // Prescaler y ARR para hacer que el timer cuente lento (ejemplo: 1us)
    INPUT_CAPTURE_TIMER->PSC = 83; // Suponiendo reloj a 84MHz
    INPUT_CAPTURE_TIMER->ARR = 0xFFFF;

    // Configurar canal para Input Capture
    if (INPUT_CAPTURE_CHANNEL == 1)
    {
        INPUT_CAPTURE_TIMER->CCMR1 &= ~TIM_CCMR1_CC1S;
        INPUT_CAPTURE_TIMER->CCMR1 |= (0x01 << TIM_CCMR1_CC1S_Pos);
        INPUT_CAPTURE_TIMER->CCER &= ~TIM_CCER_CC1P; // Rising edge
        INPUT_CAPTURE_TIMER->CCER |= TIM_CCER_CC1E;  // Enable capture
    }
    else if (INPUT_CAPTURE_CHANNEL == 2)
    {
        INPUT_CAPTURE_TIMER->CCMR1 &= ~TIM_CCMR1_CC2S;
        INPUT_CAPTURE_TIMER->CCMR1 |= (0x01 << TIM_CCMR1_CC2S_Pos);
        INPUT_CAPTURE_TIMER->CCER &= ~TIM_CCER_CC2P;
        INPUT_CAPTURE_TIMER->CCER |= TIM_CCER_CC2E;
    }
    else if (INPUT_CAPTURE_CHANNEL == 3)
    {
        INPUT_CAPTURE_TIMER->CCMR2 &= ~TIM_CCMR2_CC3S;
        INPUT_CAPTURE_TIMER->CCMR2 |= (0x01 << TIM_CCMR2_CC3S_Pos);
        INPUT_CAPTURE_TIMER->CCER &= ~TIM_CCER_CC3P;
        INPUT_CAPTURE_TIMER->CCER |= TIM_CCER_CC3E;
    }
    else if (INPUT_CAPTURE_CHANNEL == 4)
    {
        INPUT_CAPTURE_TIMER->CCMR2 &= ~TIM_CCMR2_CC4S;
        INPUT_CAPTURE_TIMER->CCMR2 |= (0x01 << TIM_CCMR2_CC4S_Pos);
        INPUT_CAPTURE_TIMER->CCER &= ~TIM_CCER_CC4P;
        INPUT_CAPTURE_TIMER->CCER |= TIM_CCER_CC4E;
    }

    // No arrancamos el timer todavía
}

void port_input_start(void)
{
    INPUT_CAPTURE_TIMER->CR1 |= TIM_CR1_CEN; // Enable timer
}

void port_input_stop(void)
{
    INPUT_CAPTURE_TIMER->CR1 &= ~TIM_CR1_CEN; // Disable timer
}

uint32_t port_input_get_captured_value(void)
{
    return INPUT_CAPTURE_CCR;
}
