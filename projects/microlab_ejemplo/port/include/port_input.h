/**
 * @file port_input.h
 * @author Tu Nombre
 * @brief Port layer for Input Capture mode (STM32F4 Nucleo board).
 * @date 04-04-2025
 */

	#ifndef PORT_INPUT_H_
	#define PORT_INPUT_H_
	
	/* Includes ------------------------------------------------------------------*/
	#include <stdint.h>
	
	/* Function prototypes ------------------------------------------------------*/
	
	/**
		* @brief Configures the GPIO pin for Input Capture (Alternate Function).
		*/
	void port_input_gpio_setup(void);
	
	/**
		* @brief Configures the Timer for Input Capture mode.
		*/
	void port_input_timer_setup(void);
	
	/**
		* @brief Starts the Timer in Input Capture mode.
		*/
	void port_input_start(void);
	
	/**
		* @brief Stops the Timer in Input Capture mode.
		*/
	void port_input_stop(void);
	
	/**
		* @brief Returns the last captured value (value of CCR).
		* 
		* @return Captured timer value.
		*/
	uint32_t port_input_get_captured_value(void);
	
	#endif // PORT_INPUT_H_