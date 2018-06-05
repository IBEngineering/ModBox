/*
 * state_menu_tune.h
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_MENU_TUNE_H_
#define STATE_MENU_TUNE_H_

#include "model_model.h"
#include "model_module.h"
#include "state_menu.h"

class TuneMenuState : public MenuState {
public:
	TuneMenuState(StateManager *mgr, Model *model);
	void setModule(Module *m);
	~TuneMenuState();
protected:
	Module *m;
	Model *model;

	void isetup();
	void iloop();
	void updateForValue(uint8_t i);
};

#endif /* STATE_MENU_TUNE_H_ */
