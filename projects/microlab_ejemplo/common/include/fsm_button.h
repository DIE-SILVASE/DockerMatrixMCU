/**
 * @file fsm_button.h
 * @brief Header for fsm_button.c file.
 * @author Román Cárdenas, Alberto Boscá, Josué Pagán (r.cardenas@upm.es, j.pagan@upm.es, alberto.bosca@upm.es)
 * @date 2025-01-22
 */
#ifndef FSM_BUTTON_H_
#define FSM_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include <fsm.h>

/* Defines -------------------------------------------------------------------*/


/* Typedefs ------------------------------------------------------------------*/

typedef struct fsm_button_t fsm_button_t;

/* Function prototypes and documentation ---------------------------------------*/

/**
 * @brief it returns the latest duration measured by the button FSM.
 *
 * > **TODO alumnos:**
 * >
 * > ✅ Return the value of the duration counter
 *
 * @param p_fsm_button pointer to the button FSM.
 * @return uint32_t amount of time (in ms) that the button has been pressed.
 */
uint32_t fsm_button_get_duration(fsm_button_t *p_fsm_button);

/**
 * @brief It sets the duration measured by the button FSM to 0.
 * 
 * > **TODO alumnos:**
 * >
 * > ✅ Set duration counter to 0
 *
 * @param p_fsm_button pointer to the button FSM.
 */
void fsm_button_reset_duration(fsm_button_t *p_fsm_button);

/**
 * @brief Creates a new FSM for measuring how long the button is pressed.
 *
 * @note this function uses malloc to save memory space in the heap for the FSM.
 * @note If you are done with the FSM, you must call fsm_button_destroy to free memory.
 *
 * @param debounce_time time (in ms) the FSM will wait in intermediate steps to avoid mechanical glitches.
 *
 * @return pointer to the button FSM.
 */
fsm_button_t * fsm_button_new(uint32_t debounce_time);

/**
 * @brief Destroys the FSM for the button of the board.
 *
 * @note This function uses free to release memory space in the heap for the FSM.
 *
 * @param p_fsm_button pointer to the button FSM.
 */
void fsm_button_destroy(fsm_button_t *p_fsm_button);

/**
 * @brief traverses the button FSM transition table and executes the first transition whose guard condition is true.
 * 
 * @param p_fsm_button pointer to the button FSM.
 */
void fsm_button_fire(fsm_button_t *p_fsm_button);

#endif // FSM_BUTTON_H_
