/*
 * model_model.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "model_model.h"

Model::Model(uint8_t size) {
	this->size = size;
	count = 0;
	modules = new Module*[size];

	streams = NULL;
	connections = NULL;
	connectionCount = 0;
	baked = NULL;

	sgtl5000 = AudioControlSGTL5000();
}

int8_t Model::hasInput(Module *t, Module *m)
{
	for(uint8_t i = 0; i < t->getInputCount(); i++)
	{
		if(t->getInputs()[i] == m->getId())	return i;
	}
	return -1;
}

void Model::deleteAllAudio()
{
	for(int i = 0; i < size; i++)
	{
		if(modules[i] != NULL)	delete modules[i];
	}
	delete[] modules;

	for(int i = 0; i < 2*size; i++)
	{
		if(connections[i] != NULL)	delete connections[i];
	}
	delete[] connections;
	connectionCount = 0;
}

result_t Model::bakeAudioFor(uint8_t id)
{
	if(baked[id])	return result_t::SUCCESS;

	uint8_t i;

	Module *m = modules[id];
	if(m == NULL)	return result_t::UNKNOWN;

	m->spStream(&streams[id]);
	baked[id] = true;

	for(i = 0; i < m->getInputCount(); i++)
	{
		if(!baked[m->getInputs()[i]])
		{
			bakeAudioFor(m->getInputs()[i]);
		}
	}

	for(i = 0; i < m->getOutputCount() * m->getParalsCount(); i++)
	{
		// FIXME: this is really janky
		uint8_t tIdx = m->getOutputs()[i];
		if(tIdx >= 4) break;
		Module *t = modules[tIdx];
		uint8_t in = hasInput(t, m);
		if(in >= 0)
		{
			AudioStream *fUse, *tUse;
			int fPort, tPort;
			bakeAudioFor(t->getId());
			m->spConnOut(&streams[id], &fUse, &fPort, i);
			t->spConnIn(&streams[t->getId()], &tUse, &tPort, in);

			connections[connectionCount] = new AudioConnection(*fUse, fPort, *tUse, tPort);
			connectionCount++;
		}
	}

	return SUCCESS;
}

result_t Model::bakeAudioFrom(uint8_t id)
{
	if(modules[id]->getInputCount() > 0)	return result_t::UNKNOWN;

	if(streams != NULL || connections != NULL)	deleteAllAudio();
	if(baked != NULL)							delete[] baked;

	streams = new AudioStream*[size];	// TODO: will not work for modules with multiple streams
	connections = new AudioConnection*[2*size];	// Assumes an average of 2 connections per module
	baked = new bool[size];
	for(int i = 0; i < size; i++){baked[i] = false;}

	result_t r = bakeAudioFor(id);
	if(r < 0)
	{
		return r;
	}

	sgtl5000.enable();
	sgtl5000.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000.volume(0.5);
	sgtl5000.adcHighPassFilterDisable();

	return SUCCESS;
}

Model::~Model() {}

