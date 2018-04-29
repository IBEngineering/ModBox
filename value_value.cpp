/*
 * value_value.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "value_value.h"

Value	&Value::operator+=(float value)	{return *this;}
Value	&Value::operator+=(int value)		{return *this;}
Value	&Value::operator-=(float value)	{return *this;}
Value	&Value::operator-=(int value)		{return *this;}
Value::~Value(){}
