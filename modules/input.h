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
				InputModule(uint8_t id);
	uint8_t		spStream(AudioStream **arrStore);
	uint8_t		spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	uint8_t		spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	void		updateForValue(AudioStream **arrStore, uint8_t val);
				~InputModule();
};

#endif /* INPUT_H_ */
