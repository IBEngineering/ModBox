/*
 * state_mgr.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#include "state_mgr.h"

StateManager::StateManager(uint8_t size,
		EncoderCapsule *encc1, EncoderCapsule *encc2,
		EncoderCapsule *encc3, EncoderCapsule *encc4,
		GDISPLAY *disp)
{
	states			= new ProgramState*[size];
	currI			= 0;	// Per default starts at 0
	uptime			= 0;
	this->size		= size;
	this->encc1		= encc1;
	this->encc2		= encc2;
	this->encc3		= encc3;
	this->encc4		= encc4;
	this->disp		= disp;

	// Nullify states to break
	for(int i = 0; i < size; i++)
	{
		states[i] = NULL;
	}
}

elapsedMillis StateManager::getUptime()
{
	return uptime;
}

void StateManager::resetUptime()
{
	uptime = 0;
}

result_t StateManager::setState(uint8_t i, ProgramState *state)
{
	if(i >= size)							return OUT_OF_BOUNDS;
	if(states[currI] != NULL && i == currI)	return STATE_MGR_ACTIVE;

	states[i] = state;
	uptime = 0;

	return SUCCESS;
}

void StateManager::setCurrentState(uint8_t state)
{
	if(state >= size)	return;
	this->currI = state;
	resetUptime();
	disp->clearBuffer();
	states[currI]->setup();
}

void		StateManager::setup()							{states[currI]->setup();}
void		StateManager::loop()							{states[currI]->loop();}
result_t	StateManager::onAnything()						{return states[currI]->onAnything();}
result_t	StateManager::onScrollPri(uint8_t f, int16_t v)	{return states[currI]->onScrollPri(f,v);}
result_t	StateManager::onScrollSec(uint8_t f, int16_t v)	{return states[currI]->onScrollSec(f,v);}
result_t	StateManager::onConfirm(uint8_t f)				{return states[currI]->onConfirm(f);}
result_t	StateManager::onReturn(uint8_t f)				{return states[currI]->onReturn(f);}

StateManager::~StateManager() {
	delete[] states;	// Delete the ProgramState*s
}

