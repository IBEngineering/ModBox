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

void GraphState::drawFocus(int8_t f)
{
	drawdata_t dd;
	if(f == 0)								dd = mdd;
	if(f < 0 && f > -STATE_GRAPH_BLOCKS)	dd = ldd[-f-1];
	if(f > 0 && f <  STATE_GRAPH_BLOCKS)	dd = rdd[ f-1];

	disp->setDrawColor(2);
	disp->drawBox(dd.x-1, dd.y-3, dd.w+2, 7);
	disp->setDrawColor(1);
}

void GraphState::drawModule(uint8_t id)
{
	Module *m = model->modules[id-1];

	mdd.id = id;
	mdd.w = disp->getStrWidth(m->getName());
	mdd.x = 64-(mdd.w+1)/2;
	mdd.y = 32;

	/* THIS USES A BRACKET SETTING: [*] */
	// *
	disp->drawStr(mdd.x, mdd.y+3, m->getName());
	// [
	disp->drawHLine(mdd.x-2, mdd.y-4, 4);
	disp->drawVLine(mdd.x-2, mdd.y-3, 7);
	disp->drawHLine(mdd.x-2, mdd.y+4, 4);
	// ]
	disp->drawHLine(mdd.x+mdd.w-2, mdd.y-4, 4);
	disp->drawVLine(mdd.x+mdd.w+1, mdd.y-3, 7);
	disp->drawHLine(mdd.x+mdd.w-2, mdd.y+4, 4);

	// FIXME: remove this debug
	disp->sendBuffer();

	uint8_t i;

	// Draw the inputs
	uint8_t lDex = model->usesInput(m);
	if(lDex > STATE_GRAPH_BLOCKS)
	{
		disp->setCursor(0,6);
		disp->print("Too many graph blocks here");
		return;
	}
	uint8_t lDac = 0;
	for(i = 0; i < m->getInputCount(); i++)
	{
		uint8_t tId = m->getInputs()[i];
		if(tId > 0)
		{
			Module *t = model->modules[tId-1];
			ldd[lDac].id = tId;
			ldd[lDac].w = disp->getStrWidth(t->getName());
			ldd[lDac].x = mdd.x - ldd[lDac].w - 10;
			ldd[lDac].y = 32 + (lDex*9+lDex-1)/2-4 -1*lDac;

			/* THIS USES A BRACKET SETTING:  *] */
			// *
			disp->drawStr(ldd[lDac].x, ldd[lDac].y+3, t->getName());
			// ]
			disp->drawHLine(ldd[lDac].x+ldd[lDac].w-2, ldd[lDac].y-4, 4);
			disp->drawVLine(ldd[lDac].x+ldd[lDac].w+1, ldd[lDac].y-3, 7);
			disp->drawHLine(ldd[lDac].x+ldd[lDac].w-2, ldd[lDac].y+4, 4);

			lDac++;
		}
	}
	lDrawn = lDac;

	// Draw the outputs
	uint8_t rDex = model->usesOutput(m);
	disp->setCursor(0,6);
	disp->printf("rDex:%d",rDex);
	disp->sendBuffer();
	if(rDex > STATE_GRAPH_BLOCKS)
	{
		disp->setCursor(70,6);
		disp->print("Too many graph blocks here");
		return;
	}
	uint8_t rDac = 0;
	for(i = 0; i < m->getOutputCount() * m->getParalsCount(); i++)
	{
		uint8_t tId = m->getOutputs()[i];
		if(tId > 0)
		{
			Module *t = model->modules[tId-1];
			rdd[rDac].id = tId;
			rdd[rDac].w = disp->getStrWidth(t->getName());
			rdd[rDac].x = mdd.x + mdd.w + 10;
			rdd[rDac].y = 32 + (rDex*9+rDex-1)/2-4 -1*rDac;

			/* THIS USES A BRACKET SETTING: [*  */
			// *
			disp->drawStr(rdd[rDac].x, rdd[rDac].y+3, t->getName());
			// ]
			disp->drawHLine(rdd[rDac].x-2, rdd[rDac].y-4, 4);
			disp->drawVLine(rdd[rDac].x-2, rdd[rDac].y-3, 7);
			disp->drawHLine(rdd[rDac].x-2, rdd[rDac].y+4, 4);

			rDac++;
		}
	}
	rDrawn = rDac;
}

void GraphState::setup()
{
	currSelect = 0;
	lastSelect = 0;
	drawModule(1);
	drawFocus(0);
}

void GraphState::loop()
{

}

/**
 * This function needs to be called when
 * the extender class feels like the focus
 * needs to shift
 * (AKA when currSelect == 0)
 */
result_t GraphState::onReFocus(uint8_t flag)
{
	if(currSelect == 0)	return result_t::EVENT_IGNORED;
	else if(currSelect < 0)
	{
		disp->clearBuffer();
		drawModule(ldd[-currSelect-1].id);
		drawFocus(0);
		currSelect = 0;
		lastSelect = 0;
	}
	else	// currSelect > 0
	{
		disp->clearBuffer();
		drawModule(rdd[currSelect-1].id);
		drawFocus(0);
		currSelect = 0;
		lastSelect = 0;
	}

	return SUCCESS;
}

result_t GraphState::onScrollPri(uint8_t flag, int16_t v)
{
	currSelect += v;
	if(currSelect < -lDrawn) currSelect = lDrawn + 1;
	if(currSelect > rDrawn) currSelect = rDrawn - 1;
	if(currSelect != lastSelect)
	{
		drawFocus(lastSelect);
		drawFocus(currSelect);
		lastSelect = currSelect;
	}

	return result_t::SUCCESS;
}

void GraphState::isetup() {}
void GraphState::iloop() {}

GraphState::~GraphState()
{
}

