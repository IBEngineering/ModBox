/*
 * state_menu_tune.cpp
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#include "state_menu_tune.h"

TuneMenuState::TuneMenuState(StateManager *mgr, Model *model) : MenuState(mgr, "Tune Menu")
{
	this->model = model;
	this->m = NULL;
}

void TuneMenuState::isetup()
{
	uint8_t i;

	menu->push(m->getName());
	for(i = 0; i < m->getValueCount(); i++)
	{
		const char *name = m->getValueNames()[i];
		menu->pushAny(name, m->getValues()[i]);
	}
}

void TuneMenuState::iloop() {}

void TuneMenuState::updateForValue(uint8_t i)
{
	disp->setCursor(5,5);
	disp->printf("ut%d", i);

	model->updateForValue(m, i);
}

void TuneMenuState::setModule(Module *m)
{
	this->m = m;
}

TuneMenuState::~TuneMenuState() {
}

