/*
 * chorus.h
 *
 *  Created on: Apr 10, 2018
 *      Author: MisterCavespider
 */

#ifndef CHORUS_H_
#define CHORUS_H_

#include "../model_module.h"

class ChorusModule : public Module {
public:
				ChorusModule(uint8_t id);
	uint8_t		spStream(AudioStream **arrStore);
	uint8_t		spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	uint8_t		spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	void		updateForValue(AudioStream **arrStore, uint8_t val);
				~ChorusModule();
};

#endif /* CHORUS_H_ */
