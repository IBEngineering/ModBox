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

result_t MenuState::onScrollPri(uint8_t flag, int16_t v)
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

result_t MenuState::onScrollSec(uint8_t flag, int16_t v)
{
	if(v == 0)	return EVENT_IGNORED;

	uint8_t i = menu->getFocus();
	int s = (flag==0) ? 1 : 10;

	if(menu->getItemType(i) == TEXT)
	{
		return EVENT_CONSUMED;	// This terminates the function without updating values
	}
	else if(menu->getItemType(i) == ItemType::VALUE_BOUNDED)
	{
		BoundedValue *val = (BoundedValue *)menu->getValue(i);
		(v>0)? *(val) += s : *(val) -= s;
	}
	else if(menu->getItemType(i) == ItemType::VALUE_ENUM)
	{
		EnumValue *val = (EnumValue *)menu->getValue(i);
		(v>0)? *(val) += s : *(val) -= s;
	}

	disp->setCursor(5,5);
	disp->printf("um%d", i);

	/*
	 * TODO: the -1 is here because the first item
	 * in the menu is the temporary title of the
	 * module. Make a way to modify the actual title,
	 * remove the title item, and remove this -1
	 */
	updateForValue(i-1);
	menu->updateItem(i);

	return EVENT_CONSUMED;
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

