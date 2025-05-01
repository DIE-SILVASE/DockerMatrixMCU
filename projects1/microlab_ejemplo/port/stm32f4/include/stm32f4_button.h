/**
 * @file stm32f4_button.h
 * @brief Header for stm32f4_button.c file.
 * @author Román Cárdenas, Alberto Boscá, Josué Pagán (r.cardenas@upm.es, j.pagan@upm.es, alberto.bosca@upm.es)
 * @date 2024-01-01
 */
#ifndef STM32F4_BUTTON_H_
#define STM32F4_BUTTON_H_


/* HW dependent includes */
#include "stm32f4xx.h"
#include "stm32f4_system.h"

/* Defines -------------------------------------------------------------------*/
#define BUTTON_PORT GPIOC /*!< Button port */
#define BUTTON_PIN 13     /*!< Button pin */

#define MODER13_MASK (0x03 << BUTTON_PIN * 2) /*<! Mask for BUTTON_PIN in MODER register */
#define PUDR13_MASK (0x03 << BUTTON_PIN * 2)  /*<! Mask for BUTTON_PIN in PUPDR register */

#define MODER13_AS_INPUT (STM32F4_GPIO_MODE_IN << BUTTON_PIN * 2)       /*<! Input mode for BUTTON_PIN in MODER register */
#define PUPDR13_AS_NOPUPD (STM32F4_GPIO_PUPDR_NOPULL << BUTTON_PIN * 2) /*<! No pull up/down for BUTTON_PIN in PUPDR register */
#define IDR13_MASK (0x01 << BUTTON_PIN)                         /*<! Mask for BUTTON_PIN in IDR register */



#define BUTTON_0_ID 0                   /*!<Button identifier*/
#define BUTTON_0_GPIO GPIOC             /*!<Button GPIO port*/
#define BUTTON_0_PIN  13                 /*!<Button GPIO pin*/
#define BUTTON_0_DEBOUNCE_TIME_MS 150   /*!<Button debounce time*/


#define GPIO_MODE_IN 0x00        /*!< GPIO as input */
#define GPIO_MODE_OUT 0x01       /*!< GPIO as output */
#define GPIO_MODE_ALTERNATE 0x02 /*!< GPIO as alternate function */
#define GPIO_MODE_ANALOG 0x03    /*!< GPIO as analog */

#define GPIO_PUPDR_NOPULL 0x00   /*!< GPIO no pull up or down */
#define GPIO_PUPDR_PUP 0x01      /*!< GPIO pull up */
#define GPIO_PUPDR_PDOWN 0x02    /*!< GPIO pull down */

/* Interruption */
#define TRIGGER_RISING_EDGE 0x01U                                      /*!< Interrupt mask for detecting rising edge */
#define TRIGGER_FALLING_EDGE 0x02U                                     /*!< Interrupt mask for detecting falling edge */
#define TRIGGER_BOTH_EDGE (TRIGGER_RISING_EDGE | TRIGGER_FALLING_EDGE) /*!< Interrupt mask for detecting both rising and falling edges */
#define TRIGGER_ENABLE_EVENT_REQ 0x04U                                 /*!< Interrupt mask to enable event requests */
#define TRIGGER_ENABLE_INTERR_REQ 0x08U                                /*!< Interrupt mask to enable interrupt request */

/* Typedefs --------------------------------------------------------------------*/

/**
 * @brief Structure to define the HW dependencies of a button.
 * 
 */
typedef struct        
{
    GPIO_TypeDef *p_port;   /*!<GPIO where the button is connected*/
    uint8_t pin;            /*!<Pin/line where the button is connected*/
    bool flag_pressed;      /*!<Flag to indicate that the button has been pressed*/
} port_button_hw_t;  

/* Global variables */
extern port_button_hw_t buttons_arr[];   /*!<Array of elements that represents the HW characteristics of the buttons*/



#endif // STM32F4_BUTTON_H_
