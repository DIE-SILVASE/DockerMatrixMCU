/**
 * @file fsm_blink.c
 * @brief Blink LED FSM main file.
 * @author Román Cárdenas, Alberto Boscá, Josué Pagán (r.cardenas@upm.es, j.pagan@upm.es, alberto.bosca@upm.es)
 * @date 2025-01-22
 */
/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdlib.h> 

/* HW dependent includes */
#include "port_system.h"
#include "port_led.h"

/* Other includes */
#include "fsm_blink.h"

/**
 * @brief Estructura de la máquina de estados para hacer parpadear el LED.
 *
 * Al contrario que en Java o Python, C no implementa un mecanismo de programación orientado a objetos.
 * Por lo tanto, no tenemos ni clases, ni objetos, ni herencia.
 * Sin embargo, podemos usar el patrón de diseño por composición para emular la herencia.
 *
 * Para ello, el primer elemento de la estructura que "hereda" será del tipo de la estructura "padre".
 * En este caso, nuestra FSM heredaría de la estructura fsm_t.
 *
 * Como el primer elemento de nuestra estructura es del tipo fsm_t,
 * podemos tratar punteros a estructuras fsm_blink_t como si fuesen punteros a estructuras fsm_t.
 * De este modo, podemos hacer uso de las funciones de fsm_t con un puntero del tipo `fsm_blink_t`.
 */
struct fsm_blink_t
{
    fsm_t fsm;          //!< inner FSM. It must be the first element so we can use composition.
    uint32_t period_ms; //!< LED toggling period.
    uint32_t last_time; //!< Auxiliary variable to know when was the last time the LED toggled.
};

/* State machine input or transition functions */
/**
 * @brief Checks if the LED must toggle.
 *
 * @param p_fsm pointer to the blink FSM.
 *
 * TODO alumnos:
 * >
 * > ✅ 1. Cast the generic FSM pointer to blink FSM pointer \n
 * > ✅ 2. Check if current system time is greater than or equal to the FSM's last time + half of its period
 *
 * @return true if the LED must toggle, false otherwise
 */
static bool check_timeout(fsm_t *p_fsm)
{
    fsm_blink_t *p_blink = (fsm_blink_t *) p_fsm;
    return port_system_get_millis() >= p_blink->last_time + p_blink->period_ms / 2;
}

/* State machine output or action functions */
/**
 * @brief Toggles the LED
 *
 * @param p_fsm pointer to the blink FSM.
 *
 * > TO-DO alumnos:
 * >
 * > ✅ 1. Cast the generic FSM pointer to blink FSM pointer \n
 * > ✅ 2. Update FSM's last time to current system time \n
 * > ✅ 3. Toggle the LED using the right system function.
 *
 */
static void do_toggle(fsm_t *p_fsm)
{
    fsm_blink_t *p_blink = (fsm_blink_t *) p_fsm;
    p_blink->last_time = port_system_get_millis(); 
    port_led_toggle();
}


/**
 * @brief Blink FSM transition table
 *
 * > TODO alumnos:
 * >
 * > ✅ 1. Define the FSM's only transition for toggling the LED. \n
 * > ✅ 2. Add a null transition (this is mandatory for all the FSMs).
 *
 */
static fsm_trans_t fsm_blink_tt[] = {
    {IDLE, check_timeout, IDLE, do_toggle},
    {-1, NULL, -1, NULL},
};

static void fsm_blink_init(fsm_blink_t *p_fsm_blink, uint32_t period_ms)
{
    fsm_init(&p_fsm_blink->fsm, fsm_blink_tt);
    
    p_fsm_blink->last_time = port_system_get_millis();
    p_fsm_blink->period_ms = period_ms;
    port_led_gpio_setup(); // configuro el pin GPIO del LED
}

fsm_blink_t *fsm_blink_new(uint32_t period_ms)
{
    fsm_blink_t *p_fsm = (fsm_blink_t *)malloc(sizeof(fsm_blink_t));
    if (p_fsm)
    {
        fsm_blink_init(p_fsm, period_ms);
    }
    return p_fsm;
}

void fsm_blink_destroy(fsm_blink_t *p_fsm_blink)
{
    free(p_fsm_blink);
}

void fsm_blink_fire(fsm_blink_t *p_fsm_blink)
{
    fsm_fire(&p_fsm_blink->fsm);
}
