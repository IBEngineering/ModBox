/*
 * ___name___.h
 *
 *  Created on: ___date___
 *      Author: ___author___
 */

#ifndef ___NAME____H_
#define ___NAME____H_

#include "../model_module.h"

class ___Name___Module : public Module {
public:
				___Name___Module(uint8_t id);
	uint8_t		spStream(AudioStream **arrStore);
	uint8_t		spConnIn(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	uint8_t		spConnOut(AudioStream **arrStore, AudioStream **used, int *port, int idx);
	void		updateForValue(AudioStream **arrStore, uint8_t val);
				~___Name___Module();
};

#endif /* ___NAME____H_ */
