/*
 * pitch_shifter.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef PITCH_SHIFTER_H_
#define PITCH_SHIFTER_H_

#define MODULE_PITCHSHIFTER_BUFFERSIZE	2048

#include "../model_module.h"

class PitchShifterModule : public Module {
public:
				PitchShifterModule();
	const char	*getName();
	const char	**getValueNames();
	uint8_t		getValueCount();
	uint8_t		getInputCount();
	uint8_t		getOutputCount();
	uint8_t		getParalsCount();
				~PitchShifterModule();
};

#endif /* PITCH_SHIFTER_H_ */
