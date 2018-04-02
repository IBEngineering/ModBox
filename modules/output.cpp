/*
 * output.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "output.h"

OutputModule::OutputModule() {
	audioStream = new AudioOutputI2S();
	values = NULL;
}

const char	*getName()			{return "OUT";}
const char	**getValueNames()	{return NULL;}
uint8_t		getValueCount()		{return 0;}
uint8_t		getInputCount()		{return 1;}
uint8_t		getOutputCount()	{return 0;}
uint8_t		getParalsCount()	{return 0;}

OutputModule::~OutputModule() {
	delete audioStream;
}

