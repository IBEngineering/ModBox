/*
 * gui.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#include <string.h>

#include "gui.h"

// Screen

Screen::Screen(GDISPLAY *disp, const char *title)
{
	this->disp = disp;
	this->title = new char[40];
	sprintf(this->title, GDISP_TITLE, title);
	this->currentLine = 0;
}

result_t Screen::show()	{return UNIMPLEMENTED;}

Screen::~Screen()
{
	delete[] title;
}

// Popup

Popup::Popup(GDISPLAY *disp, const char *title) : Screen(disp,title) {}

void Popup::drawFrame(bool fancy)
{
	disp->drawFrame(4,4,120,56);
	disp->setDrawColor(0);
	disp->drawBox(5,5,118,54);
	if(fancy)
	{
		disp->drawPixel(4,4);
		disp->drawPixel(123, 59);
		disp->setDrawColor(1);
		disp->drawHLine(3,60,17);
		disp->drawVLine(3,52,9);
		disp->drawHLine(108,3,17);
		disp->drawVLine(124,3,9);
	}
	else
	{
		disp->setDrawColor(1);
	}
}

void Popup::drawTitle()
{
	uint8_t w = disp->getStrWidth(title);
	disp->setCursor(64-(w+1)/2, GDISP_POPUP_TITLE_Y);
	disp->print(title);
}

result_t Popup::show()
{
	drawFrame(GDISP_FANCYFRAMES);
	drawTitle();

	return SUCCESS;
}

bool Popup::next()
{
	if(currentLine < GDISP_POPUP_MAXLINES)
	{
		disp->setCursor(GDISP_POPUP_X, GDISP_POPUP_TEXT_Y+GDISP_POPUP_NEXTLINE*currentLine);
		currentLine++;
		return true;
	}
	else
	{
		return false;
	}
}

// Menu

Menu::Menu(GDISPLAY *disp, const char *title, bool scrollable) : Screen(disp,title)
{
	this->scrollable = scrollable;
	this->topFocus = 0;
	this->lastFocus = 0;
	this->currFocus = 0;
	this->count = 0;
	this->values = new Value*[256];		/* 256 values  */
	this->types = new ItemType[256];	/* 256 types   */
	this->items = new const char*[256]; /* 256 strings */
}

void Menu::drawTitle()
{
	uint8_t w = disp->getStrWidth(title);
	disp->setCursor(64-(w+1)/2, GDISP_MENU_TITLE_Y);
	disp->print(title);
	disp->drawHLine(64-(w+3)/2, GDISP_MENU_TITLE_Y+2, w+2);
}

void Menu::drawScrollBar()
{
	// Draw arrows
	if(topFocus > 0)
	{
		disp->drawPixel(124, 9);
		disp->drawHLine(123, 10, 3);
		disp->drawHLine(122, 11, 5);
		disp->drawVLine(124, 12, 4);
	}
	if(topFocus + GDISP_MENU_MAXLINES < count)
	{
		disp->drawVLine(124, 56, 4);
		disp->drawHLine(122, 60, 5);
		disp->drawHLine(123, 61, 3);
		disp->drawPixel(124, 62);
	}

	// Draw box
	disp->drawFrame(123, 17, 3, 38);

	// Draw slider
	disp->drawVLine(124, 18 + (topFocus*38)/count, (GDISP_MENU_MAXLINES*38)/count);
}

void Menu::drawItem(uint8_t ii, uint8_t mi)
{
	uint8_t y = GDISP_MENU_TEXT_Y+GDISP_MENU_NEXTLINE*mi;
	disp->setCursor(GDISP_MENU_X, y);
	disp->print(items[ii]);
	if(types[ii] == VALUE_BOUNDED)
	{
		BoundedValue *bval = (BoundedValue *)values[ii];

		// Draw arrows
		if(bval->getValue() > bval->getMinimum())
		{
			disp->setCursor(83, y);
			disp->print("<");
		}
		if(bval->getValue() < bval->getMaximum())
		{
			disp->setCursor(117, y);
			disp->print(">");
		}

		// Draw text
		char buffer[16];	// TODO: declare this in a macro/global
		sprintf(buffer, "%.5g", bval->getValue());
		uint8_t w = disp->getStrWidth(buffer);
		disp->setCursor(101-w/2, y);
		disp->print(buffer);
	}
	else if(types[ii] == VALUE_ENUM)
	{
		EnumValue *eval = (EnumValue *)values[ii];

		// Draw arrows
		if(eval->getValue() > 0)
		{
			disp->setCursor(83, y);
			disp->print("<");
		}
		if(eval->getValue() < eval->getValueCount() - 1)
		{
			disp->setCursor(117, y);
			disp->print(">");
		}

		// Draw text
		char buffer[8];	// 7 chars + \0
		sprintf(buffer, "%.7s", eval->getNames()[eval->getValue()]);
		uint8_t w = disp->getStrWidth(buffer);
		disp->setCursor(101-w/2, y);
		disp->print(buffer);
	}
}

void Menu::drawItemsStatic()
{
	uint8_t i;

	for(i = 0; i < count; i++)
	{
		drawItem(i,i);
	}
}

void Menu::drawItemsDynamic()
{
	if(count <= GDISP_MENU_MAXLINES)
	{
		drawItemsStatic();
	}
	else
	{
		drawScrollBar();
		for(int i = 0; i < GDISP_MENU_MAXLINES; i++)
		{
			drawItem(topFocus + i, i);
		}
	}
}

