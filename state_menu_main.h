/*
 * state_menu_main.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_MENU_MAIN_H_
#define STATE_MENU_MAIN_H_

#include "state_menu.h"

class MainMenuState : public MenuState {
public:
	MainMenuState(StateManager *mgr);
	result_t onAnything();
	result_t onConfirm(uint8_t flag);
	~MainMenuState();
private:
	void isetup();
	void iloop();
};

#endif /* STATE_MENU_MAIN_H_ */
