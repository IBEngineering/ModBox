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
#include "value_bounded.h"
#include "value_enum.h"
#include "value_value.h"
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

#define GDISP_MENU_MAXLINES		9
#define GDISP_MENU_NEXTLINE		6
#define GDISP_MENU_X			1
#define GDISP_MENU_TITLE_Y		5
#define GDISP_MENU_TEXT_Y		15

#define GDISP_PLOT_TITLE_Y		6

#ifdef GDISP_SOFTWARE
#define GDISPLAY		U8G2_ST7920_128X64_F_SW_SPI
#endif

#ifdef GDISP_HARDWARE
#define GDISP		U8G2_ST7920_128X64_F_HW_SPI
#endif

// Item type
typedef enum
{
	TEXT = 0,
	VALUE_BOUNDED = 1,
	VALUE_BUFFER = 2,
	VALUE_ENUM = 3
} ItemType;

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

// Menu
class Menu : public Screen
{
public:
	Menu(GDISPLAY *disp, const char *title, bool scrollable);
	result_t show();
	result_t update();
	result_t push(const char *item);
	result_t pushBoundedValue(const char *item, BoundedValue *val);
	result_t pushEnumValue(const char *item, EnumValue *val);
	// TODO: add push values for different types (of values)
	uint8_t getFocus();
	result_t setFocus(uint8_t focus);
	~Menu();

	uint8_t count;					// Arount of pushed items
private:
	void drawTitle();
	void drawScrollBar();
	void drawItem(uint8_t ii, uint8_t mi);
	void drawItemsStatic();			// Without scrolling
	void drawItemsDynamic();		// With scrolling
	void drawFocus(bool d);

	bool scrollable;
	uint8_t topFocus;				// Top of the visible list

	uint8_t lastFocus, currFocus;	// 256 options should be enough

//	uint8_t count;					// Amount of pushed items
	const char **items;
	ItemType *types;
	Value **values;
};

// Plot
enum PlotType
{
	WRAP, SCROLL
};
class Plot : public Screen
{
public:
	Plot(GDISPLAY *disp, const char *title, PlotType type,
			float minY, float maxY, uint8_t stepX, uint8_t stepY);
	result_t show();
	result_t put(uint8_t idx, float y);
private:
	uint8_t vals[124];
	PlotType type;
	float minY;
	float maxY;
	uint8_t stepX;
	uint8_t stepY;

	void drawTitle();
	void drawAxes();
};

// Methods

void gdisp_init();

void gdisp_showPopupResult(GDISPLAY *disp, result_t r, const char *name);

#endif /* GUI_H_ */
