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
	uint8_t		getId();
	Value		**getValues();
	uint8_t		*getInputs();
	uint8_t		*getOutputs();
	const char	*getName();
	const char	**getValueNames();
	uint8_t		getValueCount();
	uint8_t		getInputCount();
	uint8_t		getOutputCount();
	uint8_t		getParalsCount();

	virtual	uint8_t		spStream(AudioStream **arrStore)=0;
	virtual uint8_t		spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx)=0;
	virtual uint8_t		spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx)=0;
	virtual				~Module();
protected:
	uint8_t		id;
	Value		**values	= NULL;		// Pointers to all values (can be cast)
	uint8_t		*inputs		= NULL;
	uint8_t		*outputs	= NULL;

	const char *name;
	const char **valueNames;
	uint8_t valueCount;
	uint8_t inputCount;
	uint8_t outputCount;
	uint8_t paralsCount;

	Module(uint8_t id,
			const char *name, const char **valueNames,
			uint8_t valueCount, uint8_t inputCount,
			uint8_t outputCount, uint8_t paralsCount);
};

#endif /* MODEL_MODULE_H_ */
