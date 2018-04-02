/*
 * input.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "input.h"

InputModule::InputModule() {
	audioStream = new AudioInputI2S();
	values = NULL;
}

const char	*InputModule::getName()				{return "IN";}
const char	**InputModule::getValueNames()		{return NULL;}
uint8_t		InputModule::getValueCount()		{return 0;}
uint8_t		InputModule::getInputCount()		{return 0;}
uint8_t		InputModule::getOutputCount()		{return 1;}
uint8_t		InputModule::getParalsCount()		{return 4;}

InputModule::~InputModule() {
	delete audioStream;
}

