/*
 * state_menu_test.h
 *
 *  Created on: Apr 28, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_MENU_TEST_H_
#define STATE_MENU_TEST_H_

#include "state_menu.h"
#include "state_mgr.h"

class TestMenuState : public MenuState {
public:
	TestMenuState(StateManager *mgr);
	result_t onScrollPri(uint8_t flag, int16_t v);
	result_t onScrollSec(uint8_t flag, int16_t v);
	result_t onReturn(uint8_t flag);
	virtual ~TestMenuState();
private:
	void isetup();
	void iloop();
};

#endif /* STATE_MENU_TEST_H_ */
