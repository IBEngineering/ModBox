/*
 * state.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#include "state_state.h"

ProgramState::ProgramState(StateManager *mgr, const char *title)
{
	this->mgr = mgr;
	this->title = title;

	this->encc1 = mgr->encc1;
	this->encc2 = mgr->encc2;
	this->encc3 = mgr->encc3;
	this->encc4 = mgr->encc4;
	this->disp	= mgr->disp;
}

result_t	ProgramState::onAnything()							{return EVENT_IGNORED;}
result_t	ProgramState::onScrollPri(uint8_t flag, int16_t v)	{return EVENT_IGNORED;}
result_t	ProgramState::onScrollSec(uint8_t flag, int16_t v)	{return EVENT_IGNORED;}
result_t	ProgramState::onConfirm(uint8_t flag)				{return EVENT_IGNORED;}
result_t	ProgramState::onReturn(uint8_t flag)				{return EVENT_IGNORED;}
void		ProgramState::setup()								{}
void		ProgramState::loop()								{}
			ProgramState::~ProgramState()						{}
