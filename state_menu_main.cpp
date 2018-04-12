/*
 * state_menu_main.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "state_menu_main.h"
#include "value_bounded.h"

static BoundedValue bval(0.0f, 0.1f, 440.0f);

MainMenuState::MainMenuState(StateManager *mgr) : MenuState(mgr, "Main Menu")
{

}

result_t MainMenuState::onAnything()
{
	mgr->resetUptime();
	return EVENT_IGNORED;
}

result_t MainMenuState::onScrollPri(uint8_t flag, int16_t v)
{
	result_t r = NULL_POINTER;
	if(v == 0)	return EVENT_IGNORED;
	if(v > 0)
	{
		r = menu->setFocus(menu->getFocus() + 1);
	}
	else if(menu->getFocus() > 0)	// && v < 0
	{
		r = menu->setFocus(menu->getFocus() - 1);
	}
	if(r == SUCCESS)	needsUpdate = true;
	return EVENT_CONSUMED;
}

result_t MainMenuState::onConfirm(uint8_t flag)
{
	if(menu->getFocus() == 2)
	{
		mgr->setCurrentState(2);
	}
	return SUCCESS;
}

void MainMenuState::isetup()
{
	menu->push("Display");
	menu->push("Tuner");
	menu->push("Editor");
}

void MainMenuState::iloop()
{
	if(needsUpdate)
	{
		menu->update();
		needsUpdate = false;
		return;
	}

	if(mgr->getUptime() >= 5000)
	{
		mgr->setCurrentState(0);	// TitleState
	}
}

MainMenuState::~MainMenuState() {

}

