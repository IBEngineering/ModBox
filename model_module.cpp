/*
 * model_module.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "model_module.h"

AudioStream	*Module::getAudioStream()
{
	return audioStream;
}

Value		**Module::getValues()
{
	return values;
}

Module::~Module()
{
}

