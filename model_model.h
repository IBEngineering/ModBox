/*
 * model_model.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <stdint.h>

#include "model_module.h"

class Model {
public:
	Model();
	void bakeAudioFrom();
	virtual ~Model();
private:
	uint8_t size;
	uint8_t count;
	Module **modules;

	// Audio
	AudioControlSGTL5000	sgtl5000;
};

#endif /* MODEL_MODEL_H_ */
