/*
 * input.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "../model_module.h"

class InputModule: public Module {
public:
				InputModule();
	const char	*getName();
	const char	**getValueNames();
	uint8_t		getValueCount();
	uint8_t		getInputCount();
	uint8_t		getOutputCount();
	uint8_t		getParalsCount();
				~InputModule();
};

#endif /* INPUT_H_ */
