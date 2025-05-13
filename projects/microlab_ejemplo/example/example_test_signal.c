#include "port_pwm_signal.h" // Biblioteca para configurar y manejar señales PWM
#include "port_input.h"      // Biblioteca para configurar y manejar captura de entrada
#include "port_system.h"     // Biblioteca para inicialización y utilidades del sistema
#include <stdio.h>


int main(void)
{
    port_system_init(); // Inicializa el sistema, configurando periféricos básicos como el reloj y las interrupciones

    // 1. Configurar PWM de prueba usando TIM5 en PA0
    port_pwm_signal_gpio_setup();  // Configura el pin PA0 como salida para la señal PWM
    port_pwm_signal_timer_setup(); // Configura el temporizador TIM5 para generar la señal PWM
    port_pwm_signal_start();       // Inicia el temporizador para comenzar a generar la señal PWM

    // 2. Configurar Input Capture en PA5
    port_input_gpio_setup();  // Configura el pin PA5 como entrada para capturar la señal
    port_input_timer_setup(); // Configura el temporizador para capturar eventos de la señal de entrada
    port_input_start();       // Inicia el temporizador para comenzar a capturar valores

    uint32_t last_capture = 0; // Almacena el último valor capturado por el temporizador
    uint32_t new_capture = 0;  // Almacena el nuevo valor capturado por el temporizador
    uint32_t t = port_system_get_millis(); // Obtiene el tiempo actual en milisegundos para controlar el retardo

    while (1) // Bucle infinito para medir continuamente la señal de entrada
    {
        new_capture = port_input_get_captured_value(); // Obtiene el valor capturado más reciente

        if (new_capture != last_capture) // Si el valor capturado ha cambiado, calcula el período
        {
            uint32_t period_ticks; // Variable para almacenar el período en ticks del temporizador

            if (new_capture > last_capture) // Caso sin desbordamiento del temporizador
                period_ticks = new_capture - last_capture;
            else // Caso con desbordamiento del temporizador
                period_ticks = (0xFFFF - last_capture) + new_capture + 1;

            // Convierte el período de ticks a microsegundos (asumiendo 1 tick = 1 us)
            float period_us = period_ticks;

            // Calcula la frecuencia en Hz como el inverso del período en segundos
            float frequency_hz = 1e6f / period_us;

            // Imprime el período y la frecuencia calculados
            printf("Periodo: %.2f us | Frecuencia: %.2f Hz\n", period_us, frequency_hz);

            last_capture = new_capture; // Actualiza el último valor capturado
        }

        // Introduce un retardo controlado para que el bucle se ejecute cada 10 ms
        port_system_delay_until_ms(&t, 10);
    }
}