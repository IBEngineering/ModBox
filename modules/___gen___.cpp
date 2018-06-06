/*
 * ___name___.cpp
 *
 *  Created on: ___date___
 *      Author: ___author___
 */

#include "___name___.h"

static const char *_vn[] = {___values.names()___};

___Name___Module::___Name___Module(uint8_t id) : Module(id, "___TITLE___", _vn, ___values.len___,___inputcount___,___outputcount___,___paralscount___)
{
	values = new Value*[___values.len___];
	___values.creates()___
	inputs = new uint8_t[___inputcount___]		{0};
	outputs = new uint8_t[___outputcount___]	{0};
}

uint8_t ___Name___Module::spStream(AudioStream **arrStore)
{
	___audiostream___ *s = new ___audiostream___();
	___values.defaults()___
	arrStore[0] = s;
	return 1;
}

uint8_t ___Name___Module::spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

uint8_t ___Name___Module::spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx)
{
	*used = arrStore[0];
	*port = 0;
	return 1;
}

void ___Name___Module::updateForValue(AudioStream **arrStore, uint8_t val)
{
	___AudioStream___ *s = (___audiostream___ *)arrStore[0];
	___values.updates()___
}

___Name___Module::~___Name___Module()
{
	___values.deletes()___
	delete[] values;
	delete[] inputs;
	delete[] outputs;
}
