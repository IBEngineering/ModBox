/*
 * gui.h
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#ifndef GUI_H_
#define GUI_H_

#include <U8g2lib.h>

#include "hardware.h"
#include "results.h"

// Defines

/**
 * Currently hard coded
 */
#define GDISP_SOFTWARE
#define GDISP_FANCYFRAMES		true
#define GDISP_TITLE 			"{  %s  }"

#define GDISP_POPUP_MAXLINES	6
#define GDISP_POPUP_NEXTLINE	6
#define GDISP_POPUP_X			6
#define GDISP_POPUP_TITLE_Y		12
#define GDISP_POPUP_TEXT_Y		19

#ifdef GDISP_SOFTWARE
#define GDISPLAY		U8G2_ST7920_128X64_F_SW_SPI
#endif

#ifdef GDISP_HARDWARE
#define GDISP		U8G2_ST7920_128X64_F_HW_SPI
#endif

// Screen
class Screen
{
public:
	Screen(GDISPLAY *disp, const char *title);
	virtual result_t show() =0;
	virtual ~Screen();
protected:
	GDISPLAY *disp;
	char *title;
	uint8_t currentLine;
};

// Popup
class Popup : public Screen
{
public:
	Popup(GDISPLAY *disp, const char *title);
	result_t show();
	bool next();
private:
	void drawFrame(bool fancy);
	void drawTitle();
};

//Menu
class Menu : public Screen
{
public:
	Menu(GDISPLAY *disp, const char *title, bool scrollable);
	result_t show();
	result_t update();
	result_t push(const char *item);
	// TODO: add push values for different types (of values)
	result_t setFocus(uint8_t focus);
	~Menu();
private:
	void drawTitle();

	bool scrollable;
	uint8_t lastFocus, currFocus;	// 256 options should be enough
	/* Amount of pushed items */
	uint8_t count;
	const char **items;
};

// Methods

void gdisp_init();

void gdisp_showPopupResult(GDISPLAY *disp, result_t r, const char *name);

#endif /* GUI_H_ */
