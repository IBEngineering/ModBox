/*
 * bitcrusher.cpp
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#include "bitcrusher.h"

static const char *valueNames[] = {"bits"};

BitCrusherModule::BitCrusherModule(uint8_t id) : Module(id, "BIT", valueNames, 1,1,1,1)
{
	values = new Value*[1];
	values[0] = new BoundedValue(4.0f, 1.0f, 1.0f, 16.0f);
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

BitCrusherModule::~BitCrusherModule()
{
	delete values[0];
	delete[] values;
	delete[] inputs;
	delete[] outputs;
}
