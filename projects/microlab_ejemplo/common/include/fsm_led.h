#ifndef FSM_LED_H_
#define FSM_LED_H_

#include <stdint.h>
#include <fsm_button.h>

typedef struct fsm_led_t fsm_led_t;

fsm_led_t * fsm_led_new(fsm_button_t *p_fsm_button, uint32_t min_duration);
void fsm_led_destroy(fsm_led_t *p_fsm_led);
void fsm_led_fire(fsm_led_t *p_fsm_led);

#endif // FSM_LED_H_
