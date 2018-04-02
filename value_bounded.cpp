/*
 * value_bounded.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "value_bounded.h"

BoundedValue::BoundedValue(float value, float min, float step, float max)
{
	if(min < max)		// In case someone does something stupid
	{
		this->min = min;
		this->max = max;
	}
	else
	{
		this->min = max;
		this->max = min;
	}
	this->step = step;
	this->value = value;
}

BoundedValue::BoundedValue(float min, float step, float max) : BoundedValue(min,min,step,max) {}

BoundedValue	&BoundedValue::operator+=(float value)
{
	this->value += value;
	forceBounds();
	return *this;
}

BoundedValue	&BoundedValue::operator+=(int value)
{
	this->value += step * value;
	forceBounds();
	return *this;
}

BoundedValue	&BoundedValue::operator-=(float value)
{
	this->value -= value;
	forceBounds();
	return *this;
}

BoundedValue	&BoundedValue::operator-=(int value)
{
	this->value -= step * value;
	forceBounds();
	return *this;
}

float BoundedValue::getMinimum()	{return min;}
float BoundedValue::getStep()		{return step;}
float BoundedValue::getMaximum()	{return max;}
float BoundedValue::getValue()		{return value;}

bool BoundedValue::withinBounds()
{
	if(value < min)	return false;
	if(value > max)	return false;
	return true;
}

void BoundedValue::forceBounds()
{
	if(value < min)
	{
		value = min;
		return;
	}
	if(value > max)
	{
		value = max;
		return;
	}
}

BoundedValue::~BoundedValue()	{}
