/*
 * value_bounded.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef VALUE_BOUNDED_H_
#define VALUE_BOUNDED_H_

#include "value_value.h"

class BoundedValue: public Value {
public:
	BoundedValue(float value, float min, float step, float max);
	BoundedValue(float min, float step, float max);
	BoundedValue	&operator+=(float value);
	BoundedValue	&operator+=(int value);
	BoundedValue	&operator-=(float value);
	BoundedValue	&operator-=(int value);
	float getMinimum();
	float getStep();
	float getMaximum();
	float getValue();
	~BoundedValue();
protected:
	bool withinBounds();
	void forceBounds();
private:
	float min;
	float step;
	float max;
	float value;
};

#endif /* VALUE_BOUNDED_H_ */
