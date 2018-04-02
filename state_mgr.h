/*
 * state_mgr.h
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_MGR_H_
#define STATE_MGR_H_

#include "gui.h"
#include "hardware.h"
#include "results.h"
#include "state_state.h"

class ProgramState;

class StateManager {
public:
	EncoderCapsule	*encc1;
	EncoderCapsule	*encc2;
	EncoderCapsule	*encc3;
	EncoderCapsule	*encc4;
	GDISPLAY		*disp;

	ProgramState	**states;

	StateManager(uint8_t size,
			EncoderCapsule *encc1, EncoderCapsule *encc2,
			EncoderCapsule *encc3, EncoderCapsule *encc4,
			GDISPLAY *disp);

	elapsedMillis getUptime();
	void resetUptime();
	result_t setState(uint8_t i, ProgramState *state);
	void setCurrentState(uint8_t state);

	// Pass functions
	void		setup();
	void		loop();
	result_t	onAnything();
	result_t	onScrollPri(uint8_t flag, int16_t v);
	result_t	onScrollSec(uint8_t flag, int16_t v);
	result_t	onConfirm(uint8_t flag);
	result_t	onReturn(uint8_t flag);



	~StateManager();
private:
	uint8_t			currI;
	elapsedMillis	uptime;
	uint8_t			size;
};

#endif /* STATE_MGR_H_ */
