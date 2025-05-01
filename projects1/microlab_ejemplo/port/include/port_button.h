/**
 * @file port_button.h
 * @brief Header for port_button.c file.
 * @author Román Cárdenas, Alberto Boscá, Josué Pagán (r.cardenas@upm.es, j.pagan@upm.es, alberto.bosca@upm.es)
 * @date 2024-01-01
 */
#ifndef PORT_BUTTON_H_
#define PORT_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdbool.h>

/* HW dependent includes */
#include "port_system.h"

/* Function prototypes and documentation ---------------------------------------*/
/**
 * @brief Configures the GPIO pin of the button.
 *
 * > **TODO alumnos:**
 * >
 * > ✅ 1. Enable GPIOC clock in AHB1ENR \n
 * > ✅ 2. Clean previous configuration for pin 13 in MODER and PUPDR \n
 * > ✅ 2. Set pin 13 mode as input in MODER \n
 * > ✅ 3. Set pull up/down configuration as no PUPD for pin 13 in PUPDR
 *
 */
void port_button_gpio_setup(void);

/**
 * @brief Reads status of the button and returns true if it is pressed.
 *
 * > **TODO alumnos:**
 * >
 * > ✅ 1. Read button value in the corresponding IDR register \n
 *
 * @return true if button is pressed, false otherwise
 */
bool port_button_read(void);


/**
 * @brief Configure the HW specifications of a given button.
 * 
 * @param button_id Button ID. This index is used to select the element of the buttons_arr[] array
 */
void port_button_init(uint32_t button_id);

/**
 * @brief Return the status of the button (pressed or not)
 * 
 * @returns true If the button has been pressed
 * @returns false If the button has not been pressed
 */
bool port_button_is_pressed	(uint32_t button_id);

#endif // PORT_BUTTON_H_
