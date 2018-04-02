/*
 * state_menu.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "state_menu.h"

MenuState::MenuState(StateManager *mgr, const char* title) : ProgramState(mgr, title)
{
	menu = new Menu(mgr->disp, title, true);
	needsPush = true;
	needsUpdate = false;
}

void MenuState::setup()
{
	if(needsPush)
	{
		isetup();
		needsPush = false;
	}
	menu->show();
}

void MenuState::loop()
{
	iloop();
}

MenuState::~MenuState()
{
	delete menu;
}

