/*
 * state_menu_tune.h
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_MENU_TUNE_H_
#define STATE_MENU_TUNE_H_

#include "model_module.h"
#include "state_menu.h"

class TuneMenuState : public MenuState {
public:
	TuneMenuState(StateManager *mgr, Module *m);
	void isetup();
	void iloop();
	~TuneMenuState();
protected:
	Module *m;
};

#endif /* STATE_MENU_TUNE_H_ */
