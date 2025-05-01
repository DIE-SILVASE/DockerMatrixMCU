#ifndef FSM_BLINK_H_
#define FSM_BLINK_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>

/* Other includes */
#include <fsm.h>

/* Typedefs --------------------------------------------------------------------*/
/**
 * @enum FSM_BLINK_STATES
 * @brief Blink FSM state enumeration
 */
enum FSM_BLINK_STATES
{
    IDLE, /*!< Idle state */
};

/* Typedefs --------------------------------------------------------------------*/

/* Opaque structure for the blink FSM: we know the structure exists, but not what it contains */
typedef struct fsm_blink_t fsm_blink_t;

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Creates a new FSM for blinking the LED of the board.
 *
 * @note This function uses malloc to save memory space in the heap for the FSM.
 * @note If you are done with the FSM, you must call fsm_destroy to free memory.
 *
 * @param period_ms period (in ms) of the LED blink.
 *
 * @return fsm_t* pointer to the LED FSM.
 */
fsm_blink_t * fsm_blink_new(uint32_t period_ms);

/**
 * @brief Destroys the FSM for blinking the LED of the board.
 *
 * @note This function uses free to release memory space in the heap for the FSM.
 *
 * @param p_fsm_blink pointer to the blink FSM.
 */
void fsm_blink_destroy(fsm_blink_t *p_fsm_blink);

/**
 * @brief traverses the blink FSM transition table and executes the first transition whose guard condition is true.
 * 
 * @param p_fsm_blink pointer to the blink FSM.
 */
void fsm_blink_fire(fsm_blink_t *p_fsm_blink);

#endif // FSM_BLINK_H_
