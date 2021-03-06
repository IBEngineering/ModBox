/*
 * value_value.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef VALUE_VALUE_H_
#define VALUE_VALUE_H_

#include <stdint.h>

class Value {
public:
	virtual Value	&operator+=(float value)	=0;
	virtual Value	&operator+=(int value)		=0;
	virtual Value	&operator-=(float value)	=0;
	virtual Value	&operator-=(int value)		=0;
	virtual uint8_t	identicator()				=0;
	virtual ~Value();
};

#endif /* VALUE_VALUE_H_ */
