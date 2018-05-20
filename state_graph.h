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

#define STATE_GRAPH_BLOCKS	6

typedef struct drawdata
{
	uint8_t x=0,y=0,w=0;
	uint8_t id=0;
} drawdata_t;

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
	drawdata_t ldd[STATE_GRAPH_BLOCKS];	// left
	drawdata_t mdd;						// middle
	drawdata_t rdd[STATE_GRAPH_BLOCKS];	// right
	uint8_t lDrawn=0, rDrawn=0;

	int16_t currSelect, lastSelect;

	void drawFocus(int8_t f);
	void drawModule(uint8_t id);
	result_t onReFocus(uint8_t flag);

	void isetup();
	void iloop();
};

#endif /* STATE_GRAPH_H_ */
