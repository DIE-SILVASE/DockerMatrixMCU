#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "port_system.h"
#include "port_input.h"

#define T_FSM_MS 10 // FSM tick cada 10 ms

int main() {
    // Inicializar sistema
    port_system_init();

    // Inicializar GPIO y Timer en modo Input Capture
    port_input_gpio_setup();
    port_input_timer_setup();
    port_input_start();

    uint32_t last_capture = 0;
    uint32_t new_capture = 0;
    uint32_t t = port_system_get_millis();

    while (1)
    {
        // Leer captura actual
        new_capture = port_input_get_captured_value();

        // Si hay una nueva captura diferente
        if (new_capture != last_capture)
        {
            uint32_t period_ticks;
            if (new_capture > last_capture)
                period_ticks = new_capture - last_capture;
            else
                period_ticks = (0xFFFF - last_capture) + new_capture + 1; // Si se reinició el contador

            float period_us = period_ticks; // Con prescaler 1us/tick
            float frequency_hz = 1e6f / period_us;

            printf("Periodo: %.2f us | Frecuencia: %.2f Hz\n", period_us, frequency_hz);

            last_capture = new_capture;
        }

        // FSM delay para no saturar CPU
        port_system_delay_until_ms(&t, T_FSM_MS);
    }

    return 0;
}