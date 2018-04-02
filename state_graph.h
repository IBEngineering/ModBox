/*
 * state_graph.h
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#ifndef STATE_GRAPH_H_
#define STATE_GRAPH_H_

#include "state_state.h"

class GraphState : public ProgramState
{
public:
	GraphState(StateManager *mgr, const char *title);
	virtual ~GraphState();
};

#endif /* STATE_GRAPH_H_ */
