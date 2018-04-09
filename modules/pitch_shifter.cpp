/*
 * pitch_shifter.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "pitch_shifter.h"
#include "../stk_pitch_shift.h"

static const char *valueNames[] = {"shift", };

PitchShifterModule::PitchShifterModule(uint8_t id) : Module(id, "PSH", valueNames, 1,1,1,1) {
	values = new Value*[1];
	values[0] = new BoundedValue(0.0, 0.01, 3.0);

	inputs = new uint8_t[1];
	outputs = new uint8_t[1];
}

uint8_t PitchShifterModule::spStream(AudioStream **arrStore)
{
	StkPitchShift *s = new StkPitchShift(MODULE_PITCHSHIFTER_BUFFERSIZE);
	s->shift(1.5);
	arrStore[0] = s;
	return 1;
}

uint8_t PitchShifterModule::spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

uint8_t PitchShifterModule::spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

PitchShifterModule::~PitchShifterModule() {
	delete values[0];
	delete[] values;
	delete[] inputs;
	delete[] outputs;
}

