/**
 * @file interr.c
 * @brief Interrupt service routines for the STM32F4 platform.
 * @author Román Cárdenas (r.cardenas@upm.es)
 * @date 2024-01-01
 */
// Include headers of different port elements:
#include "stm32f4xx.h"
#include "port_system.h"
#include "port_button.h"
#include "stm32f4_button.h"
#define BIT13_MASK 0x2000  /*!<Mask to select de bit 13 of the reister EXTI-> PR*/

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief This function handles the System tick timer that increments the system millisecond counter.
 *
 * > **TODO alumnos:**
 * >
 * > ✅ 1. **Increment the System tick counter `msTicks` in 1 count.** 
 *  `msTicks` is a `static volatile` variable declared in @link port_system.c @endlink. \n
 * Use set and get functions from port_system.c in order to modify it.
 *
 * @warning **The variable `msTicks` must be declared volatile!** Just because it is modified in this ISR, in order to avoid [*race conditions*](https://en.wikipedia.org/wiki/Race_condition)
. **Add it to the definition** after *static*.
 * 
 */
void SysTick_Handler(void)
{
    port_system_set_millis(port_system_get_millis() + 1);
}


// /**
//  * @brief This function handles Px10-Px15 global interrupts.
//  * 
//  *        First, this function identifies the line/ pin which has raised the interruption. 
//  *        Then, perform the desired action. Before leaving it cleans the interrupt pending register.
//  * 
//  */
// void EXTI15_10_IRQHandler(void)
// {
//     /*ISR usser button*/
//     // if (EXTI->PR & BIT_POS_TO_MASK(BUTTON_0_PIN))
//     // {
//     //     if (BUTTON_0_GPIO->IDR & BIT_POS_TO_MASK(BUTTON_0_PIN))
//     //     {
//     //         buttons_arr[BUTTON_0_ID].flag_pressed = true;
//     //     }
//     //     else
//     //     {
//     //         buttons_arr[BUTTON_0_ID].flag_pressed = false;
//     //     }
//     // }


//     if (EXTI->PR & BIT_POS_TO_MASK(buttons_arr[BUTTON_0_ID].pin)) /*Making sure the user button is generating the interruption*/
//     { 
//         if (buttons_arr[BUTTON_0_ID].p_port->IDR & BIT_POS_TO_MASK(buttons_arr[BUTTON_0_ID].pin)) {
//             // Rising edge
//             buttons_arr[BUTTON_0_ID].flag_pressed = false;
//         } else {
//             // Falling edge
//             buttons_arr[BUTTON_0_ID].flag_pressed = true;
//         }
        
//     }
//     EXTI->PR |=  BIT13_MASK; /*Cleans flag*/
//}