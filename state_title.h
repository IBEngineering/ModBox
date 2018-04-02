/*
 * state_title.h
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_TITLE_H_
#define STATE_TITLE_H_

#include "state_state.h"

class TitleState : public ProgramState {
public:
	TitleState(StateManager *mgr) : ProgramState(mgr, "TITLE") {};
	void		setup();
	void		loop();
	result_t	onAnything();
	virtual		~TitleState();
protected:
	void		isetup();
	void		iloop();
};

#endif /* STATE_TITLE_H_ */
