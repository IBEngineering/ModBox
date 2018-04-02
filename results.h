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


typedef enum {

	// Program State


	// State Manager
	STATE_MGR_OUT_OF_BOUNDS = -4,
	STATE_MGR_CURRENTLY_ACTIVE = -3,

	// Events
	EVENT_FAILED = -2,

	// Generics
	UNIMPLEMENTED = -1,

	// Success
	SUCCESS = 0,
	EVENT_IGNORED = 0,

	// Events
	EVENT_CONSUMED = 1,


} result_t;


#endif /* RESULTS_H_ */
