/*
 * output.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "../model_module.h"

class OutputModule: public Module {
public:
				OutputModule();
	const char	*getName();
	const char	**getValueNames();
	uint8_t		getValueCount();
	uint8_t		getInputCount();
	uint8_t		getOutputCount();
	uint8_t		getParalsCount();
				~OutputModule();
};

#endif /* OUTPUT_H_ */
