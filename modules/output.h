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
				OutputModule(uint8_t id);
	uint8_t		spStream(AudioStream **arrStore);
	uint8_t		spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	uint8_t		spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx);
				~OutputModule();
};

#endif /* OUTPUT_H_ */
