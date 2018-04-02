/*
 * results.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef RESULTS_H_
#define RESULTS_H_


/*
 * Order of importance of sub-libraries:
 * - Generics
 * - Events
 * - GUI
 * - State Manager
 * - Program State
 * - Abstract States
 * - Final States
 */

// TODO: think of a good way to organize this
// TODO: organize this

typedef enum {

	// Program State


	// State Manager
	STATE_MGR_OUT_OF_BOUNDS = -5,	// not really necessary anymore
	STATE_MGR_CURRENTLY_ACTIVE = -4,

	// Events
	EVENT_FAILED = -3,

	// Generics
	UNIMPLEMENTED = -2,
	OUT_OF_BOUNDS = -1,

	// Success
	SUCCESS = 0,
	EVENT_IGNORED = 0,

	// Events
	EVENT_CONSUMED = 1,


} result_t;


#endif /* RESULTS_H_ */
