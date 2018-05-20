/*
 * state_menu_tune.cpp
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#include "state_menu_tune.h"

TuneMenuState::TuneMenuState(StateManager *mgr, Module *m) : MenuState(mgr, "Tune Menu")
{
	this->m = m;
}

void TuneMenuState::isetup()
{
	uint8_t i;

	menu->push(m->getName());
	for(i = 0; i < m->getValueCount(); i++)
	{
		menu->pushAny(m->getValueNames()[i], m->getValues()[i]);
	}
}

void TuneMenuState::iloop() {}

TuneMenuState::~TuneMenuState() {
}

