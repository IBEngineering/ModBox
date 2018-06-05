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
				PitchShifterModule(uint8_t id);
	uint8_t		spStream(AudioStream **arrStore);
	uint8_t		spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	uint8_t		spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	void		updateForValue(AudioStream **arrStore, uint8_t val);
				~PitchShifterModule();
};

#endif /* PITCH_SHIFTER_H_ */
