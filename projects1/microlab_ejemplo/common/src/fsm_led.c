#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fsm.h>
#include "fsm_button.h"
#include "fsm_led.h"
#include "port_led.h"
#include "port_system.h"

enum FSM_LED_STATES {
    IDLE,
};

struct fsm_led_t {
    fsm_t fsm;
    fsm_button_t *p_fsm_button;
    uint32_t min_duration;
};

static bool check_button_duration(fsm_t *p_fsm)
{
    fsm_led_t *p_fsm_led = (fsm_led_t *) p_fsm;
    uint32_t duration = fsm_button_get_duration(p_fsm_led->p_fsm_button);
    return duration >= p_fsm_led->min_duration;
}

static void do_toggle(fsm_t *p_fsm)
{
    fsm_led_t *p_fsm_led = (fsm_led_t *)p_fsm;
    fsm_button_reset_duration(p_fsm_led->p_fsm_button);
    port_led_toggle();
}

static fsm_trans_t fsm_trans_led[] = {
    {IDLE, check_button_duration, IDLE, do_toggle},
    {-1, NULL, -1, NULL}
};

static void fsm_led_init(fsm_led_t *p_fsm_led, fsm_button_t *p_fsm_button, uint32_t min_duration)
{
    fsm_init(&p_fsm_led->fsm, fsm_trans_led);
    p_fsm_led->p_fsm_button = p_fsm_button;
    p_fsm_led->min_duration = min_duration;
    port_led_gpio_setup(); /*  Inicializa el HW del LED */
}

fsm_led_t *fsm_led_new(fsm_button_t *p_fsm_button, uint32_t min_duration)
{
    fsm_led_t *p_fsm_led = malloc(sizeof(fsm_led_t));
    if (p_fsm_led)
    {
        fsm_led_init(p_fsm_led, p_fsm_button, min_duration);
    }
    return p_fsm_led;
}

void fsm_led_destroy(fsm_led_t *p_fsm_led)
{
    fsm_button_destroy(p_fsm_led->p_fsm_button);
    free(p_fsm_led);
}

void fsm_led_fire(fsm_led_t *p_fsm_led)
{
    fsm_button_fire(p_fsm_led->p_fsm_button);
    fsm_fire(&p_fsm_led->fsm);
}
