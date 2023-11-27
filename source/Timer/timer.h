#ifndef LILEN_TIMER_H
#define LILEN_TIMER_H

#include "../../LilEn.h"

/* ================================================================ */

struct timer {

	/* Last frame end time in ticks */
	uint64_t pt;

	/* Delta time between two frames */
	float d;

	/* Accumulator */
	float acc;

	/* The variable can be used to specify the amount of time to wait before executing a particular action */
	float time;
};

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Dynamically allocate a new instance of a `Timer_t` type.
*/
extern Timer_t Timer_new(void);

/* ================================ */

/**
 * Destroy a timer `t` of type `Timer_t` and data associated with it. Deallocate memory occupied by a timer `t`.
*/
extern void Timer_destroy(Timer_t* t);

/* ================================ */

/**
 * Set a timer. Call then `Timer_is_ready` to check if the specified time has passed
*/
extern int Timer_set(const Timer_t t, float v);

/* ================================ */

/**
 * Check if the specified amount of time has passed.
*/
extern int Timer_is_ready(const Timer_t t);

/* ================================ */

/**
 * Reset the timer. Make it count seconds again.
*/
extern int Timer_reset(const Timer_t t);

/* ================================ */

/**
 * Update a timer
*/
extern void Timer_tick(const Timer_t t);

/* ================================================================ */

#endif /* LILEN_TIMER_H */