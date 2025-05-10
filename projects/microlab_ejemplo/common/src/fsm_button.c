/**
 * @file fsm_button.c
 * @brief Button FSM main file.
 * @author Román Cárdenas, Alberto Boscá, Josué Pagán (r.cardenas@upm.es, j.pagan@upm.es, alberto.bosca@upm.es)
 * @date 2024-01-01
 */
/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stddef.h>
#include <stdlib.h>

/* HW dependent includes */
#include "port_button.h"
#include "port_system.h"

/* Other includes */
#include "fsm_button.h"

/**
 * @brief Button FSM state enumeration
 */
enum FSM_BUTTON_STATES
{
    BUTTON_RELEASED,
    BUTTON_RELEASED_WAIT,
    BUTTON_PRESSED,
    BUTTON_PRESSED_WAIT,
};

/**
 * @brief Button FSM structure 
 * 
 */
struct fsm_button_t
{
    fsm_t fsm;              /*!< Internal FSM from the library */
    uint32_t debounce_time; /*!< Button debounce time in ms */
    uint32_t next_timeout;  /*!< Next timeout for the debounce in ms */
    uint32_t tick_pressed;  /*!< Number of system ticks when the button was pressed */
    uint32_t duration;      /*!< How much time the button has been pressed */
};

/* State machine input or transition functions */
/**
 * @brief checks if the button is released.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Read and return the button state
 *
 * @param p_fsm pointer to the button FSM
 * @return true if the button is realeased; false otherwise.
 */
static bool check_button_released(fsm_t *p_fsm)
{
    return port_button_read();
}

/**
 * @brief checks if the button is pressed.
 *
 * @note it is the opposite to check_button_released
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Return the opposite to check_button_released
 *
 * @param p_fsm pointer to the button FSM
 * @return true if the button is pressed; false otherwise.
 */
static bool check_button_pressed(fsm_t *p_fsm)
{
    return !check_button_released(p_fsm);
}

/**
 * @brief checks if the debounce time has passed.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Cast pointer to button FSM \n
 * > ✅ 2. get current system time \n
 * > ✅ 3. check if the current time is greater than the last debounce timeout \n
 *
 * @param p_fsm pointer to the button FSM
 * @return true if the current system time is greater than the last debounce timeout.
 */
static bool check_timeout(fsm_t *p_fsm)
{
    fsm_button_t *p_button = (fsm_button_t *) p_fsm;
    uint32_t now = port_system_get_millis();
    return now > p_button->next_timeout;
}

static void do_store_tick_pressed(fsm_t *p_fsm)
{
    fsm_button_t *p_fsm_button = (fsm_button_t *) p_fsm;
    uint32_t now = port_system_get_millis();

    p_fsm_button->tick_pressed = now;
    p_fsm_button->next_timeout = now + p_fsm_button->debounce_time;
}

static void do_set_duration(fsm_t *p_fsm)
{
    fsm_button_t *p_fsm_button = (fsm_button_t *) p_fsm;
    uint32_t now = port_system_get_millis();

    p_fsm_button->duration = now - p_fsm_button->tick_pressed;
    p_fsm_button->next_timeout = now + p_fsm_button->debounce_time;
}

/**
 * @brief Button FSM transition table
 *
 * > **TODO alumnos:**
 * >
 * > ✅ 1. Define the FSM's transitions. \n
 * > ✅ 2. Add a null transition (this is mandatory for all the FSMs).
 *
 */
static fsm_trans_t fsm_trans_button[] = {
    {BUTTON_RELEASED, check_button_pressed, BUTTON_PRESSED_WAIT, do_store_tick_pressed},
  {BUTTON_PRESSED_WAIT, check_timeout, BUTTON_PRESSED, NULL},
  {BUTTON_PRESSED, check_button_released, BUTTON_RELEASED_WAIT, do_set_duration},
  {BUTTON_RELEASED_WAIT, check_timeout, BUTTON_RELEASED, NULL},
  {-1, NULL, -1, NULL}
};

/* FSM public functions */

uint32_t fsm_button_get_duration(fsm_button_t *p_fsm_button)
{
    return p_fsm_button->duration;
}

void fsm_button_reset_duration(fsm_button_t *p_fsm_button)
{
    p_fsm_button->duration = 0;
}

static void fsm_button_init(fsm_button_t *p_fsm_button, uint32_t debounce_time)
{
    fsm_init(&p_fsm_button->fsm, fsm_trans_button);
    p_fsm_button->debounce_time = debounce_time;
    p_fsm_button->tick_pressed = 0;
    p_fsm_button->duration = 0;
    port_button_gpio_setup(); /*  Inicializa el HW del boton */
}


fsm_button_t *fsm_button_new(uint32_t debounce_time)
{
    fsm_button_t *p_fsm_button = malloc(sizeof(fsm_button_t));
    if (p_fsm_button)
    {
        fsm_button_init(p_fsm_button, debounce_time);
    }
    return p_fsm_button;
}

void fsm_button_destroy(fsm_button_t *p_fsm_button)
{
    free(p_fsm_button);
}

void fsm_button_fire(fsm_button_t *p_fsm_button)
{
    fsm_fire(&p_fsm_button->fsm);
}
