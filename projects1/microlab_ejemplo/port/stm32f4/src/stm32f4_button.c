/**
 * @file port_button.c
 * @brief Button port file for the button FSM example (HW independent). 
 * @author Román Cárdenas, Alberto Boscá, Josué Pagán (r.cardenas@upm.es, j.pagan@upm.es, alberto.bosca@upm.es)
 * @date 2024-01-01
 */
/* Includes ------------------------------------------------------------------*/
#include "port_button.h"
#include "stm32f4xx.h"
#include "stm32f4_button.h"
#include "fsm_led.h"

/* Public functions ----------------------------------------------------------*/

/* **TO-DO alumnos: ** implement port_button_gpio_setup */
void port_button_gpio_setup(void)
{
    /* Primero, habilitamos siempre el reloj de los perifericos */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    /* Luego, limpiamos los registros MODER y PUPDR correspondientes */
    BUTTON_PORT->MODER &= ~MODER13_MASK;
    BUTTON_PORT->PUPDR &= ~PUDR13_MASK;
    /* Finalmente, configuramos el boton como entrada sin pull up/pull down*/
    BUTTON_PORT->MODER |= MODER13_AS_INPUT;
    BUTTON_PORT->PUPDR |= PUPDR13_AS_NOPUPD;
}

/* **TO-DO alumnos: ** implement port_button_read */
bool port_button_read() 
{
    return (bool)(BUTTON_PORT->IDR & IDR13_MASK);
}



// void port_button_init(uint32_t button_id)
// {
//     GPIO_TypeDef *p_port = buttons_arr[button_id].p_port;
//     uint8_t pin = buttons_arr[button_id].pin;
//     port_system_gpio_config( p_port, pin, GPIO_MODE_IN, GPIO_PUPDR_NOPULL); /*!<Configure button as input and no pull up neither pull down connection*/
//     port_system_gpio_config_exti( p_port, pin, TRIGGER_BOTH_EDGE|TRIGGER_ENABLE_INTERR_REQ); /*!<Configure interruption mode in both rising and falling edges, and enable the interrupt request*/
//     port_system_gpio_exti_enable(pin, 1, 0); /*!<Enable the interrupt line and set the priority level to 1 and the subpriority level to 0*/
// }

// /**
//  * @brief Array of elements that represents the HW characteristics of the buttons.
//  * 
//  */
// port_button_hw_t buttons_arr[]= {
//     [BUTTON_0_ID]= {.p_port = BUTTON_0_GPIO, .pin = BUTTON_0_PIN, .flag_pressed = false},
// };


// bool port_button_is_pressed	(uint32_t button_id) 
// {
//     return buttons_arr[button_id].flag_pressed ;
// }


// uint32_t port_button_get_tick()
// {
//     return port_system_get_millis();
// }