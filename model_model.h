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
#include "results.h"

class Model {
public:
	Model(uint8_t size);
	result_t bakeAudioFrom(uint8_t id);
	virtual ~Model();

	Module			**modules;	// TODO: PUT THIS BAKC IN PRIVATE
	int8_t hasInput(Module *t, Module *m);	// TODO: same
private:
	uint8_t			size;
	uint8_t			count;
//	Module			**modules;
	bool			*baked;

	AudioStream		**streams;
	AudioConnection	**connections;
	uint8_t			connectionCount;

	// Audio
	AudioControlSGTL5000	sgtl5000;

//	int8_t hasInput(Module *t, Module *m);
	void deleteAllAudio();
	result_t bakeAudioFor(uint8_t id);
};

#endif /* MODEL_MODEL_H_ */
