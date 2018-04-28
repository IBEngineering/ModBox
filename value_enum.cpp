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
	this->value += value;
	this->value %= valueCount;
	return *this;
}

EnumValue &EnumValue::operator+=(int value)
{
	this->value += value;
	this->value %= valueCount;
	return *this;
}

EnumValue &EnumValue::operator-=(float value)
{
	if(this->value == 0) this->value = valueCount;	// Set to valueCount to prevent underflow
	this->value -= (uint8_t)value % valueCount;		// Modulo valueCount to prevent underflow
	this->value %= valueCount;
	return *this;
}

EnumValue &EnumValue::operator-=(int value)
{
	if(this->value == 0) this->value = valueCount;	// Set to valueCount to prevent underflow
	this->value -= value % valueCount;				// Modulo valueCount to prevent underflow
	this->value %= valueCount;
	return *this;
}

uint8_t		EnumValue::getValueCount()			{return valueCount;}
uint8_t		EnumValue::getValue()				{return value;}
void		EnumValue::setValue(uint8_t value)	{this->value = value;}
const char	**EnumValue::getNames()				{return names;}

EnumValue::~EnumValue() {}

