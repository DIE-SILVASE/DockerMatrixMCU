#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "port_system.h"
#include "fsm_led.h"
#include "fsm_button.h"

#define T_DEBOUNCE_MS 200 // Button debounce time
#define MIN_DURATION_MS 1000 // Minimum button duration time
#define T_FSM_MS 10   // Trigger period of the FSM

int main() {
    port_system_init();
    fsm_button_t *p_fsm_button = fsm_button_new(T_DEBOUNCE_MS);
    fsm_led_t *p_fsm_led = fsm_led_new(p_fsm_button, MIN_DURATION_MS);
    uint32_t t = port_system_get_millis();
    while (1)
    {
        fsm_led_fire(p_fsm_led);
        port_system_delay_until_ms(&t, T_FSM_MS);
    }
    fsm_led_destroy(p_fsm_led);    // limpiamos memoria...
    return 0;         // Y devolvemos 0 para indicar que todo ha ido bien
}
