/*
 * state_graph.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_GRAPH_H_
#define STATE_GRAPH_H_

#include "model_model.h"
#include "state_state.h"

class GraphState : public ProgramState
{
public:
	GraphState(StateManager *mgr, const char *title, Model *model);
	void setup();
	void loop();
	result_t onScrollPri(uint8_t flag, int16_t v);
	virtual ~GraphState();
protected:
	Model *model;

	uint8_t currSelect, lastSelect;

	void drawModule(uint8_t id);

	void isetup();
	void iloop();
};

#endif /* STATE_GRAPH_H_ */
