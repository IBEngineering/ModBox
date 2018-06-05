/*
 * input.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "input.h"

InputModule::InputModule(uint8_t id) : Module(id, "IN", NULL, 0, 0, 1, 4) {
	outputs = new uint8_t[4]	{0};
}

uint8_t InputModule::spStream(AudioStream **arrStore)
{
	arrStore[0] = new AudioInputI2S();
	return 1;
}

uint8_t InputModule::spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	return 0;
}

uint8_t InputModule::spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 1;
	return 1;
}

void InputModule::updateForValue(AudioStream **arrStore, uint8_t val){}

InputModule::~InputModule() {
	delete[] outputs;
}

