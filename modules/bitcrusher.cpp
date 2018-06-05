/*
 * bitcrusher.cpp
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#include "bitcrusher.h"

/**
 * This needs to have a name other
 * than 'valueNames' or the constructor
 * will assume that 'valueNames' means
 * the field.
 *
 * (Now it's called *internal*valueNames / _vn)
 */
static const char *_vn[] = {"bits", "sample rate"};

BitCrusherModule::BitCrusherModule(uint8_t id) : Module(id, "BIT", _vn, 1,1,1,1)
{
	values = new Value*[2];
	values[0] = new BoundedValue(4.0f, 1.0f, 1.0f, 16.0f);
	values[1] = new BoundedValue(32000.0f, 2000.0f, 1000.0f, 44000.0f);
	inputs = new uint8_t[1]		{0};
	outputs = new uint8_t[1]	{0};
}

uint8_t BitCrusherModule::spStream(AudioStream **arrStore)
{
	AudioEffectBitcrusher *s = new AudioEffectBitcrusher();
	s->bits(4);
	s->sampleRate(8192.0f);
	arrStore[0] = s;
	return 1;
}

uint8_t BitCrusherModule::spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

uint8_t BitCrusherModule::spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

void BitCrusherModule::updateForValue(AudioStream **arrStore, uint8_t val)
{
	AudioEffectBitcrusher *s = (AudioEffectBitcrusher *)arrStore[0];
	if(val == 0)
	{
		s->bits(((BoundedValue*)values[0])->getValue());
	}
	else if(val == 1)
	{
		s->bits(((BoundedValue*)values[1])->getValue());
	}
}

BitCrusherModule::~BitCrusherModule()
{
	delete values[0];
	delete values[1];
	delete[] values;
	delete[] inputs;
	delete[] outputs;
}
