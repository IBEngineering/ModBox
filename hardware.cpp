/*
 * hardware.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#include "hardware.h"

/**
 * Everything starts off as 0.
 */
EncoderButton::EncoderButton(uint8_t pin)
{
	this->pin = pin;
	curr = 0;
	last = 0;
	delta = 0;
}

void EncoderButton::read()
{
	last = curr;
	curr = !digitalRead(pin);
	delta = curr - last;
}

uint8_t EncoderButton::current_read()
{
	return curr;
}

uint8_t EncoderButton::last_read()
{
	return last;
}

int8_t EncoderButton::delta_read()
{
	return delta;
}
