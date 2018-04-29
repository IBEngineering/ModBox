/*
 * value_enum.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: MisterCavespider
 */

#include "value_enum.h"

EnumValue::EnumValue(uint8_t valueCount, const char **names) {
	this->valueCount = valueCount;
	this->value = 0;
	this->names = names;
}

EnumValue::EnumValue(uint8_t valueCount, uint8_t value, const char **names) {
	this->valueCount = valueCount;
	this->value = value;
	this->names = names;
}

EnumValue &EnumValue::operator+=(float value)
{
	if(this->value < valueCount - value)	this->value += value;
	return *this;
}

EnumValue &EnumValue::operator+=(int value)
{
	if(this->value < valueCount - value)	this->value += value;
	return *this;
}

EnumValue &EnumValue::operator-=(float value)
{
	if(this->value > 0)	this->value -= value;
	return *this;
}

EnumValue &EnumValue::operator-=(int value)
{
	if(this->value > 0)	this->value -= value;
	return *this;
}

uint8_t		EnumValue::getValueCount()			{return valueCount;}
uint8_t		EnumValue::getValue()				{return value;}
void		EnumValue::setValue(uint8_t value)	{this->value = value;}
const char	**EnumValue::getNames()				{return names;}

EnumValue::~EnumValue() {}

