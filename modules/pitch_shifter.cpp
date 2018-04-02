/*
 * pitch_shifter.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "pitch_shifter.h"
#include "../stk_pitch_shift.h"

static const char **valueNames = {"shift"};

PitchShifterModule::PitchShifterModule() {
	audioStream = new StkPitchShift(MODULE_PITCHSHIFTER_BUFFERSIZE);
	values = new Value*[1];
	values[0] = new BoundedValue(0.0, 0.01, 3.0);
}

const char	*PitchShifterModule::getName()			{return "SHFT";}
const char	**PitchShifterModule::getValueNames()	{return valueNames;}
uint8_t		PitchShifterModule::getValueCount()		{return 1;}
uint8_t		PitchShifterModule::getInputCount()		{return 1;}
uint8_t		PitchShifterModule::getOutputCount()	{return 1;}
uint8_t		PitchShifterModule::getParalsCount()	{return 1;}

PitchShifterModule::~PitchShifterModule() {
	delete audioStream;
	delete values[0];
	delete[] values;
}

