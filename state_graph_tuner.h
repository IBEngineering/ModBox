/*
 * state_graph_tuner.h
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_GRAPH_TUNER_H_
#define STATE_GRAPH_TUNER_H_

#include "state_graph.h"

class TunerState : public GraphState {
public:
	TunerState(StateManager *mgr, Model *model);
	result_t onConfirm(uint8_t flag);
	result_t onReturn(uint8_t flag);
	~TunerState();
};

#endif /* STATE_GRAPH_TUNER_H_ */
