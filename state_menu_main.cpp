/*
 * state_menu_main.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "state_menu_main.h"
#include "value_bounded.h"

MainMenuState::MainMenuState(StateManager *mgr) : MenuState(mgr, "Main Menu")
{

}

result_t MainMenuState::onAnything()
{
	mgr->resetUptime();
	return EVENT_IGNORED;
}


result_t MainMenuState::onConfirm(uint8_t flag)
{
	switch(menu->getFocus())
	{
	case 1:
		mgr->setCurrentState(2);
		break;
	case 3:
		mgr->setCurrentState(3);
		break;
	}

	return SUCCESS;
}

void MainMenuState::isetup()
{
	menu->push("Display");
	menu->push("Tuner");
	menu->push("Editor");
	menu->push("Test GUI");
}

void MainMenuState::iloop()
{
//	if(needsUpdate)
//	{
//		menu->update();
//		needsUpdate = false;
//		return;
//	}

	if(mgr->getUptime() >= 5000)
	{
		mgr->setCurrentState(0);	// TitleState
	}
}

MainMenuState::~MainMenuState() {

}

