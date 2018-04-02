/*
 * model_module.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef MODEL_MODULE_H_
#define MODEL_MODULE_H_

#include <Audio.h>
#include "value_bounded.h"
#include "value_value.h"

class Module {
public:
			AudioStream	*getAudioStream();
			Value		**getValues();
	virtual	const char	*getName();
	virtual	const char	**getValueNames();
	virtual	uint8_t		getValueCount();
	virtual	uint8_t		getInputCount();
	virtual	uint8_t		getOutputCount();
	virtual	uint8_t		getParalsCount();
	virtual				~Module();
protected:
	AudioStream	*audioStream;	// A mallocated audio module
	Value		**values;		// Pointers to all values (can be cast)
};

#endif /* MODEL_MODULE_H_ */
