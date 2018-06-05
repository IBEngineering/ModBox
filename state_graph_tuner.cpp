/*
 * state_graph_tuner.cpp
 *
 *  Created on: May 20, 2018
 *      Author: MisterCavespider
 */

#include "state_graph_tuner.h"

#include "state_menu_tune.h"

TunerState::TunerState(StateManager *mgr, Model *model) : GraphState(mgr, "Tuner", model)
{
	// Do nothing special here
}

result_t TunerState::onConfirm(uint8_t flag)
{
	if(currSelect == 0)
	{
		((TuneMenuState *)mgr->states[3])->setModule(model->modules[mdd.id-1]);
		mgr->setCurrentState(3);
	}
	else
	{
		return onReFocus(flag);
	}

	return EVENT_CONSUMED;
}

result_t TunerState::onReturn(uint8_t flag)
{
	mgr->setCurrentState(0);
	return EVENT_CONSUMED;
}

TunerState::~TunerState()
{
	// Do nothing special here
}