void Menu::drawFocus(bool changed)
{
	uint8_t cf = currFocus;
	uint8_t lf = lastFocus;
	if(scrollable)
	{
		cf -= topFocus;
		lf -= topFocus;
	}

	disp->setDrawColor(2);
	disp->drawBox(0, 9+GDISP_MENU_NEXTLINE*cf, (scrollable)?121:128, 7);
	if(changed)	disp->drawBox(0, 9+GDISP_MENU_NEXTLINE*lf, (scrollable)?121:128, 7);
	disp->setDrawColor(1);
}

result_t Menu::show()
{
	drawTitle();
	(scrollable) ? drawItemsDynamic() : drawItemsStatic();
	drawFocus(false);

	return SUCCESS;
}

result_t Menu::updateItem(uint8_t i)
{
	drawFocus(false);
	disp->setDrawColor(0);
	disp->drawBox(0, 9+GDISP_MENU_NEXTLINE*i, (scrollable)?121:128, 7);
	disp->setDrawColor(1);
	drawItem(i, i - topFocus);
	drawFocus(false);

	return SUCCESS;
}

result_t Menu::push(const char *item)
{
	if(count > ((scrollable) ? 255 : GDISP_MENU_MAXLINES))	return OUT_OF_BOUNDS;
	items[count] = item;
	types[count] = TEXT;
	count++;
	return SUCCESS;
}

result_t	Menu::pushAny(const char *item, Value *val)
{
	if(val == NULL)					return push(item);
	if(val->identicator() == 0x01)	return pushBoundedValue(item, (BoundedValue *)val);
	if(val->identicator() == 0x02)	return pushEnumValue(item, (EnumValue *)val);

	// Upon nothing
	return INVALID_ARGUMENT;
}

result_t Menu::pushBoundedValue(const char *item, BoundedValue *val)
{
	if(count > ((scrollable) ? 255 : GDISP_MENU_MAXLINES))	return OUT_OF_BOUNDS;
	items[count] = item;
	types[count] = VALUE_BOUNDED;
	values[count] = val;
	count++;
	return SUCCESS;
}

result_t Menu::pushEnumValue(const char *item, EnumValue *val)
{
	if(count > ((scrollable) ? 255 : GDISP_MENU_MAXLINES))	return OUT_OF_BOUNDS;
	items[count] = item;
	types[count] = VALUE_ENUM;
	values[count] = val;
	count++;
	return SUCCESS;
}

uint8_t Menu::getFocus()
{
	return currFocus;
}

result_t Menu::setFocus(uint8_t focus)
{
	if(focus >= count) return OUT_OF_BOUNDS;

	lastFocus = currFocus;
	currFocus = focus;

	if(scrollable)
	{
		if(focus < topFocus)
		{
			topFocus = focus;
			disp->setDrawColor(0);
			disp->drawBox(0, GDISP_MENU_TITLE_Y+3, 128, 64-GDISP_MENU_TITLE_Y-3);
			disp->setDrawColor(1);
			drawItemsDynamic();
			drawFocus(false);
		}
		else if(focus >= topFocus + GDISP_MENU_MAXLINES)
		{
			topFocus = focus - GDISP_MENU_MAXLINES + 1;
			disp->setDrawColor(0);
			disp->drawBox(0, GDISP_MENU_TITLE_Y+3, 128, 64-GDISP_MENU_TITLE_Y-2);
			disp->setDrawColor(1);
			drawItemsDynamic();
			drawFocus(false);
		}
		else
		{
			drawFocus(true);
		}
	}
	else
	{
		drawFocus(true);
	}

	return SUCCESS;
}

const char	*Menu::getItem(uint8_t i)		{return items[i];}
ItemType	Menu::getItemType(uint8_t i)	{return types[i];}
Value		*Menu::getValue(uint8_t i)		{return values[i];}

Menu::~Menu()
{
	delete[] items;
	delete[] types;
	delete[] values;
}

// Plot
Plot::Plot(GDISPLAY *disp, const char *title, PlotType type,
			float minY, float maxY, uint8_t stepX, uint8_t stepY) : Screen(disp, title)
{
	this->type = type;
	this->minY = minY;
	this->maxY = maxY;
	this->stepX = stepX;
	this->stepY = stepY;
}

result_t Plot::show()
{
	drawTitle();
	drawAxes();
	return SUCCESS;
}

result_t Plot::put(uint8_t idx, float y)
{
	vals[idx] = ((y - minY) / (maxY - minY)) * 52;
	disp->drawVLine(3 + idx, 61 - vals[idx], vals[idx]);
	if(type == WRAP)
	{
		disp->setDrawColor(0);
		disp->drawVLine(3+idx + ((idx==123)?-123:1), 9, 51);
		disp->setDrawColor(1);
	}
	return SUCCESS;
}

void Plot::drawTitle()
{
	uint8_t w = disp->getStrWidth(title);
	disp->setCursor(64-(w+1)/2, GDISP_MENU_TITLE_Y);
	disp->print(title);
	disp->drawHLine(64-(w+3)/2, GDISP_MENU_TITLE_Y+2, w+2);
}

void Plot::drawAxes()
{
	disp->drawVLine(2,9,54);
	disp->drawHLine(1,61,126);

	int s = 3 + stepX;
	while(s <= 126)
	{
		disp->drawPixel(s, 62);
		s += stepX;
	}

	s = 61 - stepX;
	while(s >= 9)
	{
		disp->drawPixel(1, s);
		s -= stepX;
	}
}

// Methods

void gdisp_init()
{
	// TODO: init u8g2
}

void gdisp_showPopupResult(GDISPLAY *disp, result_t r, const char *msg)
{
	Popup *popup = new Popup(disp, (r<0)?"Error":"Result");
	popup->show();
	if(!popup->next())	return;
	disp->printf("Code: %d", r);
	if(!popup->next())	return;
	disp->printf("Msg: %s", msg);
	delete popup;
	disp->sendBuffer();
	delay(1500);
}

