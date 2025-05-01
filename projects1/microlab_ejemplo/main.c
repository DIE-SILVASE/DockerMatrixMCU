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
    while(1);
}
