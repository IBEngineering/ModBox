/*
 * pitch_shifter.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "pitch_shifter.h"
#include "../stk_pitch_shift.h"

static const char *_vn[] = {"shift", };

PitchShifterModule::PitchShifterModule(uint8_t id) : Module(id, "PSH", _vn, 1,1,1,1) {
	values = new Value*[1];
	values[0] = new BoundedValue(1.0, 0.0, 0.01, 3.0);

	inputs = new uint8_t[1]		{0};
	outputs = new uint8_t[1]	{0};
}

uint8_t PitchShifterModule::spStream(AudioStream **arrStore)
{
	StkPitchShift *s = new StkPitchShift(MODULE_PITCHSHIFTER_BUFFERSIZE);
	s->shift(1.0);
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

void PitchShifterModule::updateForValue(AudioStream **arrStore, uint8_t val)
{
	StkPitchShift *s = (StkPitchShift *)arrStore[0];
	if(val == 0)
	{
		s->shift( ((BoundedValue*)values[0])->getValue() );
	}
}

PitchShifterModule::~PitchShifterModule() {
	delete values[0];
	delete[] values;
	delete[] inputs;
	delete[] outputs;
}

