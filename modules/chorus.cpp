/*
 * chorus.cpp
 *
 *  Created on: Apr 10, 2018
 *      Author: MisterCavespider
 */

#include "chorus.h"

#define MODULE_CHORUS_LENGTH	(6*AUDIO_BLOCK_SAMPLES)

static const char *_vn[] = {"voices"};
static short int delayLine[MODULE_CHORUS_LENGTH];

ChorusModule::ChorusModule(uint8_t id) : Module(id, "CHR", _vn, 1,1,1,1)
{
	values = new Value*[1];
	values[0] = new BoundedValue(8.0f, 1.0f, 1.0f, 16.0f);
	inputs = new uint8_t[1]		{0};
	outputs = new uint8_t[1]	{0};
}

uint8_t ChorusModule::spStream(AudioStream **arrStore)
{
	AudioEffectChorus *s = new AudioEffectChorus();
	s->begin(delayLine, MODULE_CHORUS_LENGTH, 16);
	arrStore[0] = s;
	return 1;
}

uint8_t ChorusModule::spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

uint8_t ChorusModule::spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

void ChorusModule::updateForValue(AudioStream **arrStore, uint8_t val)
{
	AudioEffectChorus *s = (AudioEffectChorus *)arrStore[0];
	if(val == 0)
	{
		s->voices( (int) ((BoundedValue*)values[0])->getValue() );
	}
}

ChorusModule::~ChorusModule()
{
	delete values[0];
	delete[] values;
	delete[] inputs;
	delete[] outputs;
}
