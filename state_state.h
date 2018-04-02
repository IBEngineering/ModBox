/*
 * state.h
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_STATE_H_
#define STATE_STATE_H_

#include "gui.h"
#include "hardware.h"
#include "state_mgr.h"
#include "results.h"

/**
 * Forward Declaration
 */
class StateManager;

#define R_STATE_EVENT_CONSUMED	1

class ProgramState {
public:
	ProgramState(StateManager *stateManager, const char *title);

	// Type-custom lifetime
	virtual void		setup() =0;
	virtual void		loop() =0;

	// Events,
	virtual result_t	onAnything();
	virtual result_t	onScrollPri(uint8_t flag, int16_t v);
	virtual result_t	onScrollSec(uint8_t flag, int16_t v);
	virtual result_t	onConfirm(uint8_t flag);
	virtual result_t	onReturn(uint8_t flag);

	virtual ~ProgramState();
protected:
	StateManager	*mgr;
	const char		*title;
	EncoderCapsule	*encc1;
	EncoderCapsule	*encc2;
	EncoderCapsule	*encc3;
	EncoderCapsule	*encc4;
	GDISPLAY		*disp;

	// Class-custom lifetime
	/**
	 * 'Internal setup':
	 * a setup routine specific to the state.
	 * Should only be extended in a non-extended class.
	 */
	virtual void isetup()	=0;
	/**
	 * 'Internal loop':
	 * a loop routine specific to the state.
	 * Should only be extended in a non-extended class.
	 */
	virtual void iloop()	=0;
};

#endif /* STATE_STATE_H_ */
