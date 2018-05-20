/*
 * state_menu.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_MENU_H_
#define STATE_MENU_H_

#include "gui.h"
#include "state_state.h"

class MenuState : public ProgramState {
public:
	MenuState(StateManager *mgr, const char *title);
	result_t onScrollPri(uint8_t flag, int16_t v);
	result_t onScrollSec(uint8_t flag, int16_t v);
	void setup();
	void loop();
	~MenuState();
protected:
	virtual void isetup() =0;
	virtual void iloop() =0;
	Menu *menu;
	bool needsPush;
	bool needsUpdate;
};

#endif /* STATE_MENU_H_ */
