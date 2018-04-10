/*
 * output.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "output.h"

OutputModule::OutputModule(uint8_t id) : Module(id, "OUT", NULL, 0,1,0,0) {
	inputs = new uint8_t[1];
}

uint8_t		OutputModule::spStream(AudioStream **arrStore)
{
	arrStore[0] = new AudioOutputI2S();
	return 1;
}

uint8_t		OutputModule::spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

uint8_t		OutputModule::spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	return 0;
}

OutputModule::~OutputModule() {
	delete[] inputs;
}

