/*
 * bitcrusher.h
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#ifndef BITCRUSHER_H_
#define BITCRUSHER_H_

#include "../model_module.h"

class BitCrusherModule : public Module {
public:
				BitCrusherModule(uint8_t id);
	uint8_t		spStream(AudioStream **arrStore);
	uint8_t		spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	uint8_t		spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	void		updateForValue(AudioStream **arrStore, uint8_t val);
				~BitCrusherModule();
};

#endif /* BITCRUSHER_H_ */
