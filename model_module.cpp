/*
 * model_module.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "model_module.h"

Module::Module(uint8_t id,
		const char *name, const char **valueNames,
		uint8_t valueCount, uint8_t inputCount,
		uint8_t outputCount, uint8_t paralsCount)
{
	this->id = id;
	this->name = name;
	this->valueNames = valueNames;
	this->valueCount = valueCount;
	this->inputCount = inputCount;
	this->outputCount = outputCount;
	this->paralsCount = paralsCount;
}

uint8_t		Module::getId()				{return id;}
Value		**Module::getValues()		{return values;}
uint8_t		*Module::getInputs()		{return inputs;}
uint8_t		*Module::getOutputs()		{return outputs;}
const char	*Module::getName()			{return name;}
const char	**Module::getValueNames()	{return valueNames;}
uint8_t		Module::getValueCount()		{return valueCount;}
uint8_t		Module::getInputCount()		{return inputCount;}
uint8_t		Module::getOutputCount()	{return outputCount;}
uint8_t		Module::getParalsCount()	{return paralsCount;}

Module::~Module()
{
}

