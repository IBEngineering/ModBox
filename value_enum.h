/*
 * value_enum.h
 *
 *  Created on: Apr 28, 2018
 *      Author: MisterCavespider
 */

#ifndef VALUE_ENUM_H_
#define VALUE_ENUM_H_

#include <inttypes.h>
#include "value_value.h"

class EnumValue : public Value {
public:
				EnumValue(uint8_t valueCount, const char **names);
				EnumValue(uint8_t valueCount, uint8_t value, const char **names);
	EnumValue	&operator+=(float value);
	EnumValue	&operator+=(int value);
	EnumValue	&operator-=(float value);
	EnumValue	&operator-=(int value);
	uint8_t		identicator();
	uint8_t		getValueCount();
	uint8_t		getValue();
	void		setValue(uint8_t value);
	const char	**getNames();
				~EnumValue();
private:
	uint8_t valueCount;
	uint8_t value;
	const char **names;
};

#endif /* VALUE_ENUM_H_ */
