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
	this->items = new const char*[256]; /* 256 strings */
}

void Menu::drawTitle()
{
	uint8_t w = disp->getStrWidth(title);
	disp->setCursor(64-(w+1)/2, GDISP_MENU_TITLE_Y);
	disp->print(title);
	disp->drawHLine(64-(w+3)/2, GDISP_MENU_TITLE_Y+2, w+2);
}

void Menu::drawItemsStatic()
{
	uint8_t i;

	for(i = 0; i < count; i++)
	{
		disp->setCursor(GDISP_MENU_X, GDISP_MENU_TEXT_Y+GDISP_MENU_NEXTLINE*i);
		disp->print(items[i]);
	}
}

void Menu::drawItemsDynamic()
{

}

result_t Menu::show()
{
	drawTitle();
	(scrollable) ? drawItemsDynamic() : drawItemsStatic();

	return UNIMPLEMENTED;
}

result_t Menu::update()
{
	return UNIMPLEMENTED;
}

result_t Menu::push(const char *item)
{
	if(count > ((scrollable) ? 255 : GDISP_MENU_MAXLINES))	return OUT_OF_BOUNDS;
	items[count] = item;
	count++;
	return SUCCESS;
}

result_t Menu::setFocus(uint8_t focus)
{
	if(focus > count) return OUT_OF_BOUNDS;
	lastFocus = currFocus;
	currFocus = focus;
	return SUCCESS;
}

Menu::~Menu()
{
	delete[] items;
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
}

