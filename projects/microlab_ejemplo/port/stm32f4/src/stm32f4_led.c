/**
 * @file port_led.c
 * @author Román Cárdenas (r.cardenas@upm.es)
 * @brief Port layer for the LED emulation in the Nucleo STM32F4 platform.
 * @date 01-01-2024
 */

/* Standard C includes */
#include <stdio.h>

/* HW independent includes */
#include "port_system.h"
#include "port_led.h"

/* HW dependent includes */
#include "stm32f4xx.h"
#include "stm32f4_system.h"

// HW Nucleo-STM32F446RE:
#define LD2_PIN 5           /*!< GPIO pin of the LED2 in the Nucleo board */
#define LD2_GPIO_PORT GPIOA /*!< GPIO port of the LED2 in the Nucleo board */

#define MODER5_MASK (GPIO_MODER_MODE0 << LD2_PIN * 2) /*!< Mask for the LED2 in the MODE Register */
#define PUPDR5_MASK (GPIO_PUPDR_PUPD0 << LD2_PIN * 2) /*!< Mask for the LED2 in the PUPD Register */

#define MODER5_AS_OUTPUT (STM32F4_GPIO_MODE_OUT << LD2_PIN * 2) /*!< Output mode for the LED2 in the MODE Register */
#define PUPDR5_AS_NOPUPD (STM32F4_GPIO_PUPDR_NOPULL << LD2_PIN * 2) /*!< No push/pull configuration for the LED2 in the MODE Register */

#define IDR5_MASK (GPIO_IDR_ID0 << LD2_PIN) /*!< Mask for the LED2 in the Input Data Register */
#define ODR5_MASK (GPIO_ODR_OD0 << LD2_PIN) /*!< Mask for the LED2 in the Output Data Register */

//TODO alumnos: modify
void port_led_gpio_setup(void)
{
    /* Primero , habilitamos siempre el reloj de los perifericos */
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN ;
    /* Luego , limpiamos los registros MODER y PUPDR correspondientes */
    LD2_GPIO_PORT -> MODER &= ~ MODER5_MASK ;
    LD2_GPIO_PORT -> PUPDR &= ~ PUPDR5_MASK ;
    /* Finalmente , configuramos el LED como salida sin pull up/ pull down */
    LD2_GPIO_PORT -> MODER |= MODER5_AS_OUTPUT ;
    LD2_GPIO_PORT -> PUPDR |= PUPDR5_AS_NOPUPD ;
}

//TODO alumnos: modify
bool port_led_get(void)
{
    return (LD2_GPIO_PORT->IDR & IDR5_MASK) != 0; // Return the state of the LED, which is the value of the IDR register
}

//TODO alumnos: modify
void port_led_on(void)
{
    LD2_GPIO_PORT->ODR |= ODR5_MASK; // Set the corresponding bit in the ODR register by writing a logic 1  
}

//TODO alumnos: modify
void port_led_off(void)
{
    LD2_GPIO_PORT->ODR &= ~ODR5_MASK; // Clear the corresponding bit in the ODR register by writing a logic 0
}

//TODO alumnos: modify
void port_led_toggle(void)
{
    if (port_led_get())
    {
        printf("[t = \%ld]\tLED OFF\n", port_system_get_millis());
        port_led_off();
    }
    else
    {
        printf("[t = \%ld]\tLED ON\n", port_system_get_millis());
        port_led_on();
    }
}
