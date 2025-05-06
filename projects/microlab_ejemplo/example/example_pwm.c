#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "port_system.h"
#include "port_pwm.h"
#include "fsm_button.h"
#include "stm32f4_button.h"

#define T_DEBOUNCE_MS 200    // Button debounce time
#define MIN_DURATION_MS 1000 // Minimum button duration time
#define T_FSM_MS 10          // Trigger period of the FSM
#define CHANGE_MODE_BUTTON_TIME 1000 // time in ms to change mode (long press)

int main()
{
    port_system_init();
    port_pwm_gpio_setup();
    // cada vez qye pulso el boton cambio duty
    // Create the button FSM

    fsm_button_t *p_fsm_button = fsm_button_new(T_DEBOUNCE_MS);

    int duty_cycle = 0;    

        while (1)
        {
            
                fsm_button_fire(p_fsm_button);
                uint32_t duration = fsm_button_get_duration(p_fsm_button);
                if (duration > 0)
                {
                    
                    printf("Button %d pressed for %ld ms", BUTTON_0_ID, duration);
                    // If the button is pressed for more than CHANGE_MODE_BUTTON_TIME, we toggle the LED
                    if (duration >= CHANGE_MODE_BUTTON_TIME)
                    {   //como hago para que duty_cycle sea un valor entre 0 y 100?
                        duty_cycle= (duty_cycle + 25) % 101;
                        port_pwm_set_dc(duty_cycle);
                        printf(" (long press detected)");
                        printf(" (duty cycle: %d)", duty_cycle);
                    }
                    printf("\n");
                    // We always reset the duration after reading it
                    fsm_button_reset_duration(p_fsm_button);
                }
            
        }
        // In every iteration, we fire the FSM and retrieve the duration of the button press

    // We should never reach this point
    fsm_button_destroy(p_fsm_button);
    return 0;
}
