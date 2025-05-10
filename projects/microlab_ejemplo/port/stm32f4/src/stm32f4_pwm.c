/**
 * @file port_button.c
 * @brief Button port file for the button FSM example (HW independent). 
 * @author Román Cárdenas, Alberto Boscá, Josué Pagán (r.cardenas@upm.es, j.pagan@upm.es, alberto.bosca@upm.es)
 * @date 2024-01-01
 */
/* Includes ------------------------------------------------------------------*/
#include "port_pwm.h"
#include "stm32f4xx.h"
#include "stm32f4_pwm.h"
#include <stdint.h>


/* Public functions ----------------------------------------------------------*/

/* **TO-DO alumnos: ** implement port_button_gpio_setup */
void port_pwm_gpio_setup(void)
{
    /* Primero, habilitamos siempre el reloj de los perifericos */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    
    stm32f4_system_gpio_config(PWM_GPIO_PORT,PWM_PIN,STM32F4_GPIO_MODE_AF, STM32F4_GPIO_PUPDR_NOPULL);
    stm32f4_system_gpio_config_exti(PWM_GPIO_PORT,PWM_PIN, PWM_ALT_FUNC);
    stm32f4_system_gpio_config_alternate(PWM_GPIO_PORT,PWM_PIN, PWM_ALT_FUNC);

    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN ; /* TIM2 con APB1 . */

 /* T e m p o r i z a c i o n */
/* 1) Fuente de reloj : interno ( bits CKD =00) */
PWM_TIM -> CR1 = 0x0000 ; /* Aunque es el valor por defecto */

 /* 2) D e s h a b i l i t a el contador ( no es i n d i s p e n s a b l e ) . */
 PWM_TIM -> CR1 &= ~ TIM_CR1_CEN ;

 /* 3) A segu ram os inicio del contador a 0 */
 PWM_TIM -> CNT = 0;

/* 4) Cargamos el a u t o r r e l o a d */
PWM_TIM -> ARR = 63999;

 /* 5) Cargamos el prescaler */
 PWM_TIM -> PSC = 4;

 /* 6) ( IMP ORT ANTE ) Re - inic ial iza el contador y actualiza los registros .
IM PORT ANT E que este despues de cargar ARR y PSC */
 /* Los valores de PSC y ARR estan en los registro de precarga . Para cargarlos
en los registros activos , n e c e s i t a m o s que se actualice un evento . Esto
podemos hacerlo m a n u a l m e n t e a c t u a l i z a n d o el registro TIMx - > EGR , o esperar a
que pase el timer . */
PWM_TIM -> EGR = TIM_EGR_UG ; /* Genera evento de a c t u a l i z a c i o n */

 /* PWM . CANAL 1 */
 /* 7) D e s h a b i l i t a r el output compare para hacer m o d i f i c a c i o n e s ( no es
i n d i s p e n s a b l e ) */
PWM_TIM -> CCER &= ~ TIM_CCER_CC1E ;
/* 8) H a b i l i t a m o s modo PWM y h a b i l i t a m o s el preload */
PWM_TIM -> CCMR1 |= TIM_AS_PWM1_MASK ; /* Modo PWM 1 */
PWM_TIM -> CCMR1 |= TIM_CCMR1_OC1PE ; /* Habilita el preload */

/* 9) Ancho del pulso de PWM */
PWM_TIM -> CCR1 = 32000;
 /* 10) Habilita output compare para empezar a contar ( podria hacerse en otro
momento ) */
PWM_TIM -> CCER |= TIM_CCER_CC1E ;
 /* 11) Habilita timer para empezar a contar ( podria hacerse en otro momento ) */
 PWM_TIM -> CR1 |= TIM_CR1_CEN ;
}

void port_pwm_set_dc(uint8_t dc) {
    if (dc > 100) dc = 100;

    // Calculamos el nuevo valor de CCR1
    uint32_t arr = PWM_TIM->ARR;
    uint32_t new_ccr = (dc * arr) / 100;
    PWM_TIM->CCR1 = new_ccr;
}


void port_pwm_set_frec(uint32_t){

}


void port_pwm_get_frec(uint32_t){

}

void port_pwm_stop(void){

}

void port_pwm_start(void){
    
}