    /**
 * @file port_led.h
 * @author Román Cárdenas (r.cardenas@upm.es)
 * @brief Port layer for the LED of the STM32F4 Nucleo board.
 * @date 01-01-2024
 */
#ifndef PORT_PWM_H_
#define PORT_PWM_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>

/* Function prototypes and explanations ---------------------------------------*/

/**
 * @brief Configures the GPIO port connected to the LED.
 * 
 */
void port_pwm_gpio_setup(void);

/**
 * @brief Returns the current state of the LED.
 * 
 * @return true if the LED is on
 * @return false if the LED is off
 */
uint8_t port_pwm_get_dc(void);


/**
 * @brief Returns the current state of the LED.
 * 
 * @return true if the LED is on
 * @return false if the LED is off
 */
void port_pwm_set_dc(uint8_t);


void port_pwm_set_frec(uint32_t);


void port_pwm_get_frec(uint32_t);

void port_pwm_stop(void);

void port_pwm_start(void);

#endif // PORT_LED_H_
