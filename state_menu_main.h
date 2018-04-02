/*
 * state_menu_main.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_MENU_MAIN_H_
#define STATE_MENU_MAIN_H_

#include "state_menu.h"

class MainMenuState: public MenuState {
public:
	MainMenuState(StateManager *mgr);
	result_t onAnything();
	result_t onScrollPri(uint8_t flag, int16_t v);
	~MainMenuState();
private:
	void isetup();
	void iloop();
};

#endif /* STATE_MENU_MAIN_H_ */
