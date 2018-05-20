/*
 * state_menu_test.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: MisterCavespider
 */

#include "state_menu_test.h"

#include <sys/_stdint.h>

#include "gui.h"
#include "results.h"
#include "state_mgr.h"
#include "value_bounded.h"
#include "value_enum.h"
#include "value_value.h"

static const char *a0[] =
{
	"CHEBY8", "CHEBY16", "CHEBY32", "CHEBY64"
};

static const char *a1[] =
{
	"NULL"
};

static BoundedValue bv_THIS = BoundedValue(0, -1, 0, 1);
static EnumValue ev_Enum_Value = EnumValue(4, 1, a0);
static BoundedValue bv_resonance = BoundedValue(4.30, 0, 0.1, 5);
static BoundedValue bv_frequency = BoundedValue(110.0, 20, 10, 2000);
static BoundedValue bv_something_else = BoundedValue(5, 0, 1, 10);
static BoundedValue bv_delay = BoundedValue(0, 0.1, 10);
static EnumValue ev_nothing = EnumValue(1,0,a1);

TestMenuState::TestMenuState(StateManager *mgr) : MenuState(mgr, "Test GUI") {
}

//result_t TestMenuState::onScrollPri(uint8_t flag, int16_t v)
//{
//	if(v == 0)	return EVENT_IGNORED;
//	if(v > 0)
//	{
//		menu->setFocus(menu->getFocus() + 1);
//	}
//	else if(menu->getFocus() > 0)	// && v < 0
//	{
//		menu->setFocus(menu->getFocus() - 1);
//	}
//	return EVENT_CONSUMED;
//}
//
//result_t TestMenuState::onScrollSec(uint8_t flag, int16_t v)
//{
//	if(v==0)	return EVENT_IGNORED;
//
//	ItemType type = menu->getItemType(menu->getFocus());
//	if(type == VALUE_BOUNDED)
//	{
//		BoundedValue *bval = (BoundedValue *)menu->getValue(menu->getFocus());
//		*(bval) += (v<0)?-1:1;
//	}
//	else if(type == VALUE_ENUM)
//	{
//		EnumValue *eval = (EnumValue *)menu->getValue(menu->getFocus());
//		*(eval) += (v<0)?-1:1;
//	}
//	else
//	{
//		return EVENT_IGNORED;
//	}
//
//	menu->updateItem(menu->getFocus());
//
//	return EVENT_CONSUMED;
//}

result_t TestMenuState::onReturn(uint8_t flag)
{
	mgr->setCurrentState(0);	// Main menu
	return EVENT_CONSUMED;
}

void TestMenuState::isetup()
{
	menu->pushBoundedValue("THIS", &bv_THIS);
	menu->push("More Text");
	menu->pushEnumValue("Enum Value", &ev_Enum_Value);
	menu->push("");
	menu->pushBoundedValue("resonance", &bv_resonance);
	menu->pushBoundedValue("frequency", &bv_frequency);
	menu->pushBoundedValue("something else", &bv_something_else);
	menu->pushBoundedValue("delay", &bv_delay);
	menu->pushEnumValue("nothing", &ev_nothing);
	menu->push("(hidden)");
}

void TestMenuState::iloop()
{

}

TestMenuState::~TestMenuState() {
}

