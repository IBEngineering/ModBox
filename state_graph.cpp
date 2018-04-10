/*
 * state_graph.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: MisterCavespider
 */

#include "state_graph.h"

GraphState::GraphState(StateManager *mgr, const char *title, Model *model) : ProgramState(mgr,title)
{
	this->model = model;

	currSelect = 0;
	lastSelect = 0;
}

void GraphState::drawModule(uint8_t id)
{
	Module *m = model->modules[id];

	uint8_t w = disp->getStrWidth(m->getName());
	uint8_t x = 64-(w+1)/2;
	uint8_t y = 32;

	/* THIS USES A BRACKET SETTING: [*] */
	// *
	disp->drawStr(x, y+3, m->getName());
	// [
	disp->drawHLine(x-2, y-4, 4);
	disp->drawVLine(x-2, y-3, 7);
	disp->drawHLine(x-2, y+4, 4);
	// ]
	disp->drawHLine(x+w-2, y-4, 4);
	disp->drawVLine(x+w+1, y-3, 7);
	disp->drawHLine(x+w-2, y+4, 4);

	uint8_t i;

	// Draw the inputs
	// TODO: ^

	// Draw the outputs
	// TODO: ^
}

void GraphState::setup()
{
	drawModule(0);
}

void GraphState::loop()
{

}

result_t GraphState::onScrollPri(uint8_t flag, int16_t v)
{
	return result_t::EVENT_IGNORED;
}

void GraphState::isetup() {}
void GraphState::iloop() {}

GraphState::~GraphState()
{
	// TODO Auto-generated destructor stub
}

